#include "lightMeter.h"
#if LIGTHMETER

lightMeter::lightMeter(){
	Wire.begin();
	this->Meter->begin();
  	this->lux = 0;
}

int lightMeter::setup(){
	Wire.begin();
	this->Meter->begin();
}

void lightMeter::update(){
	this->lux = this->Meter->readLightLevel();

	if (this->lux > 10000) this->light = true;
	else this->light = false;

	modules::setBool("lighting", this->light);
	modules::setInt("lux", this->lux);
}

int lightMeter::getLux(){
	return this->lux;
}

bool lightMeter::getStatus(){
	return this->light;
}

#endif