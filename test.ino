#include <Ticker.h>
#include "dhtnew.h"

#define DHTPIN D7
#define PHOTORESISTOR_PIN A0

DHTNEW dht(DHTPIN);

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
  int value = analogRead(PHOTORESISTOR_PIN);
  Serial.print("Photoresistor value: ");
  Serial.println(value);
}

void setup() {
  Serial.begin(9600);

  dhtTicker.attach(1, read_dht);
  photoresistorTicker.attach(1, read_photoresistor);
}

void loop() {
}
