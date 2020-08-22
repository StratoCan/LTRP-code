// LTRP Code
// www.stratocan.eu

#include <Arduino.h>
#include <Wire.h>
#include <SerialTransfer.h>

#define BAUDRATE 115200
#define OCSADDR 9 // openCanSat address

SerialTransfer Transfer;

int builtInLed = 13;

struct STRUCT {
	long randomak;
} data;

void setup() {
	pinMode(builtInLed, OUTPUT);

	Serial.begin(BAUDRATE);
	Transfer.begin(Serial);

	// wait for serial
	//while(!Serial);
}

void loop() {
	data.randomak = random(10);

	Transfer.sendDatum(data);
	delay(500);
}