import processing.serial.*;
  Serial myPort;        // The serial port
 int xPos = 1;         // horizontal position of the graph
 
 void setup () {

 size(1024, 512);         // set the window size:
 
 println(Serial.list());   // List all the available serial ports
 myPort = new Serial(this, Serial.list()[8], 9600);   //   /dev/tty.usbmodem1411 FTDI cable
 myPort.bufferUntil('\n'); // don't generate a serialEvent() unless you get a newline character:
 
 background(0);// set inital background to black
 }
 void draw () {     // everything happens in the serialEvent()
}
 
 void serialEvent (Serial myPort) {
 String inString = myPort.readStringUntil('\n');
 
 if (inString != null) 
 {
   inString = trim(inString);
   float inByte = float(inString);
   inByte = map(inByte, 0, 1023, 0, height);  //  formatting dataread into height
   stroke(200,0,0);
   line(xPos, height, xPos, height - inByte);  // draw the vertical line:
   if (xPos >= width) {   // at the end of box, go back to the beginning:
     xPos = 0;
     background(0);
      }
   else {  // increment the horizontal position
     xPos++;
         }
     }
}
 
