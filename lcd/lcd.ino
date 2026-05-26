
#include<LiquidCrystal.h>
#include<Wire.h>
LiquidCrystal lcd(12,11,5,4,3,2);
#define LDRpin A1
#define Relaypin 5
int ONTreshold=400.0;
int OFFTreshold=600.0;
void setup() {
  // put your setup code here, to run once:
pinMode(LDRpin,INPUT);
pinMode(Relaypin,OUTPUT);
lcd.begin(16,2);
lcd.setCursor(0,0);
lcd.print("Light dependent lamps");
delay(5000);
lcd.clear();
}
