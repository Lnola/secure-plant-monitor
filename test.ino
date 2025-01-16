#include <Ticker.h>
#include "dhtnew.h"

#define DHTPIN D7
#define PHOTORESISTOR_PIN A0

DHTNEW dht(DHTPIN);

Ticker dhtTicker;
Ticker photoresistorTicker;

volatile bool dhtReady = false;
volatile bool photoresistorReady = false;

void set_dht_ready() {
  dhtReady = true;
}

void set_photoresistor_ready() {
  photoresistorReady = true;
}

void read_dht() {
  if (!dht.read()) {
    Serial.println("[DHT]: Sensor not ready or failed to read");
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

  dhtTicker.attach(1, set_dht_ready);
  photoresistorTicker.attach(1, set_photoresistor_ready);
}

void loop() {
  if (dhtReady) {
    dhtReady = false;
    read_dht();
  }

  if (photoresistorReady) {
    photoresistorReady = false;
    read_photoresistor();
  }
}
