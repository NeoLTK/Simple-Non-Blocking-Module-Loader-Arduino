#include "digitalThermo.h"
#if DIGITALTHERMO


digitalThermo::digitalThermo(int pinout) { 
  this->oneWire = OneWire(pinout); 
  this->sensors = DallasTemperature(&this->oneWire);
  
  this->sensors.setWaitForConversion(false);
  this->sensors.begin(); 
} 

void digitalThermo::update() { 
  static unsigned long int time = millis();
  static float tmp = 0;
  static bool requesting = false;
  
  if(!requesting){
    this->sensors.requestTemperatures(); 
    time = millis();
    requesting = true;
  } else {
      if((millis() - time) > this->sensors.millisToWaitForConversion(this->sensors.getResolution())) {
        requesting = false;
        tmp = this->sensors.getTempCByIndex(0);
      }
  }

 modules::setFloat("temperature", tmp);

} 

#endif
