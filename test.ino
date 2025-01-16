#include <Ticker.h>
#include "dhtnew.h"

#define DHT_PIN D7
#define PHOTORESISTOR_PIN A0
#define FLAME_PIN D5

DHTNEW dht(DHT_PIN);

Ticker dhtTicker;
Ticker photoresistorTicker;
Ticker flameTicker;

volatile bool dhtReady = false;
volatile bool photoresistorReady = false;
volatile bool flameReady = false;

void set_dht_ready() {
  dhtReady = true;
}

void set_photoresistor_ready() {
  photoresistorReady = true;
}

void set_flame_ready() {
  flameReady = true;
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

  dhtReady = false;
}

void read_photoresistor() {
  int value = analogRead(PHOTORESISTOR_PIN);
  Serial.print("[Photoresistor]: Value: ");
  Serial.println(value);

  photoresistorReady = false;
}

void read_flame() {
  int value = digitalRead(FLAME_PIN);
  Serial.print("[Flame]: Value: ");
  Serial.println(value);

  flameReady = false;
}

void setup() {
  Serial.begin(9600);

  pinMode(FLAME_PIN, INPUT);

  dhtTicker.attach(1, set_dht_ready);
  photoresistorTicker.attach(1, set_photoresistor_ready);
  flameTicker.attach(1, set_flame_ready);
}

void loop() {
  if (dhtReady) read_dht();
  if (photoresistorReady) read_photoresistor();
  if (flameReady) read_flame();
}