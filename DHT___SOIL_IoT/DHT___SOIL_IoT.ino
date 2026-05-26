#include "WiFi.h"
#include "DHT.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// ----------------------
// WiFi Settings
// ----------------------
#define wifiName     ""
#define wifiPassword ""    

// ----------------------
// Adafruit IO Settings
// ----------------------
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT   1883
#define AIO_USERNAME    ""
#define AIO_KEY         ""

// ----------------------
// Sensor Pins
// ----------------------
#define DHTPIN  4
#define DHTTYPE DHT22       // Use DHT11 if needed: DHT11
#define SOIL_PIN 34         // Analog pin for soil sensor

DHT dht(DHTPIN, DHTTYPE);

// ----------------------
// WiFi + MQTT Client Setup
// ----------------------
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Feeds (Adafruit IO)
Adafruit_MQTT_Publish tempFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/");
Adafruit_MQTT_Publish humFeed  = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/");
Adafruit_MQTT_Publish soilFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/");

// ----------------------
// Reconnect to MQTT Server
// ----------------------
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

  Serial.println("MQTT Connected!");
}

// ----------------------
// Setup
// ----------------------
void setup() {
  Serial.begin(115200);
  dht.begin();

  // Connect to WiFi
  Serial.print("Connecting to WiFi");
  WiFi.begin(wifiName, wifiPassword);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Try!");
    delay(500);
  }
  Serial.println("\nWiFi connected!");
}

// ----------------------
// Main Loop
// ----------------------
void loop() {
  MQTT_connect();  // Ensure connection

  // Read DHT Sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read Soil Moisture (0–4095)
  int soilData = analogRead(SOIL_PIN);

  // Convert soil to % (optional)
long soilPercent = map(soilData, 0, 4095, 0, 100);

  // Print values locally
  Serial.print("Temp: "); Serial.print(temperature);
  Serial.print("°C  Humidity: "); Serial.print(humidity);
  Serial.print("%  Soil: "); Serial.print(soilPercent);
  Serial.println("%");

  // Publish to Adafruit IO
  tempFeed.publish(temperature);
  humFeed.publish(humidity);
 // soilFeed.publish(soilPercent);
  soilFeed.publish(soilPercent);

  delay(1000);  // Send every 1 second
}
