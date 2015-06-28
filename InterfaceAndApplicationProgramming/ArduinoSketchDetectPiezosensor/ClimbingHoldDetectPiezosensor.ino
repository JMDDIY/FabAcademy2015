// send value [0..1024] read on ADC3 to serial port 
// ATtiny45 at 8MHz internal
// Piezo with // R=1Mohm  between GND and ADC3 pin (pin2)

#include <SoftwareSerial.h>
#define RX 1
#define TX 2              /* only TX is connected on the board*/

SoftwareSerial MySerial(RX,TX);  

 
int SensorPin = A3;

int sensorValue = 0;



void setup() {
pinMode(SensorPin,INPUT);    /* init pin and serial */

MySerial.begin(9600);
}

void loop() {
 
  sensorValue = analogRead(SensorPin);     /* read value ADC3 */ 
  MySerial.println(sensorValue);               /*send value on serial*/ 
  delay(100);

}

