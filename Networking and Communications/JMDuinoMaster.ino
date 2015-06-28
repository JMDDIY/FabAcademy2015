// Wire Master Writer

// Refer to the "Wire Slave Receiver" 



#include <Wire.h>

#define NODE1_ADDR   0x10        // 7 bit I2C address node1
#define NODE2_ADDR   0x11        // 7 bit I2C address node2
#define NODE3_ADDR   0x12        // 7 bit I2C address node3

int datareceived = 0;

void setup()
{
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
}



void loop()
{
Serial.print("demande de 3 blinks a node1: ");
BlinkNode(NODE1_ADDR,3);
delay(3000);

Serial.print("demande de 5 blinks a node2: ");
BlinkNode(NODE2_ADDR,5);
delay(3000);
  
Serial.print("demande de 7 blinks a node3: ");
BlinkNode(NODE3_ADDR,7);
delay(3000);  
}

void BlinkNode(byte NodeNum,byte times)
{
Wire.beginTransmission(NodeNum); // transmit to device nodenum
Wire.write(times);
delay(1000);
//Wire.requestFrom(NodeNum,2);
//while (Wire.available())   // slave may send less than requested
//  {
//datareceived = Wire.read();
//Serial.print("reponse:");
//Serial.println(datareceived);
//  }
Wire.endTransmission(); 

}

