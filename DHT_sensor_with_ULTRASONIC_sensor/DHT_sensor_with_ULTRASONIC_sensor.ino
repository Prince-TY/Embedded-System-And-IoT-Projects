#include<DHT.h>
#define DHTPIN 6
#define DHTTYPE DHT11
#define TRIG-PIN 3
#define ECHO-PIN 4
#define LED-TEMP 5
#define LED-HUMID 6
#define LED-WATER 7
#define MAX-TANK-HEIGHT 50cm
DHT dht(DHTPIN,DHTTYPE)
void setup() {
  // put your setup code here, to run once:
serial.begin(9600);
dht.begin();
pinMode(TRIG-PIN,OUTPUT);
pinMode(ECHO-PIN,INPUT);
pinMode(LED-TEMP,OUTPUT);
pinMode(LED-HUMID,OUTPUT);
pinMode(LED-WATER,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
float temperature=dht.readTemperature();
float humidity=dht.readHumidity();
if(isnan Temperature){
serial.println("failed to read from DHT sensor");
return;}
float waterlevel=measure water level();
serial.print("temperature:");
serial.print("temperature");
serial.println("c");
serial.print("humidity:");
serial.print("humidity");
serial.print("%");
serial.print("water level:");
serial.print("water level");
serial.println("cm");
float measure water level();
digitalWrite(TRIG-PIN,LOW);
delay microsecond(2);
digitalWrite(TRIG-PIN,HIGH);
delay microsecond(10);
digitalWrite(TRIG-PIN,LOW);
long duration=pulseIn(ECHO-PIN,HIGH);
float distance=duration*o.034/2;
return MAX-TANK-HEIGHT-DISTANCE;}
void check alerts(float temp,float hum,float water level){
 if(temp>35){
digitalWrite(LED-TEMP,HIGH);
serial.println("alert:HIGH temperature:")}
else{
digitalWrite(LED-TEMP,LOW);}
if(hum<30){
digitalWrite(LED-HUMID,HIGH);
serial.println("alert,low humidity");
   }
else{
digitalWrite(LED-HUMID,LOW);
float critical water level=MAX-TANK-HEIGHT*0.2}
if(water level<critical water level){
digitalWrite(LED-WATER,HIGH);
serial.println("alert:low water level");}
else{
digitalWrite(LED-WATER,LOW);}}
