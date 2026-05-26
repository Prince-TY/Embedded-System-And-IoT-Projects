#include <WiFi.h>
#include <Wire.h>
#include <DHT.h>
#include <LiquidCrystal_PCF8574.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// ========= WIFI =========
#define WIFI_SSID ""
#define WIFI_PASS ""

// ========= MQTT =========
#define AIO_SERVER ""
#define AIO_SERVERPORT 1883
#define AIO_USERNAME ""
#define AIO_KEY ""

// ========= HARDWARE =========
#define DHTPIN 23
#define DHTTYPE DHT11
#define RELAY_PIN 13

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_PCF8574 lcd(0x3F); // change if needed

// ========= VARIABLES =========
float temperature = 0;
float humidity = 0;
bool fanOn = false;

// ========= MQTT =========
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish tempFeed =
  Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/");

// ========= MQTT CONNECT =========
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

// ========= SETUP =========
void setup() {
  Serial.begin(115200);

  dht.begin();

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Fan OFF

  // I2C start
  Wire.begin(21, 22);

  // LCD init (DIFFERENT from old library)
  lcd.begin(16, 2);
  lcd.setBacklight(255);

  lcd.setCursor(0, 0);
  lcd.print("Temp System");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  delay(2000);
  lcd.clear();

  // WiFi
  Serial.print("Connecting WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
}

// ========= LOOP =========
void loop() {

  // MQTT maintain
  MQTT_connect();
  mqtt.processPackets(1000);
  mqtt.ping();

  // ===== READ SENSOR =====
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Sensor Error");
    lcd.clear();
    lcd.print("Sensor Error");
    delay(2000);
    return;
  }

  // ===== CONTROL LOGIC =====
  if (temperature >= 28) {
    digitalWrite(RELAY_PIN, LOW);  // ON
    fanOn = true;
    Serial.println("Fan ON");
  } else {
    digitalWrite(RELAY_PIN, HIGH); // OFF
    fanOn = false;
    Serial.println("Fan OFF");
  }

  // ===== SEND TO CLOUD =====
  tempFeed.publish(temperature);

  // ===== SERIAL OUTPUT =====
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" C | Hum: ");
  Serial.print(humidity);
  Serial.println(" %");

  // ===== LCD DISPLAY =====
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print("C ");

  lcd.print("H:");
  lcd.print(humidity);
  lcd.print("% ");

  lcd.setCursor(0, 1);
  if (fanOn) {
    lcd.print("Fan ON   ");
  } else {
    lcd.print("Fan OFF  ");
  }

  delay(2000);
}