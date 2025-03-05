 #define encoderOutA 2 
 #define encoderOutB 12
 #define encoderSwitch 3
 

#include "rotary.h"

#if ROTARY 


int previousStateA = 1;
//int previousStateB = 1;

volatile static int rotary::counter;
static int rotary::switchState;

rotary::rotary(int t, int tt) {
    pinMode(encoderOutA, INPUT);
    pinMode(encoderOutB, INPUT);
    pinMode(encoderSwitch, INPUT);

    rotary::setVoid("pos", (int*)&rotary::counter);
    rotary::setVoid("state", (int*)&rotary::switchState);
    

    previousStateA = digitalRead(encoderOutA);
    //previousStateB = digitalRead(encoderOutB);

    attachInterrupt(digitalPinToInterrupt(encoderOutA), rotary::ISR_encoderChange, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderSwitch), rotary::ISR_encoderSwitch, CHANGE);
}

void rotary::update() {
  rotary::setBool("istState", digitalRead(encoderSwitch));
}

void rotary::ISR_encoderSwitch() {
  int buttonState = digitalRead(encoderSwitch);
  if (buttonState != HIGH) switchState = 1;
}

void rotary::ISR_encoderChange() {    

  int currentStateA = digitalRead(encoderOutA);
  int currentStateB = digitalRead(encoderOutB);

  if (currentStateA != previousStateA) {
      if (currentStateA == 1 && currentStateB == 1) // Falling edge
          counter--;
      else if (currentStateA == 1 && currentStateB == 0) // Rising edge
          counter++;

      previousStateA = currentStateA;
  }
}

#endif

