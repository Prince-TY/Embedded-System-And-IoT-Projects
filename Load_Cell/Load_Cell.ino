#include <HX711.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ===== HX711 PINS =====
#define DT  3
#define SCK 2

// ===== LEDs & BUZZER =====
#define redLed    8
#define greenLed  9
#define buzzer    10

// ===== CREATE OBJECTS =====
HX711 scale;
LiquidCrystal_I2C lcd(0x27,16,2);

// ===== CALIBRATION FACTOR =====
float calibration_factor = -2280.0;

void setup() {

  Serial.begin(9600);

  // ===== OUTPUT PINS =====
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // ===== LCD START =====
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("LOAD CELL SYS");
  delay(2000);
  lcd.clear();

  // ===== HX711 START =====
  scale.begin(DT, SCK);

  // ===== SET CALIBRATION =====
  scale.set_scale(calibration_factor);

  // ===== RESET SCALE =====
  scale.tare();

  lcd.setCursor(0,0);
  lcd.print("System Ready");
  delay(2000);
  lcd.clear();
}

void loop() {

  // ===== READ WEIGHT =====
  float weight = scale.get_units(10);

  // ===== SERIAL MONITOR =====
  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" KG");

  // ===== LCD DISPLAY =====
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Weight:");

  lcd.setCursor(0,1);
  lcd.print(weight);
  lcd.print(" KG");

  // ===== WEIGHT CONDITIONS =====

  // NO LOAD
  if(weight < 1){

    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, LOW);
    digitalWrite(buzzer, LOW);
  }

  // NORMAL LOAD
  else if(weight >= 1 && weight < 5){

    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
    digitalWrite(buzzer, LOW);
  }

  // OVERLOAD
  else if(weight >= 5){

    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);

    tone(buzzer, 1000);
    delay(500);
    noTone(buzzer);
  }

  delay(500);
}