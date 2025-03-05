#include "hydration.h"
#if HYDRATION


hydration::hydration(int pinout, moisture *Moisture) : relay(pinout) {
	this->MoistureProp = Moisture;
	this->setup();
}

hydration::hydration(int pinout) : relay(pinout) {
	this->MoistureProp = NULL;
	this->setup();
}

void hydration::setup(){
	this->hydrateTime = HYDRATION_hydrating_time;
	this->curTimer = millis();
	this->oldTimer = this->curTimer;
	this->hydrating = false;
	this->fatalError = 0;
	this->hydrateProcess = false;
}


void hydration::update(int index){
	this->curTimer = millis();

	if(this->fatalError) {
		relay::disable();
		Serial.print("Pot [");
    	Serial.print(index);
    	Serial.print("] ");
		Serial.println("/!\\ hydration fatalError and is locked, reset arduino for unlock");
		return;
	}

	if(this->MoistureProp->disconnected) return;

	if(this->MoistureProp && this->MoistureProp->getError()) {
		this->hydrating = false;
		this->hydrateProcess = false;
		relay::disable();
		Serial.print("Pot [");
    	Serial.print(index);
    	Serial.print("] ");
		Serial.println("/!\\ Hydration tempory locked");
		
		return;
	}

	if ((this->curTimer - this->oldTimer) > 30000)
		this->oldTimer = this->curTimer;

	if ((this->curTimer - this->oldTimer) > (this->hydrateTime+500) && this->hydrating) {
		this->hydrating = false;
		this->fatalError = true;
		relay::disable();

		return;
	}

	if(this->hydrateProcess == true) 
		if(!this->hydrate(index))
			//this->hydrateProcess = false;


	return;
}

int hydration::process() {
	if(this->fatalError || (this->MoistureProp && this->MoistureProp->getError())  ) {
		relay::disable();
		return -1;
	}

	if (this->hydrateProcess && !this->hydrating){
		this->hydrateProcess = false;
		return 0;
	} else if (!this->hydrateProcess && !this->hydrating) 
		this->hydrateProcess = true;

	return 1;
}

int hydration::hydrate(int index) {
	if(this->fatalError || (this->MoistureProp && this->MoistureProp->getError())){
		relay::disable();
		return -1;
	}

	if ((this->curTimer - this->oldTimer) > this->hydrateTime + 2000)
		this->oldTimer = this->curTimer;

	Serial.print("Pot [");
	Serial.print(index);
	Serial.print("]");
	Serial.print("hydrating process - ");
	Serial.println(this->curTimer - this->oldTimer);

	if((this->curTimer - this->oldTimer) < this->hydrateTime && !this->hydrating) {
		this->hydrating = true;
		this->oldTimer = this->curTimer;
		this->enable();
	} else if ((this->curTimer - this->oldTimer) > this->hydrateTime && this->hydrating) {
		this->hydrating = false;
 		relay::disable();
 		return 0;
 	} 

	return 1;
}

void hydration::enable(){
	if(this->MoistureProp && this->MoistureProp->stabilized) {
		int moisture = this->MoistureProp->getPercentValue();
		int moistureVal = this->MoistureProp->getPercentValue();

		if(moisture < 90 ) {
			digitalWrite(this->pinout, LOW); 
			return;
		} else {
			relay::disable();
			return;
		}
	}

	digitalWrite(this->pinout, LOW);
	return;
}
#endif