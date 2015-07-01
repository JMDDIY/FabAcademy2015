#include "FastLED.h"


#define NUM_LEDS 136    /*4 in the 1st breakout */

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  
#define DATA_PIN 5
#define NUM_HOLDS 109
// Define the array of leds
CRGB leds[NUM_LEDS];
uint32_t MyColor;

static const boolean Lane[10][NUM_HOLDS] = {
{0,0,1,0,1,0,0,1,1, 0,0,0,0,0,0,0,0,1,0, 0,0,1,1,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,0,0, 0,1,0,1,0,0,0,0,0,0, 0,0,0,0,0,1,0,1,0,0, 0,1,0,1,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,1,0, 1,1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,1,0, 0,1,0,0,0,0,0,0,0,0},
{0,1,1,0,0,1,0,1,0, 0,0,0,0,1,1,0,0,0,0, 0,0,0,1,0,1,0,0,0,0, 0,0,0,0,1,1,0,0,0,0, 0,0,0,0,1,0,0,0,0,0, 0,0,1,0,1,0,0,0,0,0, 0,0,0,0,0,0,1,0,0,0, 0,0,1,0,1,0,0,0,0,0, 0,0,0,0,0,0,1,0,0,0, 0,0,0,1,1,0,0,0,0,0, 0,0,0,0,0,1,0,0,0,0},
{0,1,1,0,1,1,1,0,0, 0,0,1,1,0,0,0,0,0,0, 0,0,0,0,0,0,1,0,0,0, 0,1,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,0,0, 0,0,1,1,0,0,0,0,0,0, 0,0,0,0,0,1,1,0,0,0, 0,0,0,0,1,1,0,0,0,0, 0,0,0,1,1,0,0,0,0,0, 0,0,0,0,0,0,1,0,0,0, 0,0,0,1,0,0,0,0,0,0},
{1,0,0,1,0,1,1,0,0, 0,1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,1, 0,1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,0,1, 0,1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,1, 0,1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,1,0},
{0,0,1,0,1,0,0,0,1, 0,0,0,0,0,0,0,1,0,1, 1,0,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,0, 1,0,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,1,0, 1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,0,1, 0,1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,0, 1,0,0,0,0,0,0,0,0,0},
{1,0,0,1,0,1,1,0,0, 1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,1,0, 0,0,0,1,0,0,0,0,0,0, 0,0,0,0,1,1,0,0,0,0, 0,0,0,0,0,1,1,0,0,0, 0,0,1,0,1,0,0,0,0,0, 0,0,0,0,0,0,1,0,0,0, 0,0,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,0,0, 0,0,1,0,0,0,0,0,0,0},
{0,0,1,0,1,0,0,1,0, 0,0,0,0,0,0,1,0,0,0, 0,1,0,0,1,0,0,0,0,0, 0,0,0,0,0,0,1,0,0,1, 0,1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,1, 0,1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,1, 1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,1, 0,1,0,0,0,0,0,0,0,0},
{0,0,1,0,1,0,0,1,1, 0,0,0,1,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,0,0, 0,1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,1,0, 1,0,0,1,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,0,0, 1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,1},
{0,1,0,1,0,1,1,1,0, 0,0,0,0,1,1,0,0,0,0, 0,0,0,0,1,1,0,0,0,0, 0,0,0,1,1,0,0,0,0,0, 0,0,0,0,0,0,1,1,0,0, 0,0,0,0,1,0,0,0,0,0, 0,0,0,0,1,1,0,0,0,0, 0,0,0,1,0,1,0,0,0,0, 0,0,0,0,0,1,0,0,0,0, 0,0,0,0,0,1,0,0,0,0, 0,0,0,0,1,1,0,0,0,0},
{1,1,1,1,1,1,1,1,1, 0,1,1,1,0,1,1,1,0,0, 0,0,0,1,0,0,0,1,0,0, 0,1,1,0,0,1,1,0,0,0, 0,0,0,1,0,0,0,1,0,0, 0,0,0,0,0,0,0,0,0,0, 0,1,1,0,1,0,1,0,0,1, 1,0,0,1,0,1,0,1,0,1, 0,1,1,0,1,1,1,0,1,1, 1,0,0,1,0,1,0,1,0,1, 0,1,1,0,0,1,0,1,1,1}};

/*{0,1,0,1,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0}*/

const byte NbLedByHolds[NUM_HOLDS] = {4,4,4,4,4,4,4,4,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

int ActiveLane[NUM_LEDS];
int CompteurAddressLED;
int MyLane;
char CharRead;
char FlushExtraChar;
int compteurTempo;
int NbLedInThisHold;
int StatusLed;
int Error;      /*used for loop*/
byte RG_Exchangetampon;
void setup() 
{
        Serial.begin(9600);                                  /*init Serial*/
	FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds,NUM_LEDS);  /*init LedStrip*/

        Error = -1;
}

