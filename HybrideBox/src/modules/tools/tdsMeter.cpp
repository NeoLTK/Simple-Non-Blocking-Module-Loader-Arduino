#include "tdsMeter.h"
#if TDS
 
float temperature = 25,tdsValue = 0;
 
tdsMeter::tdsMeter(int pinout){
    this->gravityTds.setPin(pinout);
    this->gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
    this->gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
    this->gravityTds.begin();  //initialization
    /*this->HBox = HBox;*/
}
 
void tdsMeter::update(){
    //temperature = readTemperature();  //add your temperature sensor and read it
    //this->gravityTds.setTemperature(this->HBox->thermistorTempC);  // set the temperature and execute temperature compensation
    this->gravityTds.update();  //sample and calculate
    this->waterEC = gravityTds.getTdsValue() +198 ;  // then get the value
   
}

int tdsMeter::getEc(){
    return this->waterEC;
}
#endif