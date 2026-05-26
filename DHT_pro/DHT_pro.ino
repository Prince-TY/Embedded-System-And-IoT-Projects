#include <LiquidCrystal.h>
#include <DHT.h>
#define DHTPIN 7        
#define DHTTYPE DHT11    
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define RELAY_PIN 8
void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); 

  lcd.begin(16, 2);
  lcd.print("Humidity Ctrl");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  
  dht.begin();
  delay(2000);
}

void loop() {
  float h = dht.readHumidity();
  //float t = dht.readTemperature();

  // Check if readings are valid
  if (isnan(h)) {
    lcd.clear();
    lcd.print("Sensor Error!");
    delay(2000);
  }

  // Display readings
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hum: ");
  lcd.print(h);
  lcd.print("%");

 // lcd.setCursor(0, 1);
  //lcd.print("Temp: ");
  //lcd.print(t);
  //lcd.print((char)223); // Degree symbol
  //lcd.print("C");

  if (h < 60) {
    digitalWrite(RELAY_PIN, HIGH); // Turn fan ON
  } else if (h > 75) {
    digitalWrite(RELAY_PIN, LOW); // Turn fan OFF
  }

  delay(2000); 
}
