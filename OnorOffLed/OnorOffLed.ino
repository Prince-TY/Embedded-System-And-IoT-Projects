int led1=2;
int led2=3;
int led3=4;
String state="";
String ONState="ON";
String OFFState="OFF";
String onState="on";
String offState="off";
String OnState="On";
String OffState="Off";
String oNString="oN";
String oFFString="oFF";
String kwatsa="kwatsa";
String kuzimya="kuzimya";
String Dig="1";
String dig="0";
int Delay=300;
void setup() {
Serial.begin(9600);
//pinMode(led,OUTPUT);
digitalWrite(led1,0);
   digitalWrite(led2,0);
   digitalWrite(led3,0);
}
void loop() {
Serial.println("Enter state:(ON/OFF/kwatsa/kuzimya/Logic HIGH=1/Logic LOW=0)");
while(Serial.available()==0){}
state=Serial.readStringUntil('\n');
if(state==ONState||state==onState||state==OnState||state==oNString||state==kwatsa || state==Dig){
   digitalWrite(led1,1);
   digitalWrite(led2,1);
   digitalWrite(led3,1);
}else if(state==OFFState||state==offState||state==OffState||state==oFFString||state==kuzimya || state == dig){
 digitalWrite(led1,0);
   digitalWrite(led2,0);
   digitalWrite(led3,0);
   /*for(int y=0;y<3;y++){
  digitalWrite(led,1);
delay(Delay);
 digitalWrite(led,0);
delay(Delay);
  }*/
}else{
  Serial.print("Incorrect Inputs");
}
delay(Delay);
}
