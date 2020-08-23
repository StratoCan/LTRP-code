// openCanSat code
// www.stratocan.eu

#include <Arduino.h>
#include <SerialTransfer.h>
#include <RFM69.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BAUDRATE	115200
#define D13LED		42 // D13 LED
#define MLED			69 // MLED

// RFM69
#define networkID			0
#define nodeID				1
#define toNodeID			2
#define FREQUENCY			RF69_433MHZ
#define FREQUENCYSPEC	433000000
#define RFM69pin			43
#define RFM69int			9

// BME280
#define BME280addr		(0x77)
#define seaLevelPress	1013.25

SerialTransfer Transfer;
Adafruit_BME280 bme;
RFM69 radio(RFM69pin, RFM69int, true);

struct STRUCT {
	float DHTtemp;
	float DHThum;
	float BMPtemp;
	float BMPpress;
	float BMPalt;
	float yaw;
	float pitch;
	float roll;
	String err;
} data;

struct STRUCT {
	int id;
	float DHTtemp;
	float DHThum;
	float BMPtemp;
	float BMPpress;
	float BMPalt;
	float BMEtemp;
	float BMEpress;
	float BMEalt;
	float yaw;
	float pitch;
	float roll;
} dataOut;

int id = 1;

void printData() {
	SerialUSB.print("DHTtemp: ");
	SerialUSB.println(data.DHTtemp);
	SerialUSB.print("DHThum: ");
	SerialUSB.println(data.DHThum);
	SerialUSB.print("BMPtemp: ");
	SerialUSB.println(data.BMPtemp);
	SerialUSB.print("BMPpress: ");
	SerialUSB.println(data.BMPpress);
	SerialUSB.print("BMPalt: ");
	SerialUSB.println(data.BMPalt);
	SerialUSB.print("yaw: ");
	SerialUSB.println(data.yaw);
	SerialUSB.print("pitch: ");
	SerialUSB.println(data.pitch);
	SerialUSB.print("roll: ");
	SerialUSB.println(data.roll);
	SerialUSB.println(data.err);
}

void resetDataOut() {
	dataOut.DHTtemp = 0;
	dataOut.DHThum = 0;
	dataOut.BMPtemp = 0;
	dataOut.BMPpress = 0;
	dataOut.BMPalt = 0;
	dataOut.BMEtemp = 0;
	dataOut.BMEpress = 0;
	dataOut.BMEalt = 0;
	dataOut.BMEhum = 0;
	dataOut.yaw = 0;
	dataOut.pitch = 0;
	dataOut.roll = 0;
}

void readData() {
	dataOut.DHTtemp = data.DHTtemp;
	dataOut.DHThum = data.DHThum;
	dataOut.BMPtemp = data.BMPtemp;
	dataOut.BMPpress = data.BMPpress;
	dataOut.BMPalt = data.BMPalt;
	dataOut.BMEtemp = bme.readTemperature();
	dataOut.BMEpress = bme.readPressure() / 100.0F;
	dataOut.BMEalt = bme.readAltitude(seaLevelPress);
	dataOut.BMEhum = bme.readHumidity();
	dataOut.yaw = data.yaw;
	dataOut.pitch = data.pitch;
	dataOut.roll = data.roll;
}

void setup() {
	pinMode(D13LED, OUTPUT);
	SerialUSB.begin(BAUDRATE);
	Serial5.begin(BAUDRATE);
	Transfer.begin(Serial5);
	bme.begin(BME280addr);
	radio.initialize(FREQUENCY, nodeID, networkID);
	radio.setFrequency(FREQUENCYSPEC);
	radio.setHighPower(true);
}

void loop() {
	resetDataOut();
	if(Transfer.available()) {
		dataOut.id = id;
		Transfer.rxObj(data);
		readData();
	}
	digitalWrite(D13LED, LOW);

	delay(1000);
}

/*
//SEQUENCES

void startUpSequence(){

}
void fallSequence(){

}

void groundSequence(){

}

//SEQUENCES END

//ROUTINES AND SUBSEQUENCES

void chuteDetach(){
	//subsequence
}

void standUp(){
	//stand up routine used to lift the LTRP
}

void hiberanate(){
	//hibernate routine to conservate battery capacity
}

//ROUTINES AND SUBSEQUENCES END

*/