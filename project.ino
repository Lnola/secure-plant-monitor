#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <LittleFS.h>
#include <time.h>

const bool SILENCE_SENSOR_LOGS = 1;
const char* TEMPERATURE_TOPIC = "lnola/sensor/temperature";
const char* HUMIDITY_TOPIC = "lnola/sensor/humidity";
const char* PHOTORESISTOR_TOPIC = "lnola/sensor/light-level";
const char* FLAME_TOPIC = "lnola/sensor/flame";

const char* WIFI_SSID = "Ferrotel";
const char* WIFI_PASSWORD = "ferrotel2018";
const char* MQTT_SERVER = "188.245.235.247";
const int MQTT_PORT = 8883;

WiFiClientSecure wifiClient;
PubSubClient mqtt(wifiClient);

void setup_wifi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
}

void configure_time() {
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  Serial.print("Waiting for time sync...");
  while (time(nullptr) < 100000) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nTime synchronized!");
}

void load_certificates() {
  if (!LittleFS.begin()) {
    Serial.println("Failed to mount LittleFS.");
    return;
  }

  File caCertFile = LittleFS.open("/ca.crt", "r");
  if (!caCertFile) {
    Serial.println("Failed to open CA certificate file.");
    return;
  }
  String caCert = caCertFile.readString();
  caCertFile.close();
  wifiClient.setTrustAnchors(new BearSSL::X509List(caCert.c_str()));

  File clientCertFile = LittleFS.open("/client.crt", "r");
  if (!clientCertFile) {
    Serial.println("Failed to open client certificate file.");
    return;
  }
  String clientCert = clientCertFile.readString();
  clientCertFile.close();

  File clientKeyFile = LittleFS.open("/client.key", "r");
  if (!clientKeyFile) {
    Serial.println("Failed to open client private key file.");
    return;
  }
  String clientKey = clientKeyFile.readString();
  clientKeyFile.close();

  wifiClient.setClientRSACert(new BearSSL::X509List(clientCert.c_str()),
                              new BearSSL::PrivateKey(clientKey.c_str()));

  Serial.println("Certificates loaded successfully.");
}

void reconnect() {
  while (!mqtt.connected()) {
    if (mqtt.connect("ESP8266Client")) {
      Serial.println("MQTT connected");
    } else {
      Serial.print("MQTT connection failed, rc=");
      Serial.println(mqtt.state());
      delay(5000);
    }
  }
}

#include <Ticker.h>
#include "dhtnew.h"

#define DHT_PIN D7
#define PHOTORESISTOR_PIN A0
#define FLAME_PIN D5
#define BUZZER_PIN D6

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

  if (!SILENCE_SENSOR_LOGS) {
    Serial.print("[DHT]: Temperature: ");
    Serial.print(temperature);
    Serial.print("°C, Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
  }

  char temperaturePayload[10];
  char humidityPayload[10];
  snprintf(temperaturePayload, sizeof(temperaturePayload), "%.0f", temperature);
  snprintf(humidityPayload, sizeof(humidityPayload), "%.0f", humidity);

  mqtt.publish(TEMPERATURE_TOPIC, temperaturePayload);
  mqtt.publish(HUMIDITY_TOPIC, humidityPayload);

  dhtReady = false;
}

void read_photoresistor() {
  int value = analogRead(PHOTORESISTOR_PIN);
  if (!SILENCE_SENSOR_LOGS) {
    Serial.print("[Photoresistor]: Value: ");
    Serial.println(value);
  }

  char payload[10];
  snprintf(payload, sizeof(payload), "%d", value);
  mqtt.publish(PHOTORESISTOR_TOPIC, payload);

  photoresistorReady = false;
}

void read_flame() {
  int value = digitalRead(FLAME_PIN);
  if (!SILENCE_SENSOR_LOGS) {
    Serial.print("[Flame]: Value: ");
    Serial.println(value);
  }

  if (value == HIGH) {
    tone(BUZZER_PIN, 1000);
  } else {
    noTone(BUZZER_PIN);
  }

  char payload[10];
  snprintf(payload, sizeof(payload), "%d", value);
  mqtt.publish(FLAME_TOPIC, payload);

  flameReady = false;
}

void setup() {
  Serial.begin(115200);

  // WiFi setup
  setup_wifi();
  configure_time();
  load_certificates();

  // MQTT setup
  mqtt.setServer(MQTT_SERVER, MQTT_PORT);

  // SENSOR PIN setup
  pinMode(FLAME_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // SENSOR TICKER setup
  dhtTicker.attach(2, set_dht_ready);
  photoresistorTicker.attach(0.5, set_photoresistor_ready);
  flameTicker.attach(0.5, set_flame_ready);
}

void loop() {
  if (!mqtt.connected()) reconnect();
  mqtt.loop();

  if (dhtReady) read_dht();
  if (photoresistorReady) read_photoresistor();
  if (flameReady) read_flame();
}
