#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define Relay 12
#include<Servo.h>
LiquidCrystal_I2C lcd(0x27,16,2);
Servo pservo;
String Ppassword = "54321";
String PIN = "";
int wrongCount=0;
bool blocked=false;

#define redled 10
#define greenled 11
#define buzzer 13

const byte ROWS = 4;
const byte COLS = 4;

char key[ROWS][COLS] = {

  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

const byte rowPins[ROWS] = {A0,A1,7,6};
const byte colPins[COLS] = {5,4,3,2};

Keypad xkeypad = Keypad(makeKeymap(key), rowPins, colPins, ROWS, COLS);

void setup() {
  pservo.attach(9);
  pservo.write(0);

  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(Relay,OUTPUT);

  digitalWrite(Relay,1);// NC OFF

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Smart Lock");

  delay(3000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter PIN:");

  Serial.println("Enter Password:");
}

void loop() {

  char xkey = xkeypad.getKey();

  if(xkey){

   // Serial.println(xkey);

    if(xkey == '#'){

      checkPassword();
    }

    else if(xkey == '*'){
      PIN = "";
      lcd.clear();
      lcd.print("Cleared");
      delay(1000);
      lcd.clear();
      lcd.print("Enter PIN:");
    }

    else{
      PIN += xkey;
      Serial.print("*");
      lcd.setCursor(PIN.length()-1,1);
      lcd.print("*");
    }
  }
}

void checkPassword(){
  lcd.clear();
  if(PIN == Ppassword){

    Serial.println("Correct Password");
    Serial.println("Access Allowed");
    pservo.write(90);
    delay(5000);
    pservo.write(0);

    lcd.setCursor(0,0);
    lcd.print("Access Granted");
    delay(5000);
    lcd.clear();
    lcd.print("Enter PIN:");
   // lcd.clear();
    digitalWrite(greenled, HIGH);
    digitalWrite(Relay,0);
    delay(5000);
    digitalWrite(Relay,1);
    digitalWrite(greenled, LOW);
    wrongCount=0;
  }

  else{
       wrongCount++;
      digitalWrite(Relay,1);

  if(wrongCount >=3){
  lcd.print("Wrong PIN");
  lcd.clear();
  lcd.print("System Blocked");
  Serial.print("System Blocked For Six Seconds");
  tone(buzzer,500,1000);
  digitalWrite(redled,1);
  pservo.write(0);
  delay(6000);
  digitalWrite(redled,0);
  digitalWrite(Relay,1);
 }else{

    Serial.println("Incorrect Password");
    Serial.println("Access Denied");

    lcd.setCursor(0,0);
    lcd.print("Access Denied");

    digitalWrite(redled, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(3000);

    digitalWrite(redled, LOW);
    digitalWrite(buzzer, LOW);
  }
  PIN = "";
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter PIN:");
}}
