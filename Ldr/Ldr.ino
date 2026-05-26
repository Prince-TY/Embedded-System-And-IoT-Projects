const int ldrPin = A0;     // LDR connected to analog pin
const int ledPin = 13;     // LED pin

int ldrValue = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  ldrValue = analogRead(ldrPin);

  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // threshold control
  if (ldrValue < 500) {
    digitalWrite(ledPin, HIGH);  // dark → LED ON
  } else {
    digitalWrite(ledPin, LOW);   // bright → LED OFF
  }

  delay(200);
}