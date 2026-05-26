const int trigPin = 7;
const int echoPin =9;
const int LED1=3;
const int LED2=5;
const int buzzer=6;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
   pinMode(LED1, OUTPUT);
   pinMode(LED2,OUTPUT);
   pinMode(buzzer,OUTPUT);
}

void loop() {
  long duration; 
  float distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343 )/ 2;
  if(distance<30){
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,HIGH);
    delay(100);
   
  }
  else if(distance>30){
    digitalWrite(buzzer,HIGH);
    delay(100);
  }
  else{
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(buzzer,LOW);
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(100);
}
