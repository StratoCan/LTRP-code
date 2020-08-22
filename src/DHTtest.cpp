// DHT test
// www.stratocan.eu

#include <Arduino.h>
#include <DHT.h>

#define BAUDRATE 115200
#define DHTpin 5

DHT dht(DHTpin, DHT11);

void setup() {
	Serial.begin(BAUDRATE);
	dht.begin();
}

void loop() {
	Serial.print("temp: ");
	Serial.println(dht.readTemperature());
	Serial.print("hum: ");
	Serial.println(dht.readHumidity());
	delay(1000);
}