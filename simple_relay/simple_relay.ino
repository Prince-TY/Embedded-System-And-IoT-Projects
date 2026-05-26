#include <LiquidCrystal.h>
#include<Wire.h>
LiquidCrystal lcd(12,11,5,4,3,2);

int relay=10;

void setup() {
  // put your setup code here, to run once:
pinMode(relay,HIGH);
lcd.begin(16,2);
//lcd.backlight();
lcd.setCursor(0,0);
lcd.print("Relay");
delay(5000);
lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(relay,HIGH);
delay(2000);
lcd.setCursor(0,0);
lcd.print("LAMP ON");
delay(2000);
lcd.clear();
digitalWrite(relay,LOW);
delay(2000);
lcd.setCursor(0,1);
lcd.print("LAMP OFF");
delay(2000);
lcd.clear();
}
