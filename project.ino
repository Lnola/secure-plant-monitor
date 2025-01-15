#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

const char* WIFI_SSID = "Ferrotel";
const char* WIFI_PASSWORD = "ferrotel2018";
const char* MQTT_SERVER = "broker.hivemq.com";
const int MQTT_PORT = 8883;

const char* TEST_TOPIC = "test/topic";

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

// TODO: remove if there is no actuator implementation
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message on ");
  Serial.print(topic);
  Serial.print(": ");
  for (int i = 0; i < length; i++) Serial.print((char)payload[i]);
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP8266Client")) {
      client.subscribe(TEST_TOPIC);  // TODO: remove if there is no actuator implementation
      Serial.println("MQTT connected");
    } else {
      Serial.print("MQTT connection failed, rc=");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

// TODO: remove if there is no actuator implementation
void check_connection() {
  static unsigned long lastMsg = 0;
  static unsigned long now = millis();
  if (now - last > 2000) {
    last = millis();
    client.publish(TEST_TOPIC, "Hello from ESP8266!");
    Serial.println("Message sent: Hello from ESP8266!");
  }
}

void setup() {
  Serial.begin(115200);

  // WiFi setup
  setup_wifi();
  espClient.setInsecure();  // Disable certificate verification (insecure, for testing purposes only)

  // MQTT setup
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  check_connection()  // TODO: remove if there is no actuator implementation
}
