#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

LiquidCrystal_I2C lcd(0x27, 16, 2); 

#define WIFI_SSID       ""
#define WIFI_PASS       ""

#define AIO_SERVER      ""
#define AIO_SERVERPORT  
#define AIO_USERNAME    ""
#define AIO_KEY         ""

#define SOIL_PIN 34
#define RELAY_PIN 23

int dryValue = 4095;
int wetValue = 1500;

long soilValue = 0;
long moisturePercent = 0;

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish soilFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/");
 

void MQTT_connect() {
  int8_t ret;

  if (mqtt.connected()) return;

  Serial.print("Connecting MQTT... ");

  while ((ret = mqtt.connect()) != 0) {
    Serial.println("Failed");
    mqtt.disconnect();
    delay(2000);
  }

  Serial.println("Connected!");
}


void setup() {
  Serial.begin(115200);

  
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // OFF

 
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Soil System");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  delay(2000);
  lcd.clear();

  Serial.print("Connecting WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
}


void loop() {
  MQTT_connect();

  mqtt.processPackets(1000);
  mqtt.ping();

  
  soilValue = analogRead(SOIL_PIN);

  moisturePercent = map(soilValue, dryValue, wetValue, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);

  Serial.print("Moisture: ");
  Serial.print(moisturePercent);
  Serial.println("%");

  soilFeed.publish(moisturePercent);// Publish to Adafruit io IOT Platform

  bool pumpOn;

  if (moisturePercent < 50) {
    digitalWrite(RELAY_PIN, LOW);  // ON
    pumpOn = true;
    Serial.println("Pump ON");
  } else if(moisturePercent >50) {
    digitalWrite(RELAY_PIN, HIGH); // OFF
    pumpOn = false;
    Serial.println("Pump OFF");
  }

  lcd.setCursor(0, 0);
  lcd.print("Moisture: ");
  lcd.print(moisturePercent);
  lcd.print("%   ");

  lcd.setCursor(0, 1);
  if (pumpOn) {
    lcd.print("Watering...   ");
  } else {
    lcd.print("Pump Stopped  ");
  }

  delay(2000);
}