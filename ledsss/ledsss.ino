// ===== 10 LEDs ON ONE ARDUINO PIN =====
// All LEDs connected in parallel to pin 8
// (each LED must have its own resistor)

int leds[] = {8,8,8,8,8,8,8,8,8};

void setup() {

  // Configure all array elements as OUTPUT
  for(int i = 0; i < 8; i++) {

    pinMode(leds[i], OUTPUT);
  }
}

void loop() {

  // ===== TURN ALL LEDs ON =====
  for(int i = 0; i < 10; i++) {

    digitalWrite(leds[i], HIGH);
  }

  delay(200);

  // ===== TURN ALL LEDs OFF =====
  for(int i = 0; i < 8; i++) {

    digitalWrite(leds[i], LOW);
  }

  delay(200);
}