#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pins
#define gasSensor A0
#define alarmPin 8

// Threshold (adjust this!)
int gasThreshold = 400;

void setup() {
  pinMode(alarmPin, OUTPUT);
  digitalWrite(alarmPin, LOW);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
}

void loop() {
  int gasValue = analogRead(A0);

  // Display on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gas Level:");

  lcd.setCursor(0, 1);
  lcd.print(gasValue);

  // Check gas level
  if (gasValue > gasThreshold) {
    digitalWrite(alarmPin, HIGH); // Alarm ON

    lcd.setCursor(10, 1);
    lcd.print("ALERT!");
  } else {
    digitalWrite(alarmPin, LOW); // Alarm OFF

    lcd.setCursor(10, 1);
    lcd.print("SAFE ");
  }

  // Debug
  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  delay(1000);
}