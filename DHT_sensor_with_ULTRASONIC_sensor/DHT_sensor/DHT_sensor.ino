
#include <DHT.h>

#define DHTPIN 6
#define DHTTYPE DHT11
int LED2 = 3;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(LED2, OUTPUT);
}

void loop() {
  float t = dht.readTemperature(); // Added parentheses here!
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h)) { // It's a good idea to check if the readings are valid!
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Temperature:");
    Serial.println(t);
    Serial.print("Humidity:");
    Serial.println(h);

    if (t > 40) {
      digitalWrite(LED2, HIGH);
      delay(1000);
    } else {
      digitalWrite(LED2, LOW);
    }
  }
  delay(2000);
}
