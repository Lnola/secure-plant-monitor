#include <Ticker.h>
#include "dhtnew.h"

#define DHTPIN D7
#define PHOTORESISTOR_PIN A0

DHTNEW dht(DHTPIN);

Ticker photoresistorTicker;

void read_dht() {
  if (millis() - dht.lastRead() < 2000) return;
  if (!dht.read()) {
    Serial.println("[DHT]: Sensor not ready or failed to read");
    Serial.println(dht.getTemperature());
    Serial.println(dht.getHumidity());
    return;
  }
  float temperature = dht.getTemperature();
  float humidity = dht.getHumidity();

  Serial.print("[DHT]: Temperature: ");
  Serial.print(temperature);
  Serial.print("°C, Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
}

void read_photoresistor() {
  int value = analogRead(PHOTORESISTOR_PIN);
  Serial.print("[Photoresistor]: Photoresistor value: ");
  Serial.println(value);
}

void setup() {
  Serial.begin(9600);

  // photoresistorTicker.attach(1, read_photoresistor);
}

void loop() {
  read_dht();
}
