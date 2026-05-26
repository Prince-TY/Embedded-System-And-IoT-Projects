#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x20, 16, 2);

#define irSensor 2
#define led 3
#define buzzer 4
#define relay 5

int CountUpItem = 0;
bool previousState = HIGH;

void setup() {
  pinMode(irSensor, INPUT);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("IR Sensor System Started");

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("IR SENSOR");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM READY");
  delay(1000);
  lcd.clear();
}

void loop() {
  bool sensorState = digitalRead(irSensor);


  if (sensorState == LOW && previousState == HIGH) {
    CountUpItem++;
    
    
    digitalWrite(led, HIGH);
    tone(buzzer, 300);
    digitalWrite(relay, HIGH);

    Serial.print("Object Detected. Items: "); 
    Serial.println(CountUpItem);
  
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Item Detected");
    lcd.setCursor(0, 1);
    lcd.print("Items: "); 
    lcd.print(CountUpItem);
    
    delay(200); 
  } 
 
  else if (sensorState == HIGH && previousState == LOW) {
  
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
    digitalWrite(relay, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("NO OBJECT");
    lcd.setCursor(0, 1);
    lcd.print("FOUND");
    
    delay(50); 
  }
  previousState = sensorState;
}
