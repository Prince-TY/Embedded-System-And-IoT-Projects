#include<LiquidCrystal_I2C.h>
#include<Wire.h>
#define PIR 6
#define Relay 5

LiquidCrystal_I2C lcd(0x27,16,2);
void setup() {
Serial.begin(9600);

lcd.init();
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("Mot Detector");
delay(2000);
lcd.clear();

pinMode(Relay,OUTPUT);
pinMode(PIR,INPUT);

}

void loop() {
 bool motion=digitalRead(PIR);

 /*if(motion != HIGH || motion != 0){
  lcd.setCursor(0,0);
  lcd.print("An Error!!!");
  return;
 }else{
*/
  if(motion == HIGH){
    digitalWrite(Relay,HIGH);
    delay(3000);
    lcd.setCursor(0,0);
    Serial.println("Motion detected");
    lcd.print("Motion Detected");
    lcd.setCursor(0,1);
    lcd.print("Lamp ON");

  }else{
    digitalWrite(Relay,LOW);
    delay(3000);
    lcd.setCursor(0,0);
    lcd.print("Not Detected"); 
     Serial.println(" No Motion detected");
    lcd.setCursor(0,1);
    lcd.print("Lamp OFF");
  }
 
delay(1000);
}
