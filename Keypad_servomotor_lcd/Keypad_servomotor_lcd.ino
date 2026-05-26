#include <Keypad.h>          
#include <Servo.h>           
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// --- KEYPAD SETUP ---
const byte ROWS = 4;         
const byte COLS = 3;         // Changed from 4 columns to 3 columns

const int Relay = 11;

// 4x3 keypad layout
char keys[ROWS][COLS] = {    
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {5, 4, 3, 2}; 
byte colPins[COLS] = {8, 7, 6};    // Only 3 column pins now

// Create keypad object
Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x20,20,4);

// --- SERVO & VARIABLES ---
Servo doorServo;

String masterPassword = "1234";
String userAttempt = "";
int led=12;
int buzzer=13;
void setup() {
  Serial.begin(9600);

  doorServo.attach(10);
  doorServo.write(0);
  pinMode(led,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(Relay, OUTPUT);

  Serial.println("--- DOOR SECURITY SYSTEM ---");
  Serial.println("Please Enter Password to Open:");

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Keypad Security");

  delay(3000);

  lcd.clear();
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Enter PASS:");
 // delay(2000);
 // lcd.clear();

  char pressedKey = customKeypad.getKey();

  if (pressedKey) {

    if (pressedKey == '#') {

      checkPassword();

    } 
    else if (pressedKey == '*') {

      userAttempt = "";

      Serial.println("\nCleared. Try again:");

    } 
    else {

      userAttempt += pressedKey;

      Serial.print("*");
      lcd.setCursor(14,0);
      lcd.print(userAttempt);
    }
  }
}

void checkPassword() {

  if (userAttempt == masterPassword) {

    Serial.println("\n[ACCESS GRANTED]");
    Serial.println("Opening Door...");

    digitalWrite(Relay, 1);
    delay(3000);
    digitalWrite(Relay,0);
    lcd.setCursor(0,0);


    lcd.print("Password:Correct !");
    lcd.setCursor(0,1);
    lcd.print("Door State:On");
    lcd.setCursor(0,2);
    lcd.print("Lamp State:On");
    delay(5000);

    doorServo.write(90);
    delay(2000);
    doorServo.write(0);
    delay(2000);
    lcd.clear();
    doorServo.write(0);

    Serial.println("Door Locked.");
    Serial.println("\nEnter Password for next user:");
    digitalWrite(led,HIGH);
    delay(3000);
    digitalWrite(led,0);
  } 
  else {

    Serial.println("\n[ACCESS DENIED]");
    Serial.println("Wrong code. Try again:");
      doorServo.write(90);
      delay(2000);
       doorServo.write(0);
       delay(2000);
    lcd.setCursor(0,0);
    lcd.print("Password:Incorrect !");
    lcd.setCursor(0,1);
    lcd.print("Door State:Off");
    lcd.setCursor(0,2);
    lcd.print("Lamp State:Off");
    delay(5000);
    lcd.clear();
digitalWrite(buzzer,HIGH);
delay(4000);
digitalWrite(buzzer,0);
  }

  userAttempt = "";
}