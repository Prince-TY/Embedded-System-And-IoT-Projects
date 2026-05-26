#include<LiquidCrystal_I2C.h>
#include<Wire.h>
#define Trig 4
#define Echo 2
long duration;
int distance;
LiquidCrystal_I2C lcd(0x27,2,16);
const int led1=5;
const int led2=6;
const int led3=7;
void setup() {
  Serial.begin(115200);
lcd.init();
lcd.backlight();
lcd.setCursor(0,4);
lcd.print("System Ready!!!");
delay(5000);
lcd.clear();
pinMode(Trig,OUTPUT);
pinMode(Echo,INPUT);
pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
pinMode(led3,OUTPUT);
}

void loop() {
digitalWrite(Trig,0);
delayMicroseconds(2);
digitalWrite(Trig,1);
delayMicroseconds(10);
digitalWrite(Trig,0);

duration=pulseIn(Echo,1);
distance=(duration*0.0343)/2;

if(distance<=2){
  lcd.setCursor(0,0);
  lcd.print("You are in:");
 lcd.print(distance);
  lcd.print("cm");
  digitalWrite(led1,1);
  Serial.print("Distance:");
  Serial.print(distance);
  Serial.println("cm");
   delay(1000);
}
if(distance==3||distance<=4){
  lcd.setCursor(0,0);
  lcd.print("You are in:");
  lcd.print(distance);
  lcd.print("cm");
  digitalWrite(led2,1);
   Serial.print("Distance:");
  Serial.print(distance);
  Serial.println("cm");
   delay(1000);
}
if(distance==5||distance<=6){
  lcd.setCursor(0,0);
   lcd.print("You are in:");
  lcd.print(distance);
  lcd.print("cm");
  digitalWrite(led3,1);
   Serial.print("Distance:");
  Serial.print(distance);
  Serial.println("cm");
  delay(1000);
}

}  