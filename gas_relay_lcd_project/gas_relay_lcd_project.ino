#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD setup (change 0x27 if needed)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin definitions
#define OXYGEN_SENSOR A0
#define RELAY_PIN 7

// Air quality calibration values
#define Good_Quality 200
#define Polluted_Air 1023

int Air_Quality = 0;
int Oxygen_Percentage = 0;

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Relay OFF initially (active LOW)

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);

  lcd.setCursor(0, 0);
  lcd.print("Greenhouse Sys");
  delay(2000);
  lcd.clear();
}

void loop() {

  // Read sensor value
  Air_Quality = analogRead(OXYGEN_SENSOR);

  // Convert to percentage using map()
  Oxygen_Percentage = map(Air_Quality, Good_Quality, Polluted_Air, 0, 100);

  // Limit values between 0–100
  Oxygen_Percentage = constrain(Oxygen_Percentage, 0, 100);

  // Display values on Serial Monitor
  Serial.print("Raw Value: ");
  Serial.print(Air_Quality);
  Serial.print(" | Oxygen %: ");
  Serial.println(Oxygen_Percentage);

  // LCD Display
  lcd.setCursor(0, 0);
  lcd.print("O2 Level: ");
  lcd.print(Oxygen_Percentage);
  lcd.print("%   ");

  // CONTROL LOGIC
  if (Oxygen_Percentage < 5) {
    // LOW OXYGEN → TURN FAN ON
    digitalWrite(RELAY_PIN, LOW); // Relay ON
    lcd.setCursor(0, 1);
    lcd.print("Fan ON  (LOW O2) ");

  } else if (Oxygen_Percentage > 21) {
    // HIGH OXYGEN → TURN FAN OFF
    digitalWrite(RELAY_PIN, HIGH); // Relay OFF
    lcd.setCursor(0, 1);
    lcd.print("Fan OFF (HIGH O2)");

  } else {
    // NORMAL RANGE
    digitalWrite(RELAY_PIN, HIGH); // Fan OFF
    lcd.setCursor(0, 1);
    lcd.print("O2 Normal        ");
  }

  delay(1000);
}