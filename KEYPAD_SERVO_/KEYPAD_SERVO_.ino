#include <Keypad.h>          // Library to manage the 4x4 keypad matrix
#include <Servo.h>           // Library to control the servo motor movement
#include<LiquidCrystal_I2C.h>
#include<Wire.h>
// --- KEYPAD SETUP ---
const byte ROWS = 4;         // Four horizontal rows on the keypad
const byte COLS = 4;         // Four vertical columns on the keypad
const int Relay=11;
char keys[ROWS][COLS] = {    // Map the physical buttons to characters
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; // Connect keypad Row pins 1-4 to Arduino D9-D6
byte colPins[COLS] = {5, 4, 3, 2}; // Connect keypad Col pins 5-8 to Arduino D5-D2

// Create the keypad object using the settings above
Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x20,16,2);
// --- SERVO & VARIABLES ---
Servo doorServo;                   // Create a name for our servo motor
String masterPassword = "1234";    // The secret code to open the door
String userAttempt = "";           // String to hold the numbers being typed

void setup() {
  Serial.begin(9600);              // Start communication with the computer screen
  doorServo.attach(10);            // Connect the Servo signal wire to Pin 10
  doorServo.write(0);              // Set door to 0 degrees (Closed position)
  pinMode(Relay,OUTPUT);
  Serial.println("--- DOOR SECURITY SYSTEM ---"); // Header message
  Serial.println("Please Enter Password to Open:"); // Instruction for the user

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Keypad Security");
  delay(3000);
  lcd.clear();
}

void loop() {
  char pressedKey = customKeypad.getKey(); // Check if any button was pressed

  if (pressedKey) {                // If a button was actually touched...
    
    if (pressedKey == '#') {       // If the '#' key (Enter) is pressed
      checkPassword();             // Jump to the function that checks the code
    } 
    else if (pressedKey == '*') {  // If the '*' key (Cancel) is pressed
      userAttempt = "";            // Wipe the current typing memory
      Serial.println("\nCleared. Try again:"); // Tell user it was reset
    } 
    else {                         // If any number (0-9) or letter was pressed
      userAttempt += pressedKey;   // Add that character to our attempt string
      Serial.print("*");           // Show a star instead of the number for privacy
    }
  }
}

void checkPassword() {             // This function runs when '#' is pressed
  if (userAttempt == masterPassword) { // Compare what was typed to the secret code
    Serial.println("\n[ACCESS GRANTED]"); // Print success message
    Serial.println("Opening Door...");    // Tell user the door is moving
    digitalWrite(Relay,1);
    doorServo.write(87);           // Move servo to 87 degrees (Open)
    delay(5000);                   // Keep door open for 5 seconds
    
    doorServo.write(0);            // Move servo back to 0 degrees (Close)
    Serial.println("Door Locked."); // Tell user it is secure again
    Serial.println("\nEnter Password for next user:"); // Reset for next person
  } 
  else {                           // If the typed code does NOT match
    Serial.println("\n[ACCESS DENIED]");   // Print error message
    Serial.println("Wrong code. Try again:"); // Ask to try again
     digitalWrite(Relay,1);
  }
  
  userAttempt = "";                // Clear the memory for the next attempt
}
