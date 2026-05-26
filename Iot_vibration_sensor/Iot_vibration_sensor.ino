
#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/********* WIFI SETTINGS *********/
#define WIFI_SSID       ""
#define WIFI_PASS       ""
#define AIO_SERVER      ""
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    ""
#define AIO_KEY         ""
/********* PINS *********/
#define VIB_PIN 22     // Vibration sensor
#define LED_PIN 2      // LED
WiFiClient client;
/********* MQTT CLIENT *********/
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
/********* FEEDS *********/
// Publish vibration data
Adafruit_MQTT_Publish vibration = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/");

// Subscribe LED control
Adafruit_MQTT_Subscribe ledFeed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/");

/********* FUNCTION *********/
void MQTT_connect();

/********* SETUP *********/
void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  pinMode(VIB_PIN, INPUT);

  Serial.println("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("p");
  }

  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Subscribe to LED feed
  mqtt.subscribe(&ledFeed);
}

/********* LOOP *********/
void loop() {

  MQTT_connect();

  /********* RECEIVE LED COMMAND *********/
  Adafruit_MQTT_Subscribe *subscription;

  while ((subscription = mqtt.readSubscription(1000))) {
    if (subscription == &ledFeed) {

      String msg = (char *)ledFeed.lastread;

      Serial.print("LED Command: ");
      Serial.println(msg);

      if (msg == "1") {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("LED ON");
      } else {
        digitalWrite(LED_PIN, LOW);
        Serial.println("LED OFF");
      }
    }
  }
  /********* READ VIBRATION SENSOR *********/
long vibrationState = digitalRead(VIB_PIN);
  Serial.print("Vibration State: ");
  Serial.println(vibrationState);
  /********* SEND DATA TO ADAFRUIT *********/
  if (!vibration.publish(vibrationState)) {
    Serial.println("Failed to send data!");
  } else {
    Serial.println("Data sent to Adafruit IO ✔");
  }

  delay(2000); // every 2 seconds
}
/********* MQTT CONNECTION *********/
void MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) return;
  Serial.print("Connecting to MQTT... ");
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying in 5 seconds...");
    mqtt.disconnect();
    delay(5000);
  }
  Serial.println("Connected to Adafruit IO!");
}
