/* ATtiny45 as an I2C Slave    

 * ATtiny Pin 1 = (RESET) N/U                      ATtiny Pin 2 = (D3) N/U
 * ATtiny Pin 3 = (D4) to LED1                     ATtiny Pin 4 = GND
 * ATtiny Pin 5 = I2C SDA                          ATtiny Pin 6 = N/U
 * ATtiny Pin 7 = I2C SCK                          ATtiny Pin 8 = VCC (2.7-5.5V)

 * More on TinyWireS usage - see TinyWireS.h
 */

#include "TinyWireS.h"                  // wrapper class for I2C slave routines

#define I2C_SLAVE_ADDR  0x12           // i2c slave address (18)
#define LED1_PIN         4              // ATtiny Pin 3

void setup(){
  pinMode(LED1_PIN,OUTPUT);             // lep pin
  Blink(LED1_PIN,1);                    // show it's alive
  TinyWireS.begin(I2C_SLAVE_ADDR);      // init I2C Slave mode
}

void loop(){
  byte byteRcvd = 0;
  if (TinyWireS.available()){           // got I2C input!
    byteRcvd = TinyWireS.receive();     // get the byte from master
    Blink(LED1_PIN,byteRcvd);           // master must wait for this to finish before calling Wire.requestFrom
                                        
                                        // send it back to master
    TinyWireS.send(byteRcvd);  }
}

void Blink(byte led, byte times){ // poor man's display
  for (byte i=0; i< times; i++){
    digitalWrite(led,HIGH);
    delay (200);
    digitalWrite(led,LOW);
    delay (100);
  }
}
