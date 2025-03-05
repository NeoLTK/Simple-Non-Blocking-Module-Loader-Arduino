#include "src/core/HybrideBox.h"
#include "src/core/serialMonitor.h"

box *Box = (box*) malloc(sizeof(box));

bool restart = true;
void setup() {
  Box = new box();
  delay(1000);
  
  
  //eprom::load()->readLongInt(1);  
} 


void loop() {  
  Box->update();

 /* if (restart) Serial.println("restarted push K to hide");

  int  incomingByte;
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if(incomingByte == 107) restart = false;
  }*/
  delay(DELAY);
}
