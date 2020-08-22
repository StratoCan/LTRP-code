// openCanSat code
// www.stratocan.eu

#include <Arduino.h>
#include <SerialTransfer.h>

#define BAUDRATE 115200

SerialTransfer Transfer;

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
	SerialUSB.print("aaX: ");
	SerialUSB.println(data.aaX);
	SerialUSB.print("aaY: ");
	SerialUSB.println(data.aaY);
	SerialUSB.print("aaZ: ");
	SerialUSB.println(data.aaZ);
	SerialUSB.println(data.err);
}

void setup() {
	SerialUSB.begin(BAUDRATE);
	Serial5.begin(BAUDRATE);
	Transfer.begin(Serial5);
}

void loop() {
	if(Transfer.available()) {
		Transfer.rxObj(data);
		printData();
	}

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