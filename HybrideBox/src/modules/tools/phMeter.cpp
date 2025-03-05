#include "phMeter.h"
#if PH

float voltage,phValue,temmperature = 25;

phMeter::phMeter( int pinout) : pinout(pinout) {
	this->ph.begin();
}

void phMeter::update(){


	static unsigned long oldTime = millis();
    if(millis()-oldTime>1000U){    
        modules* Thermistor = modules::Manager->find(THERMISTOR_ID);
        float temperature = (Thermistor ? Thermistor->getFloat("temperature") : 25);

        oldTime = millis();        
        voltage = analogRead(this->pinout)/1024.0*5000;  
        phValue = this->ph.readPH(voltage, temmperature); 
        this->phValue = phValue;
        
        modules::setFloat("ph", this->phValue - 0.90);

    }
    //ph.calibration(voltage,temmperature);  */
}

float phMeter::getPh(){
    return this->phValue;
}
#endif