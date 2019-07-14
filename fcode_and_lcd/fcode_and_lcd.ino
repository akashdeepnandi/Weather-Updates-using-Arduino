#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(12,11,5,4,3,2);



#include "dht.h"
#define dht_apin A0 
 
dht DHT;
int LED = 11;
int analog_IN = A1;  
const int sensorMin = 0;     
const int sensorMax = 1024;   

const int hallSensorPin = A3;                      
const unsigned long sampleTime = 2000;
const int maxRPM = 1260;                  
int rpmMaximum = 0;

#include <SFE_BMP180.h>
#include <Wire.h>
SFE_BMP180 pressure;
#define ALTITUDE 1655.0 





void setup(){
  pinMode(LED, OUTPUT);
  pinMode(analog_IN, INPUT);
  pinMode(hallSensorPin,INPUT);
  Serial.begin(9600); 
  lcd.begin(16, 2);
  lcd.print("JEC WEATHER");
  lcd.setCursor(0, 1);
  lcd.print("STATION");
  lcd.clear();
  if (pressure.begin())
  Serial.print("");
  else
  {
  Serial.print("");
  
  }

  }
 
void loop(){




            
  
      if(Serial.available()>0) {
      char x = Serial.read();
      if(x=='x') {
        
        DHT.read11(dht_apin);
        
        Serial.print(DHT.humidity);
        Serial.print(",");
        
        Serial.print(DHT.temperature); 
        Serial.print(",");
        
        int Value = analogRead(analog_IN);  
        
        Serial.print(Value);  
        Serial.print(",");

        int sensorReading = analogRead(A2);
        int range = map(sensorReading, sensorMin, sensorMax, 0, 3);
        switch (range) 
        {
        case 0:    // Sensor getting wet
        Serial.print("F");
        Serial.print(",");
        break;
        case 1:    // Sensor getting wet
        Serial.print("R");
        Serial.print(",");
        break;
        case 2:    // Sensor dry - To shut this up delete the " Serial.println("Not Raining"); " below.
        Serial.print("NR");
        Serial.print(",");
        break;
        }  
 


  char status;
  double T,P,p0,a;
  
  status = pressure.startTemperature();
  if (status != 0)
  {

    delay(status);
 
    status = pressure.getTemperature(T);
    if (status != 0)
    {
      // Print out the measurement:
      //Serial.print("temperature: ");
      //Serial.print(T,2);
      //Serial.print(" deg C, ");
      //Serial.print((9.0/5.0)*T+32.0,2);
      //Serial.print(" deg F");
      
       status = pressure.startPressure(3);
      if (status != 0)
      {

        delay(status);

        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          
          
          Serial.print(P,2);
          Serial.print(",");
          Serial.print(P*0.0295333727,2);
          Serial.print(",");

 
          p0 = pressure.sealevel(P,ALTITUDE); // we're at 1655 meters (Boulder, CO)
          
          Serial.print(p0,2);
          Serial.print(",");
          Serial.print(p0*0.0295333727,2);
          Serial.print(",");
 

 
          a = pressure.altitude(P,p0);
          //Serial.print("computed altitude: ");
          //Serial.print(a,0);
          //Serial.print(" meters, ");
          //Serial.print(a*3.28084,0);
          //Serial.println(" feet");
        }
        else Serial.print("error retrieving pressure measurement\n");
      }
      else Serial.print("error starting pressure measurement\n");
    }
    else Serial.print("error retrieving temperature measurement\n");
  }
  else Serial.print("error starting temperature measurement\n");

  
        int rpm = getRPM();
        if (rpm > rpmMaximum) rpmMaximum = rpm;
        lcd.clear();
        displayRPM(rpm);
        displayBar(rpm); 


         lcd.setCursor(0, 0);
        lcd.print("JEC WEATHER");
        lcd.setCursor(0, 1);
        lcd.print("STATION");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("TEMP=");
        lcd.print(DHT.temperature);
        lcd.print("C");
        lcd.setCursor(0, 1);
        lcd.print("HUM=");
        lcd.print(DHT.humidity);
        lcd.print("%");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LDR=");
        lcd.print(analogRead(analog_IN));
        lcd.print("Cd");
        lcd.setCursor(0, 1);
        lcd.print("RAIN=");
        lcd.print(map(analogRead(A2), sensorMin, sensorMax, 0, 3));
        delay(1000);
        lcd.clear(); 
        lcd.setCursor(0, 0);
        lcd.print("wind s=");
        lcd.print(getRPM());
        lcd.print("rpm");
        lcd.setCursor(0, 1);
        lcd.print("max s=");
        lcd.print(rpmMaximum);
        lcd.print("rpm");
       delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("press=");
        //lcd.print(bmp180.startPressure);
        lcd.print("hPa");

       delay(1000);
        lcd.clear();      
        } // bracket for x
        

        }
        
}








        int getRPM()
        {
        int count = 0;
        boolean countFlag = LOW;
        unsigned long currentTime = 0;
        unsigned long startTime = millis();
        while (currentTime <= sampleTime)
        {
        if (digitalRead(hallSensorPin) == HIGH)
         {
        countFlag = HIGH;
         }
        if (digitalRead(hallSensorPin) == LOW && countFlag == HIGH)
        {
        count++;
        countFlag=LOW;
        }
        currentTime = millis() - startTime;
        }
        int countRpm = int(60000/float(sampleTime))*count;
        return countRpm;
        }
    
      void displayRPM(int rpm) 
      {

  
      Serial.print(rpm);
      Serial.print(",");

      Serial.println(rpmMaximum);
    //  Serial.print(",");
 

      }

      void displayBar(int rpm)
      {
      int numOfBars=map(rpm,0,maxRPM,0,15);


      
      //lcd.setCursor(0,1);
      if (rpm!=0)
      {
      for (int i=0; i<=numOfBars; i++)
      {
      // lcd.setCursor(i,1);
      // lcd.write(1023);

      }
      }
      } 
