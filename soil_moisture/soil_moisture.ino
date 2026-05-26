#include<LiquidCrystal_I2C.h>
#include<Wire.h>
#define ONTreshold 30
#define OFFTreshold 60
const int SOILPIN=10; 
const int relay=9;

LiquidCrystal_I2C lcd(0*27,16,2);

void setup() {
  pinMode(10,INPUT);
  pinMode(9,OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Soil Moisture Sensor!!");
  delay(5000);
  lcd.clear();
}

void loop() {
   digitalWrite(9,LOW);  // A HYSTERESIS TO PREVENT RELAY CHATTER
   
  int sensorvalue=analogRead(10);
  int SensorValuePercent=map(sensorvalue,0,1023,0,100);
 if(isnan(sensorvalue)){   //ERROR HANDLING CODE
    lcd.setCursor(0,1);
    lcd.print("Sensor Error!!"); 
    delay(3000);
  }
  lcd.setCursor(0,0);
  lcd.print("Soil moisture level:");  //DISPLAYING SOIL MOISTURE LEVEL
  lcd.print(SensorValuePercent);
  lcd.print("%");
  
  if(SensorValuePercent<30){
    digitalWrite(9,HIGH); // TURN PUMP ON ACCORDING TO THE CONDITION 
    }
  if(SensorValuePercent>60){
   digitalWrite(9,LOW);  // TURN PUMP OFF ACCORDING TO THE CONDITION
  }
  }
