String Name = "";
int Age;
String WDYL = "";
String WDYS = "";
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("OUR USER CREDENTIALS:");
  Serial.println("Enter your Name:");
  while (Name == "") {
  if (Serial.available() > 0) {
    Name = Serial.readStringUntil('\n');
    }
  }
  Serial.println("Enter your Age:");
  while (Age == 0) {
if (Serial.available() > 0) {
 Age = Serial.parseInt();
   }
  }
  Serial.println("Where do you live?");
  while (WDYL == "") {
  if (Serial.available() > 0) {
  WDYL = Serial.readStringUntil('\n');
  }
  }
  Serial.println("Where do you study?");
  while (WDYS == "") {
if (Serial.available() > 0) {
WDYS = Serial.readStringUntil('\n');

}}
}
void loop() {
  Serial.println("\n Entered Credentials");
  Serial.println("Name: " + Name);
  Serial.println("Age: ");
  Serial.println( Age);
  Serial.println("Lives in: " + WDYL);
  Serial.println("Studies at: " + WDYS);

  delay(5000);
}