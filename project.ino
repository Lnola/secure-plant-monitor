#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

const char* WIFI_SSID = "Ferrotel";
const char* WIFI_PASSWORD = "ferrotel2018";
const char* MQTT_SERVER = "broker.hivemq.com";
const int MQTT_PORT = 8883;

WiFiClientSecure espClient;
PubSubClient client(espClient);

void setup_wifi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP8266Client")) {
      Serial.println("MQTT connected");
    } else {
      Serial.print("MQTT connection failed, rc=");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  // WiFi setup
  setup_wifi();
  espClient.setInsecure();  // Disable certificate verification (insecure, for testing purposes only)

  // MQTT setup
  client.setServer(MQTT_SERVER, MQTT_PORT);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();
}
