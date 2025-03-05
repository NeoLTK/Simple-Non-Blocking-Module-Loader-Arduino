#include "moisture.h"
#if MOISTURE 

// low : 20% - 30% ( terre clair sec au toucher )
// mid : 50% ++ (terre noir humid au toucher )s
// semble bon : 80% - 85% ( terro frais jamais arroser du grenier hiver )
// semble trop : 90% + ( le capteur sort mouiller )

moisture::moisture(int pinout) {
	if (!pinout) return;

	this->pinout = pinout;
	this->airVal = MOISTURE_air_value;//640;// MV2 nano // 620;  //674 - 665
	this->waterVal = MOISTURE_water_value;  //280 
	this->moistureVal = 0;
	this->moisturePercent = 0;
	this->error = 0;
	this->curTimer = millis();
	this->oldTimer = curTimer;
	this->warn = 0;
	this->stableTime = MOISTURE_stabilized_trigger;
	this->stableTimer = 0;
	this->oldMoisture = 0;
	this->wireTimer = 0;
	this->disconnected = false;

	this->wire[3] = 1; //grn 0 off 1 on 2 warn
	
}

void moisture::update(){
	this->moistureVal = analogRead(this->pinout); 
	this->curTimer = millis();
	
	if(this->moistureVal < (this->waterVal - 5) || this->moistureVal > (this->airVal + 5)){
		this->disconnected = true;
		this->error = 1;
		this->oldTimer = this->curTimer;
		return 0;
	} 

	if (this->disconnected && (this->curTimer - this->oldTimer) > MOISTURE_disconnect_trigger) {
		this->disconnected = false;
	} else if(this->disconnected) return 0;

	
	int percent = this->getPercentValue();

	Serial.println(moistureVal);
	Serial.println("test");

	if(percent <= 15 && percent >= 0) {
		Serial.print("Pot [");
		Serial.print("] ");
		Serial.println("/!\\ probably out of pot ");
		this->error = 1;
	} else {
		this->error = 0;
	}

	/*if(this->error){
		for(int i = 0; i != 2; i++){
			if(this->wire[i] == 0) {
				Serial.print((i == 0 ? "/!\\ GRN" : ( i == 1 ? "/!\\ VIN" : "/!\\ LINK")));
				Serial.println(" probably disconnected");
			}	
		}
	}*/

	//manque signal
	/*for (int i = 0; i != 2; i++){
		int tmp = (i == 1 ? (this->waterVal - 50) :  (this->airVal + 20 ));

		if((this->moistureVal < tmp && this->wire[i] != 2 ) || (this->wire[i] != 1 && (this->curTimer - this->wireTimer[i]) > 5000)) {
			if(this->wire[i] == 1) {
				this->wire[i] = 2;
				this->wireTimer[i] = this->curTimer;
			} else if (this->moistureVal > tmp){
				this->error = 0;
				this->wire[i] = 1;
				this->wireTimer[i] = this->curTimer;
			} else {
				this->error = 1;
				this->wire[i] = 0;
			}
		}
	}*/

/*
	if((this->moistureVal < (this->waterVal - 20) && this->wire[1] != 2 ) || (this->wire[1] != 1 && (this->curTimer - this->oldTimer) > 5000)) {
		if(this->wire[1] == 1) {
			this->wire[1] = 2;
			this->oldTimer = this->curTimer;
		} else if (this->moistureVal > (this->waterVal - 50)){
			this->error = 0;
			this->wire[1] = 1;
			this->oldTimer = this->curTimer;
		} else {
			this->error = 1;
			this->wire[1] = 0;
		}
	}

	if((this->moistureVal > (this->airVal + 20) && this->wire[0] != 2) || ( this->wire[0] != 1 && (this->curTimer - this->oldTimer) > 5000)){
		if(this->wire[0] == 1) {
			this->wire[0] = 2;
			this->oldTimer = this->curTimer;
		} else if (this->moistureVal < (this->airVal + 20 )){
			this->error = 0;
			this->wire[0] = 1;
			this->oldTimer = this->curTimer;
		} else  {
			this->error = 1;
			this->wire[0] = 0;
		}
	} */

	
	if ((this->curTimer - this->stableTimer) >= this->stableTime) {
	  	if(( percent >= (this->oldMoisture -1 )  && percent <= (this->oldMoisture +1))) {
		    this->stabilized = true;
		    this->stableTimer = this->curTimer;
	  	} else {
		  	this->oldMoisture = percent;
		  	this->stableTimer = this->curTimer;
		  	this->stabilized = false;
	  	}
	}
}

int moisture::getError(){
	return this->error;
}



int moisture::getPercentValue(){
	this->moisturePercent = map(this->moistureVal, this->airVal, this->waterVal, 0, 100);

	if(this->moisturePercent >= 100)  return 100;
	else if(this->moisturePercent <=0) return 0;
	else if(this->moisturePercent > 0 && this->moisturePercent < 100) return this->moisturePercent;

	return -1;
}

int moisture::getValue() {
	return this->moistureVal;
}

/*int moisture::qualibrate(){
	//P0 = analyse Air
	//P1 = Set Air + Analyse water
	//P2 = Set water

	this->phaze = 0;
	this->p1 = false;
	this->p2 = false;
	
	while (this->phaze != 3) {
		this->soilMoistureVal = analogRead(A0); 
	 	if (analog push || this->phase == 1) {
		    if (this->p1 != true) {
		    	this->airVal = this->soilMoistureVal; 
		    	this->p1 = true;
		    }
		    if (analog push || this->phaze == 2){
		       if (this->p2 != true) {
					this->waterVal = this->soilMoistureVal; 
					this->p2 = true;
		       }
		       if (this->p2 == true) return 1;
		    }
		}
	}
	
	return 0;
}*/
#endif