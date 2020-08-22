// LTRP Code
// www.stratocan.eu

#include <Arduino.h>
#include <Wire.h>
#include <SerialTransfer.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <I2Cdev.h>
#include <MPU6050_6Axis_MotionApps_V6_12.h>

#define BAUDRATE 115200
#define builtInLED 13
#define DHTpin 5
#define BMP280addr (0x76) // adresa BMP280
#define MPUint 3
#define MPU6050addr (0x68) //adresa MPU6050

SerialTransfer Transfer;
DHT dht(DHTpin, DHT11);
Adafruit_BMP280 bmp;
MPU6050 mpu;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer
// MPU orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 gy;         // [x, y, z]            gyro sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

int bmpKorekce = 32;

struct STRUCT {
	float DHTtemp;
	float DHThum;
	float BMPtemp;
	float BMPpress;
	float BMPalt;
	float yaw;
	float pitch;
	float roll;
	float aaX;
	float aaY;
	float aaZ;
	String err;
} data;

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
	mpuInterrupt = true;
}

void setup() {
	pinMode(builtInLED, OUTPUT);
	pinMode(MPUint, INPUT);

	Serial.begin(BAUDRATE);
	Transfer.begin(Serial);
	Wire.begin();
	Wire.setClock(400000);
	dht.begin();
	bmp.begin(BMP280addr);
	mpu.initialize();
	devStatus = mpu.dmpInitialize();

	// gyro offsets, scaled for min sensitivity
	mpu.setXGyroOffset(51);
	mpu.setYGyroOffset(8);
	mpu.setZGyroOffset(21);
	mpu.setXAccelOffset(1150);
	mpu.setYAccelOffset(-50);
	mpu.setZAccelOffset(1060);

	// fungovalo to??
	if (devStatus == 0) {
		// kalibrace - generate offsets and calibrate MPU
		mpu.CalibrateAccel(6);
		mpu.CalibrateGyro(6);
		//mpu.PrintActiveOffsets();
		mpu.setDMPEnabled(true);
		// enable arduino interrupt detection
		attachInterrupt(digitalPinToInterrupt(MPUint), dmpDataReady, RISING);
		mpuIntStatus = mpu.getIntStatus();
		dmpReady = true;
		packetSize = mpu.dmpGetFIFOPacketSize();
	}
	else {
		data.err = "Gyro fucked up: " + devStatus;
	}
}

void loop() {
	// reading ze senzorů
	data.DHTtemp = dht.readTemperature();
	data.DHThum = dht.readHumidity();
	data.BMPtemp = bmp.readTemperature();
	data.BMPpress = (bmp.readPressure()/100.00) + bmpKorekce;
	data.BMPalt = bmp.readAltitude();

	// GYRO + ACCEL
	if (!dmpReady) return; // pokud se něco posralo tak nic nezkoušet
	// přečtení packetu z FIFO
	if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
		// gyro
		mpu.dmpGetQuaternion(&q, fifoBuffer);
		mpu.dmpGetGravity(&gravity, &q);
		mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
		data.yaw = ypr[0] * 180 / M_PI;
		data.pitch = ypr[1] * 180 / M_PI;
		data.roll = ypr[2] * 180 / M_PI;
	}

	Transfer.sendDatum(data);
	delay(1000);
}