int x;
int y;
char t;
int output;
void setup(){
Serial.begin(9600);
delay(1000);
while(Serial.available()>0){
Serial.read();
}
Serial.println("Enter first number:");
while (Serial.available() == 0){}
x = Serial.parseInt();
delay(200);

 while(Serial.available() > 0){
  Serial.read(); 
 }
Serial.println("Enter second number:");
while(Serial.available() == 0){}
y = Serial.parseInt();
delay(200);

while (Serial.available()> 0) {
 Serial.read();  
  }
 Serial.println("Enter operator like(+, -, *, /):");
while (Serial.available() == 0) {}
 t = Serial.read();

Serial.print("You entered:");
Serial.print(x);
Serial.print("And");
Serial.println(y);
Serial.print("Operator: ");
Serial.println(t);
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
  Serial.print("Result = ");
  Serial.println(output);
}
void loop() {
}