#if POT
#include "pot.h"

pot::pot(HybrideBox *HBox, int pm, int ph){
	this->Moisture = new moisture(pm);
	this->Hydration = new hydration(ph, this->Moisture);

	this->curTime = millis();
	this->lasHydTime = this->curTime;
	this->hydrationInterval = HYDRATION_hydrating_interval;
	this->hydrateCycle = 0;
	this->HBox = HBox;
}
void pot::update(){this->update(0);}

int pot::update(int index){
	this->curTime = millis();

	this->Moisture->update();
  	this->Hydration->update(index);



	int moisture = this->Moisture->getPercentValue();


	if(!this->Moisture->disconnected && this->Moisture->stabilized) 
	    if ((moisture <= 60 && moisture >= 10) && (this->curTime - this->lasHydTime) > this->hydrationInterval) {

	      if(!this->Hydration->process()) {
	        this->lasHydTime = this->curTime;
	        this->hydrateCycle = this->hydrateCycle + 1;
	    }
	} 


	/*if(this->Moisture->getError()) {
		this->hydrating = false;
		this->hydrateProcess = false;
		this->stopPump();
		Serial.print("Pot [");
    	Serial.print(index);
    	Serial.print("] ");
		Serial.println("/!\\ Hydration tempory locked");
		
		return;
	}*/

	if(this->HBox){
		this->HBox->pot[index-1].moisture = pot::getMoisturePercent();
		this->HBox->pot[index-1].moistureValue = pot::getMoistureValue();
		this->HBox->pot[index-1].stabilized = pot::isStabilized();
		this->HBox->pot[index-1].isConnected = pot::isConnectedMoisture();
		this->HBox->pot[index-1].hydrateCycle = pot::hydrateCycle;
	}

	return 1;
}


int pot::getMoisturePercent(){
	return this->Moisture->getPercentValue();
}


bool pot::isConnectedMoisture(){
	return this->Moisture->disconnected;
}

int pot::getMoistureValue(){
	return this->Moisture->getValue();
}

bool pot::isStabilized(){
	return this->Moisture->stabilized;
}

#endif