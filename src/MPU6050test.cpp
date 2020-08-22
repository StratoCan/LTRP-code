// MPU6050 test
// www.stratocan.eu

#include <Arduino.h>
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050_6Axis_MotionApps_V6_12.h>

#define BAUDRATE 115200
#define MPUint 3

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
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 gy;         // [x, y, z]            gyro sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
	mpuInterrupt = true;
}

void setup() {
	pinMode(MPUint, INPUT);

	Serial.begin(BAUDRATE);
	Wire.begin();
	Wire.setClock(400000);
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
		Serial.print("GYRO ERROR: ");
		Serial.println(devStatus);
	}
}

void loop() {
	// GYRO + ACCEL
	if (!dmpReady) return; // pokud se něco posralo tak nic nezkoušet
	// přečtení packetu z FIFO
	if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
		// gyro
		mpu.dmpGetQuaternion(&q, fifoBuffer);
		mpu.dmpGetGravity(&gravity, &q);
		mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
		Serial.print("yaw: ");
		Serial.println(ypr[0] * 180 / M_PI);
		Serial.print("pitch: ");
		Serial.println(ypr[1] * 180 / M_PI);
		Serial.print("roll: ");
		Serial.println(ypr[2] * 180 / M_PI);
		// accel
		mpu.dmpGetQuaternion(&q, fifoBuffer);
		mpu.dmpGetAccel(&aa, fifoBuffer);
		mpu.dmpGetGravity(&gravity, &q);
		mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
		mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
		Serial.print("aaX: ");
		Serial.println(aaWorld.x);
		Serial.print("aaY: ");
		Serial.println(aaWorld.y);
		Serial.print("aaZ: ");
		Serial.println(aaWorld.z);
	}
	delay(1000);
}