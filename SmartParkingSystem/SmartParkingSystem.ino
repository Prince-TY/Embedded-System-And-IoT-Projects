#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>

#define EnIR 4
#define ExIR 5
#define GreenEn 6
#define GreenEx 7
#define Max 5

bool previous = HIGH;
bool last = HIGH;
int counter = 0; 

LiquidCrystal_I2C lcd(0x20, 16, 2);
Servo entranceServo;
Servo exitServo;

void setup() {
  Serial.begin(9600);

  entranceServo.attach(8);
  entranceServo.write(0);
  exitServo.attach(9);
  exitServo.write(0);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Smart Parking SYS");
  delay(1500);
  lcd.clear();

  pinMode(GreenEn, OUTPUT);
  pinMode(GreenEx, OUTPUT);
  pinMode(EnIR, INPUT);
  pinMode(ExIR, INPUT);

  Serial.println("Smart Parking System Ready!");
}

void loop() {
  entranceCounter();
  exitCounter();
}

void entranceCounter() {
  bool entrance = digitalRead(EnIR);

  if (entrance == LOW && previous == HIGH) {
    if (counter <= Max) {
      counter++;
      Serial.print("Number of Cars Inside: ");
      Serial.println(counter);
      Serial.println("Spaces available:" + Max-counter);
      
      digitalWrite(GreenEn, HIGH);
      entranceServo.write(90);
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Car detected");
      lcd.setCursor(0, 1);
      lcd.print("Cars Inside: ");
      lcd.print(counter);
    } else {
      Serial.println("No Spaces Available");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Lot Full!");
    }
    delay(2000); 
    digitalWrite(GreenEn, LOW);
    entranceServo.write(0);
  }
  previous = entrance; 
}
void exitCounter() {
  bool exit = digitalRead(ExIR);

  if (exit == LOW && last == HIGH) {
    if (counter > 0) {
      counter--;
      Serial.print("Number of Cars Inside: ");
      Serial.println(counter);
      Serial.println("Spaces available:" + Max-counter);
      
      digitalWrite(GreenEx, HIGH);
      exitServo.write(90);
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Car detected");
      lcd.setCursor(0, 1);
      lcd.print("Cars Inside: ");
      lcd.print(counter);
    }
    delay(2000);
    digitalWrite(GreenEn, LOW);
    exitServo.write(0);
  }
  last = exit;
}
