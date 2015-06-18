#include <SoftwareSerial.h>
#define RX 1
#define TX 2              /* only TX is connected on the board*/

SoftwareSerial MySerial(RX,TX); 

int SensorPin1 = A2; 
int SensorPin2 = A3;

int sensorValue1 = 0;
int sensorValue2 = 0;


void setup() {
pinMode(SensorPin1,INPUT);    /* init pin and serial */
pinMode(SensorPin2,INPUT);
MySerial.begin(9600);
}

void loop() {
 
  sensorValue1 = analogRead(SensorPin1);     /* read value ADC2 */
  delay(10);
  MySerial.print("Piezo 1 :  ");
  MySerial.print(sensorValue1);               /*send value on serial*/
 
  sensorValue2 = analogRead(SensorPin2);     /* read value on ADC3 */
  delay(10);
  MySerial.print("           Piezo 2 :  ");
  MySerial.println(sensorValue2);            /* send value to serial*/
 

}