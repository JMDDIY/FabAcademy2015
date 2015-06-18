#include <SoftwareSerial.h>
#define RX 1
#define TX 2

SoftwareSerial MySerial(RX,TX);

int SensorPin = A2;
int LedPin = 3;

int sensorValue = 0;
int sensorValueLEDON =0;
int sensorValueLEDOFF = 0;


void setup() {
pinMode(SensorPin,INPUT);
pinMode(LedPin,OUTPUT);
MySerial.begin(9600);
}

void loop() {
  digitalWrite(LedPin,HIGH);
  sensorValueLEDOFF = analogRead(SensorPin);  
  MySerial.print("valueOFF");
  MySerial.println(sensorValueLEDOFF);
  delay(10);
 
  digitalWrite(LedPin,LOW);
 
  sensorValueLEDON = analogRead(SensorPin); 
  delay(10);
  MySerial.print("valueON");
  MySerial.println(sensorValueLEDON);  
 
  
  sensorValue = sensorValueLEDON - sensorValueLEDOFF;
  MySerial.print("value");
  MySerial.println(sensorValue);
 
if (sensorValue >= 70) {
  MySerial.print("Contact");   
  }

}
     