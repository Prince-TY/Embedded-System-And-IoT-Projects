#define rightTracker 4
#define leftTracker 5

void setup() {

  Serial.begin(9600);

  pinMode(rightTracker, INPUT_PULLUP);

  pinMode(leftTracker, INPUT_PULLUP);
}

void loop() {

  int right = digitalRead(rightTracker);

  int left = digitalRead(leftTracker);

  Serial.print("RIGHT = ");
  Serial.print(right);

  Serial.print("   LEFT = ");
  Serial.println(left);

  delay(500);
}