void loop() 
{
 
        while (Error == -1)         /* while read value not correct ....*/ 
        {
        CharRead ='?'; 
        Serial.println("Level 4b     : 0 ");
        Serial.println("Level 5a     : 1 ");
        Serial.println("Level 5b     : 2 ");
        Serial.println("Level 5b     : 3 ");
        Serial.println("Level 5c     : 4 ");
        Serial.println("Level 5c     : 5 ");
        Serial.println("Level 5c     : 6 ");
        Serial.println("Level 6a     : 7 ");
        Serial.println("Level 6a     : 8 ");
        Serial.println("Level 6b     : 9 ");
        Serial.print("Which Lane     [0..9]? :");
        while (CharRead == '?'){ 
        if (Serial.available() > 0) {                                /*char in buffer line ? */
                    CharRead = Serial.read();                        /*read the 1st one */     
                    while (Serial.available () > 0) Serial.read();   /*remove the char pending in stack*/
    
                                         
                     
                                           /* activate the change */
                                     }
        
                                }
        Serial.println(CharRead);          /* send back the typed char for view */
       

        switch (CharRead){                            /* validate the value */
          case '0' : MyLane = 0;Error = 0;break;
          case '1' : MyLane = 1;Error = 0;break;
          case '2' : MyLane = 2;Error = 0;break;
          case '3' : MyLane = 3;Error = 0;break;
          case '4' : MyLane = 4;Error = 0;break;
          case '5' : MyLane = 5;Error = 0;break;
          case '6' : MyLane = 6;Error = 0;break;
          case '7' : MyLane = 7;Error = 0;break;
          case '8' : MyLane = 8;Error = 0;break;
          case '9' : MyLane = 9;Error = 0;break;
          default : Error = -1;Serial.println("not in range");
                           }
        }
        
        CompteurAddressLED=0;                    /*convert table of holds into table of leds */     
        for (int i = 0; i < NUM_HOLDS; i++)
        { 
       
         StatusLed = Lane[MyLane][i];
         NbLedInThisHold = NbLedByHolds[i];
          
         
                for(int j=0 ; j < NbLedInThisHold ; j++ )
                {
                ActiveLane[CompteurAddressLED] = StatusLed;
                CompteurAddressLED++;
                } 
                
        }
        
        
        
        
        Error = -1;
        
        while (Error == -1)
        {
        Serial.println("Red      : 0 ");
        Serial.println("DarkRed  : 1 ");
        Serial.println("Orange   : 2 ");
        Serial.println("Yellow   : 3 ");
        Serial.println("Green    : 4 ");
        Serial.println("Purple   : 5 ");
        Serial.println("Blue     : 6 ");
        Serial.println("Cyan     : 7 ");
        Serial.println("Gray     : 8 ");
        Serial.println("White    : 9 ");
        Serial.print("Which Color  [0..9]? :");
        
        CharRead ='?';  
        while (CharRead == '?'){ 
        if (Serial.available() > 0) {
                                      CharRead = Serial.read();           /* read the 1st one*/
                                      while (Serial.available () > 0) Serial.read();   /*remove the char pending in stack*/ 
                                    }
        }
        Serial.println(CharRead);
        switch (CharRead){                                        /* validate the data and set the color */
          case '0': MyColor = CRGB::DarkRed; Error = 0;break;
          case '1': MyColor = CRGB::Red;   Error = 0;break;
          case '2': MyColor = CRGB::Orange;Error = 0;break;
          case '3': MyColor = CRGB::Yellow;Error = 0;break;
          case '4': MyColor = CRGB::Green; Error = 0;break;
          case '5': MyColor = CRGB::Purple;Error = 0;break;
          case '6': MyColor = CRGB::Blue;  Error = 0;break;
          case '7': MyColor = CRGB::Cyan;  Error = 0;break;
          case '8': MyColor = CRGB::Gray;  Error = 0;break;
          case '9': MyColor = CRGB::White; Error = 0;break;
          
          
         default : {Error = -1;Serial.println("not in range");}
                        }
        }                
        Error =-1;
       
       
       for (int i=0; i < NUM_LEDS; i++)
         {
          if ( ActiveLane[i] == 0 ) { leds[i] = CRGB::Black; }
                
          else     { if (i<36) { leds[i] = MyColor;    }
                   else { leds[i] = MyColor;
                          RG_Exchangetampon = leds[i].r;
                          leds[i].r = leds[i].g;
                          leds[i].g = RG_Exchangetampon;
                         }
                   
                   
                   
                   
                 
                   }
         }
       
       FastLED.show();                          /* activate the change */
 
}
