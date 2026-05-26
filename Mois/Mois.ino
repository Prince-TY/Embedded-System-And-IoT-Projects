#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Set the LCD address to 0x20 or 0x27 for a 16x2 display
LiquidCrystal_I2C lcd(0x20, 16, 2);

#define SOIL_ANALOG_PIN A0

void setup() {
  Serial.begin(9600);
  
  // Initialize the I2C LCD screen
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("SOIL MONITOR");
  lcd.setCursor(0, 1);
  lcd.print("INITIALIZING...");
  delay(1500);
  lcd.clear();
}

void loop() {
  // Read raw value (0 to 1023)
  int rawValue = analogRead(SOIL_ANALOG_PIN);

  // Map and constrain values to get an accurate 0% - 100% reading
  int moisturePercent = map(rawValue, 1023, 0, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);

  // Print data to the Serial Monitor
  Serial.print("Moisture: ");
  Serial.print(moisturePercent);
  Serial.println("%");

  // Display data on the I2C LCD
  lcd.setCursor(0, 0);
  lcd.print("Soil Moisture: ");
  
  lcd.setCursor(0, 1);
  lcd.print(moisturePercent);
  lcd.print("%   "); // Extra spaces clear old characters when numbers shift from 3 digits to 2

  delay(500); // Smooth updates twice per second
}
