#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

int Num1 = 0;
int Num2 = 0;

LiquidCrystal_I2C lcd(0x20,16,2);

const byte ROWS = 4;
const byte COLS = 3;

 char key[ROWS][COLS] = {

  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'','0','=','+'}
};

const byte rowPins[ROWS] = {9,8,7,6};
const byte colPins[COLS] = {5,4,3,2};

Keypad xkeypad = Keypad(makeKeymap(key), rowPins, colPins, ROWS, COLS);





void setup() {
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Smart Calc");

  delay(3000);

  lcd.clear();
 /* lcd.setCursor(0,0);
  lcd.print("Enter PIN:");

  Serial.println("Enter Password:");
}*/

}

void loop() {
 int number = xkeypad.getKey();
 if(number){
   if(number == '='){
   getResult();
}else if(number =='on'){
  lcd.clear();
  lcd.print("Try Again");
  Num1 =0;
  Num2 =0; 
}}}

void getResult(){

switch (t) {
case '+':
 output = x + y;
break;

 case '-':
output = x - y;
 break;

case '*':
output = x * y;
break;

case '/':
 if (y != 0)
 output = x / y;
else {
 Serial.println("Error: Division by zero");
return;
}
break;

default: 
 Serial.println("Invalid operator!");
return;
  }
}
