// baseStation code
// www.stratocan.eu

#include <Arduino.h>
#include <Wire.h>
#include <RFM69.h>
#include <OcsStorage.h>
#include <Ucglib.h>

#define BAUDRATE	115200
#define D13LED		42 // D13 LED
#define MLED			69 // MLED
// BUTTONS
#define BUTTON_1 5
#define BUTTON_2 4
#define BUTTON_3 3

// RFM69
#define networkID			0
#define nodeID				2
#define FREQUENCY			RF69_433MHZ
#define FREQUENCYSPEC	433300000
#define RFM69pin			43
#define RFM69int			9

bool isRadioOk = true;
uint8_t screenNum = 1;

RFM69 radio(RFM69pin, RFM69int, true);
Ucglib_ST7735_18x128x160_HWSPI ucg(6, 7, -1);
OcsGraphics ocsDesign(ucg);
OcsStorage ocsData(ocsDesign);
OcsStorage::message income;

void setup() {
	Serial.begin(BAUDRATE);
	// screen
	ucg.begin(UCG_FONT_MODE_TRANSPARENT);
	ucg.clearScreen();
	ocsDesign.drawBackground();
  ocsDesign.drawHomescreen();
	// Buttons
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(BUTTON_3, INPUT);
	// RFM69
	if(!radio.initialize(FREQUENCY, nodeID, networkID)) {
		isRadioOk = false;
	}
	else {
		radio.setFrequency(FREQUENCYSPEC);
		radio.setHighPower(true); // Always use this for RFM69HW
	}
}

void loop() {
	int button1 = digitalRead(BUTTON_1);
	int button2 = digitalRead(BUTTON_2);
	int button3 = digitalRead(BUTTON_3);

	if(button1 == LOW) {
		if(screenNum == 1) {
			screenNum = 0;
			ocsDesign.drawLeftScreen();
			delay(300);
		}
		else if(screenNum == 2) {
			screenNum = 1;
			ocsDesign.drawHomescreen();
			delay(300);
		}
	}
	else if(button2 == LOW) {
		if(screenNum != 1) {
			screenNum = 1;
			ocsDesign.drawHomescreen();
			delay(300);
		}
	}
	else if(button3 == LOW) {
		if(screenNum == 1) {
			screenNum = 2;
			ocsDesign.drawRightScreen();
			delay(300);
		}
		else if(screenNum == 0) {
			screenNum = 1;
			ocsDesign.drawHomescreen();
			delay(300);
		}
	}

	// radio
	if (radio.receiveDone()) {
	income = *(OcsStorage::message*)radio.DATA;
	ocsData.Update(income, screenNum);
	delay(300);
	}
}