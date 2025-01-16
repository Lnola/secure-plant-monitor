#include <Ticker.h>

const int photoresistorPin = A0;

Ticker photoresistorTicker;

void read_photoresistor() {
  int val = analogRead(photoresistorPin);
  Serial.print("Photoresistor value: ");
  Serial.println(val);
}

void setup() {
  Serial.begin(9600);
  photoresistorTicker.attach(0.1, read_photoresistor);
}

void loop() {
}
