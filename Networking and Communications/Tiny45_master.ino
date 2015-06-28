/* ATtiny45 as an I2C Master 
 * I2C master
 * SETUP:
 * ATtiny Pin 1 = (RESET) N/U                  ATtiny Pin 2 = N/U
 * ATtiny Pin 3 = (D4) N/U                     ATtiny Pin 4 = GND
 * ATtiny Pin 5 = SDA                          ATtiny Pin 6 = N/U
 * ATtiny Pin 7 = SCK                          ATtiny Pin 8 = VCC (2.7-5.5V)
 * NOTE! - It's very important to use pullups on the SDA & SCL lines!

 * TinyWireM USAGE see TinyWireM.h   */

#include <TinyWireM.h>                  // I2C Master lib for ATTinys which use USI
#include <SoftwareSerial.h>

#define NODE1_ADDR   0x10        // 7 bit I2C address node1
#define NODE2_ADDR   0x11        // 7 bit I2C address node2
#define NODE3_ADDR   0x12        // 7 bit I2C address node3
#define RX 3
#define TX 4
int datareceived = 0;
SoftwareSerial Myserial(RX,TX);

void setup(){
  Myserial.begin(9600);                 
  TinyWireM.begin();                    // initialize I2C lib
  delay (1000);
}

void loop(){
  delay(5000);
  Myserial.print("demande de blink node1");
  BlinkNode(NODE1_ADDR,0x1);
  datareceived = TinyWireM.receive();
  Myserial.println(datareceived);
  delay (1000);
  BlinkNode(NODE2_ADDR,0x2);
  delay (1000);
  BlinkNode(NODE3_ADDR,0x3);
  delay (1000);

}

void BlinkNode(byte NodeNum,byte times) 
{
  TinyWireM.beginTransmission(NodeNum);
  TinyWireM.send(times);                 // Ask node to blink n time
  TinyWireM.endTransmission();          // Send to the slave
}

