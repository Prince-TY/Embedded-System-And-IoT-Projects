#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 7        
#define DHTTYPE DHT11    
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define RELAY_PIN 8

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Relay off initially

  lcd.begin(16, 2);
  lcd.print("Humidity Ctrl");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  
  dht.begin();
  delay(2000);
  lcd.clear();
}

void loop() {
  float h = dht.readHumidity();

  // Error handling: sensor not responding
  if (isnan(h)) {
    lcd.clear();
    lcd.print("Sensor Error!");
    delay(2000);
    return;
  }

  // Limit humidity display to 0–100%
  if (h > 100) h = 100;
  if (h < 0) h = 0;

  // Display humidity
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.print((int)h);   // display integer value only
  lcd.print("%");

  // Control fan relay based on humidity range
  if (h < 60) {
    digitalWrite(RELAY_PIN, LOW); // Fan ON
    lcd.setCursor(0, 1);
    lcd.print("Fan: ON ");
  } 
  else if (h > 75) {
    digitalWrite(RELAY_PIN, HIGH); // Fan OFF
    lcd.setCursor(0, 1);
    lcd.print("Fan: OFF");
  } 
  else {
    lcd.setCursor(0, 1);
    lcd.print("Fan: HOLD");
  }

  delay(2000);
}
