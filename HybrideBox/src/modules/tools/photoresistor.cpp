#include "photoresistor.h"
#if PHOTORESISTOR

photoResistor::photoResistor(int pinout){
	this->pinout = pinout;
  this->lux = 0;
}
int sensorRawToPhys(int raw){
  // Conversion rule
  float Vout = float(raw) * (5 / float(1023));// Conversion analog to voltage
  float RLDR = (10000 * (5 - Vout))/Vout; // Conversion voltage to resistance
  int phys=500/(RLDR/1000); // Conversion resitance to lumen
  return phys;
}

void photoResistor::update(){
	int sensorVal = analogRead(this->pinout);
  	this->lux = sensorRawToPhys(sensorVal);

  	modules::setVoid("lux", (int*) &this->lux);
}




#endif