#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
#define LDR_PIN A0
#define led 8
#define Treshold 500
int lightLevel = 0;
void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0); 
  lcd.begin(16,2);
 // lcd.backlight();
  lcd.print("LDR Lamp System");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
 // Serial.begin(9600);
}

void loop() {
  lightLevel = analogRead(LDR_PIN);
  lcd.setCursor(0,0);
  lcd.print("Light: ");
  lcd.print(lightLevel);
  if (lightLevel < Treshold) {
    digitalWrite(led, 1); 
    lcd.setCursor(0, 1);
    lcd.print("Lamp: ON ");
  } else {
    digitalWrite(led, 0); 
    lcd.setCursor(0, 1);
    lcd.print("Lamp: OFF");
  }
  delay(1000);
}
