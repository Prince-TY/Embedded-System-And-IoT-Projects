int x;
int y;
char t;
void setup() {
Serial.begin(115200);
while(x==0){
if(Serial.available()>0){
  x=Serial.parseInt();
}
}
while(y==0){
if(Serial.available()>0){
  y=Serial.parseInt();
}
}
  if(Serial.available()>0){
    t=Serial.read();
    if(t=='\n'||t=='\r'){
    return;
  }
  }
  Serial.print("Integers entered: ");
  Serial.print(x);
  Serial.print(" and ");
  Serial.println(y);

}

void loop() {
}
