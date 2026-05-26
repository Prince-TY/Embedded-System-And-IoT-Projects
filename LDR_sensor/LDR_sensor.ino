//#include <LiquidCrystal_I2C.h>
#include<LiquidCrystal.h>
//#include<Wire.h>
LiquidCrystal lcd(12,11,5,4,3,2);
//LiquidCrystal_I2C lcd(0*27,16,2);
#define flame 8
#define Relaypin 8
int ONTreshold=400.0;
int OFFTreshold=600.0;
void setup() {
  // put your setup code here, to run once:
pinMode(flame,INPUT);
pinMode(Relaypin,OUTPUT);
lcd.begin(16,2);
//lcd.init();
//lcd.backlight();
lcd.begin(16,2);
lcd.setCursor(0,0);
lcd.print("FLAME");
delay(5000);
lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
float LDRvalues=analogRead(A2);
if(isnan(LDRvalues)){
  lcd.setCursor(0,0);
  lcd.print("an error troubleshoot");
 delay(5000);
  lcd.clear();
}else if(LDRvalues<400.0){
  lcd.setCursor(0,0);
  lcd.print("Light level:");
  lcd.print(LDRvalues);
  lcd.setCursor(0,1);
  lcd.print("NIGHT");
  //lcd.clear();
  digitalWrite(5,HIGH);
}else if(LDRvalues>600.0){
 lcd.setCursor(0,0);
  lcd.print("Light level:");
  lcd.print(LDRvalues);
  lcd.setCursor(0,1);
  lcd.print("DAY");
  //lcd.clear();
  digitalWrite(5,LOW); 
}else{

lcd.clear();
}
}
