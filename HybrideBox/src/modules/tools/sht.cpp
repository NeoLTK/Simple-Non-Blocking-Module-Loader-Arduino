#include "sht.h"
#if DHTSENSOR

sht::sht(int pinout){
	this->pin = pinout;
	this->type = "DHT22";
	this->curTime = millis();
	this->checkTime = curTime;
	this->interval = 2000;

	this->curTemp = 0.0;
	this->curHumi = 0.0;
/*
	this->HBox = HBox;*/
}

void sht::update(){
	this->curTime = millis();

	if ((this->curTime - this->checkTime) > this->interval) {
		this->checkTime = millis();

		int chk = this->DHT.read22(this->pin);

	    this->curHumi = this->getHumi();
	    this->curTemp = (float) this->DHT.getTemperature();		

	    modules::setFloat("humidity", this->curHumi); 
	    modules::setFloat("temperature", this->curTemp); 
	}

	/*if(this->HBox) {
		this->HBox->temperature = this->curTemp;
		this->HBox->humidity = this->curHumi;
	}*/
}

float sht::getHumi(){
	float humi = (float) this->DHT.getHumidity();

	for(int i = 1; i < 8; i++){
	    if (this->calHumiDHT[i] > humi){
			int dhtLow = this->calHumiDHT[i-1];
			int dhtHigh = this->calHumiDHT[i];
			int calLow = this->calHumi[i-1];
			int calHigh = this->calHumi[i];

			return map(humi, dhtLow, dhtHigh, calLow, calHigh);
	    }
	 }
}


float sht::getHumidity(){
	return this->curHumi;
}


float sht::getTemperature(){
	return this->curTemp;
}

#endif