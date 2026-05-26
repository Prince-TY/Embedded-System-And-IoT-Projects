#include <Keypad.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'C', '0', '=', '+'} 
};

byte rowPins[ROWS] = {A0, A1, A2, A3}; 
byte colPins[COLS] = {9, 8, 7, 6}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// Variables to store user inputs
String inputString = "";
long firstNumber = 0;
long secondNumber = 0;
char op = ' ';
byte step = 0; // 0: First Number, 1: Operator, 2: Second Number, 3: Result

void setup() {
  lcd.begin(16, 2);
  resetCalculator();
}

void loop() {
  char key = customKeypad.getKey();
  
  if (key) {
    // Always clear if ON/C is pressed
    if (key == 'C') {
      resetCalculator();
      return;
    }

    if (step == 0) { // Asking for First Number
      if (key >= '0' && key <= '9') {
        inputString += key;
        lcd.setCursor(0, 1);
        lcd.print(inputString);
      } else if (inputString.length() > 0 && (key == '+' || key == '-' || key == '*' || key == '/')) {
        // If an operator is pressed, save first number and move directly to operator step
        firstNumber = inputString.toInt();
        inputString = "";
        op = key;
        step = 2; // Jump directly to asking for second number
        lcd.clear();
        lcd.print("2nd Number:");
      }
    } 
    else if (step == 2) { // Asking for Second Number
      if (key >= '0' && key <= '9') {
        inputString += key;
        lcd.setCursor(0, 1);
        lcd.print(inputString);
      } else if (key == '=' && inputString.length() > 0) {
        secondNumber = inputString.toInt();
        inputString = "";
        calculateAndShowResult();
      }
    }
  }
}

void resetCalculator() {
  inputString = "";
  firstNumber = 0;
  secondNumber = 0;
  op = ' ';
  step = 0;
  lcd.clear();
  lcd.print("1st Number:");
}

void calculateAndShowResult() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(firstNumber);
  lcd.print(op);
  lcd.print(secondNumber);
  lcd.print("=");

  lcd.setCursor(0, 1);
  
  // Switch case for operations
  switch (op) {
    case '+':
      lcd.print(firstNumber + secondNumber);
      break;
    case '-':
      lcd.print(firstNumber - secondNumber);
      break;
    case '*':
      lcd.print(firstNumber * secondNumber);
      break;
    case '/':
      if (secondNumber == 0) {
        lcd.print("Error: Div by 0");
      } else {
        lcd.print((float)firstNumber / secondNumber);
      }
      break;
    default:
      lcd.print("Error");
      break;
  }
  
  step = 3; // Finished calculation. Press 'C' to start again.
}
