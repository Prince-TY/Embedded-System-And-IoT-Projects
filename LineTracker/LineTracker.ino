#include<LiquidCrystal_I2C.h>
#include<Wire.h>

#define rightTracker 4
#define leftTracker 5

LiquidCrystal_I2C lcd(0x20,16,2);
int redled = 6;
int buzzer = 7;
int greenled=8;

void setup() {
 Serial.begin(9600);

 pinMode(redled,OUTPUT);
 pinMode(buzzer,OUTPUT);
 pinMode(rightTracker,INPUT_PULLUP);
 pinMode(leftTracker,INPUT_PULLUP);
 pinMode(greenled,OUTPUT);

 lcd.init();
 lcd.backlight();
 lcd.setCursor(0,0);
 lcd.print("Parking Controller!!");
 delay(1500);
 lcd.clear();

 Serial.print("Parking Controller System!!!!");

}

void loop() {

 bool right = digitalRead(rightTracker);
 bool left = digitalRead(leftTracker);


 if(right == HIGH && left == HIGH){
  Serial.print("Car Is In Correct Lot!!!");
  lcd.setCursor(0,0);
  lcd.print("Correct Parking!");
  
  digitalWrite(greenled,HIGH);
  delay(1000);
  digitalWrite(greenled,0);
  
 }else{ 

  Serial.print("Incorrect Parking!!!");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Incorrect Parking");
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Try Again !!");

  tone(buzzer,300,1000);
  digitalWrite(redled,HIGH);
  delay(1000);
  digitalWrite(buzzer,0);
  digitalWrite(redled,0);

 
 }
}
