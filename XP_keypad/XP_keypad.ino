#include <Servo.h>

#include<Keypad.h>
//#include<Servo.h>
#include<LiquidCrystal_I2C.h>
#include<Wire.h>

LiquidCrystal_I2C lcd(0x20,16,2);
//LiquidCrystal_I2C lcd=LiquidCrystal_I2C(0x20,16,2);
Servo pservo;
String Ppassword="54321";
String PIN="";

#define redled 10
#define greenled 11
#define buzzer 1

const byte ROWS=4;
const byte COLS=3;

char key[ROWS][COLS] = {
                        {'1','2','3'},
                        {'4','5','6'},
                        {'7','8','9'},
                        {'*','0','#'}
};

const byte rowPins[ROWS]={9,8,7,6};
const byte colPins[COLS]={5,4,3};

Keypad xkeypad= Keypad(makeKeymap(key),colPins,rowPins,ROWS,COLS);
//Keypad xkeypad(makeKeypad(key),colPins,rowPins,ROWS,COLS);
 //void checkPassword();
void setup() {
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pservo.attach(12);
  pservo.write(0);

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Smart lock");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter PIN:");
  
  Serial.print("Enter Password:");
}

void loop() {
  char xkey = xkeypad.getKey();
  if(xkey){
    if(xkey =='#'){
      checkPassword();
    }else if(xkey == '*'){
     PIN ="";

    }else{
      PIN += xkey;
      Serial.print("*");
      lcd.setCursor(PIN.length() -1, 1);
      lcd.print("*");
    }
    

  }}


  void checkPassword(){

    if(PIN == Ppassword){

      Serial.print("Correct Password");Serial.print("Access Allowed");
      lcd.setCursor(0,1);
      lcd.print("Granted!!");
       digitalWrite(greenled,HIGH);
       pservo.write(90);
      delay(5000);
    }
    else{

      Serial.print("Incorrect Password");Serial.print("Access Denied");
      lcd.setCursor(0,1);
      lcd.print("Denied!!");
      digitalWrite(redled,HIGH);
      digitalWrite(buzzer,HIGH);
      pservo.write(0);

    }
    
  }
  void resetSystem(){
     PIN ="";
     Serial.print("Enter Password");

      lcd.setCursor(0,1);
      lcd.print("Enter PIN");
      delay(1000);
  }
    
    
