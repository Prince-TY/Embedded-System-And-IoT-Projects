#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// WiFi
#define WIFI_SSID ""
#define WIFI_PASS ""

// Adafruit IO
#define AIO_SERVER      ""
#define AIO_SERVERPORT  8883
#define AIO_USERNAME    ""
#define AIO_KEY         "My key"

// LED pin
#define LED_PIN 2
WiFiClientSecure client;

// MQTT
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// ⚠️ FIXED: feed name MUST be lowercase if created that way
Adafruit_MQTT_Subscribe ledFeed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/feedname");

void MQTT_connect() {
  int8_t ret;

  if (mqtt.connected()) return;

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;

  while ((ret = mqtt.connect()) != 0) {

    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying in 2 seconds...");

    mqtt.disconnect();
    delay(2000);

    retries--;
    if (retries == 0) {
      Serial.println("MQTT FAILED ❌");
      return;
    }
  }

  Serial.println("MQTT Connected! ✅");
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // 🔥 VERY IMPORTANT FOR SSL
  client.setInsecure();  

  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected ✅");

  mqtt.subscribe(&ledFeed);
}

void loop() {

  MQTT_connect();

  mqtt.processPackets(500);
  mqtt.ping();

 Adafruit_MQTT_Subscribe *subscription;

while ((subscription = mqtt.readSubscription(1000))) {

  if (subscription == &ledFeed) {

    // 🔥 FIX: properly read and clean the value
    String value = String((char*)ledFeed.lastread);
    value.trim();          // remove spaces, \n, \r
    value.toUpperCase();   // normalize

    Serial.print("Received: [");
    Serial.print(value);
    Serial.println("]");

    if (value == "ON") {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED STATUS: ON 🔆");
    }
    else if (value == "OFF") {
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED STATUS: OFF ⚫");
    }
    else {
      Serial.println("Unknown command");
    }
  }
}}