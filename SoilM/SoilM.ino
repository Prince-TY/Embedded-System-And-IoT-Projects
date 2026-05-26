#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define Relay 3
#define Soil A2
const int wet = 300;
const int dry = 800;
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  Serial.begin(9600);
  pinMode(Relay, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Soil Monitor");
  delay(2000);
  lcd.clear();
  digitalWrite(Relay, LOW);
}
void loop() {
  int values = analogRead(Soil);
  int SoilPercent = map(values, wet, dry, 100, 0);
  SoilPercent = constrain(SoilPercent, 0, 100);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moisture:" + SoilPercent); lcd.print("%");
  if (SoilPercent < 90) {
    digitalWrite(Relay, HIGH);
    lcd.setCursor(10, 1);
    lcd.print("ON ");
  } else if(SoilPercent == 100||SoilPercent > 100){
    digitalWrite(Relay, LOW);
    lcd.setCursor(10, 1);
    lcd.print("OFF");
  }
  Serial.print("SoilPercent: ");
  Serial.print(SoilPercent);
  Serial.println("%");
  delay(1000);
}