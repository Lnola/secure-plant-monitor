#include <Ticker.h>
#include "dhtnew.h"

#define DHTPIN D7

DHTNEW dht(DHTPIN);

const int photoresistorPin = A0;

Ticker dhtTicker;
Ticker photoresistorTicker;


void read_dht() {
  if (dht.read()) {
    float temperature = dht.getTemperature();
    float humidity = dht.getHumidity();

    Serial.print("[DHT]: Temperature: ");
    Serial.print(temperature);
    Serial.print("°C, Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
  } else {
    Serial.println("[DHT]: Sensor not ready or failed to read");
  }
}

void read_photoresistor() {
  int val = analogRead(photoresistorPin);
  Serial.print("Photoresistor value: ");
  Serial.println(val);
}

void setup() {
  Serial.begin(9600);

  dhtTicker.attach(1, read_dht);
  photoresistorTicker.attach(0.1, read_photoresistor);
}

void loop() {
}
