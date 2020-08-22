// openCanSat code
// www.stratocan.eu

#include <Arduino.h>
#include <Wire.h>
#include <SerialTransfer.h>

#define BAUDRATE 115200

SerialTransfer Transfer;

struct STRUCT {
	long randomak;
} data;

void setup() {
	SerialUSB.begin(BAUDRATE);
	Serial5.begin(BAUDRATE);
	Transfer.begin(Serial5);
}

void loop() {
	if(Transfer.available()) {
		Transfer.rxObj(data);
		SerialUSB.println(data.randomak);
	}
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