
#include <Pixy.h>
#include <SPI.h>
#include "Timer.h"

#define MAX_BLOCKS 1;



Pixy pixy;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.print("Starting...\n");
  int pixyMessage = pixy.init();
  if(pixyMessage){
    Serial.print(pixyMessage); //Does that work as I think it does????
  }
  else{
    Serial.print("Pixy successfuly initialized");
  }
}

void loop() {
 
  static int i = 0;
  uint16_t blocks;
  char buff[32];

  blocks = pixy.getBlocks(MAX_BLOCKS);
  long startTime = micros();
  long endTime  = 0;
  
  if(blocks){
    endTime = micros();
    Serial.print(endTime - startTime);
  }
  
  
}
