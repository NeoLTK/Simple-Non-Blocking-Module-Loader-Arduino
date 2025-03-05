
#include "hydraponics.h"
#if HYDRO
#include <EEPROM.h>
//#include "../../tools/screen/screen.h"



hydraponics::hydraponics(int pinout) : relay(pinout) {
	this->curTimer = millis();
	this->oldTimer = 0;
	/*this->rollOver = 2000;*/
	this->hydrating = false;
	this->over = 0;
	this->force = false;
	//pinMode(2, INPUT);
	if(EEPROM.read(0x00)) this->force = true;

}

String getTime(unsigned long int ms){
	String tmp;
	unsigned long int milliseconds = ms;
	unsigned long int seconds = milliseconds / 1000;
	milliseconds %= 1000;

	int minutes = seconds / 60;
	seconds %= 60;

	unsigned long int hours = minutes / 60;
	minutes %= 60;

	tmp.concat(hours);
	tmp.concat(":");
	tmp.concat(minutes);
	tmp.concat(":");
	tmp.concat(seconds);

	return tmp;
}

void hydraponics::update()  {
	//screen* Screen =  (screen*) modules::Manager->findObj(SCREEN_ID);
	this->curTimer = millis();
/*	if (digitalRead(2) == HIGH) 
	 	this->force = true;*/

	int  incomingByte;
	if (Serial.available() > 0) {
	    incomingByte = Serial.read();

	   	if(incomingByte == 102) force = (!force ?  true : false);
	}
	
	if (this->oldTimer  > this->curTimer) {
		this->over = sizeof(unsigned long int) - this->oldTimer;
		this->oldTimer = 0;
	}
	
	this->curTimer = this->over + this->curTimer;

	if (((this->curTimer - this->oldTimer) > HYDRO_HYDRATION_hydrating_time) && this->hydrating ) {
		//EEPROM.update(0x00, 0);

		this->hydrating = false;
		relay::disable();
		this->oldTimer = millis();
		if(this->over) this->over = 0;
	}

	if ((((this->curTimer - this->oldTimer) > HYDRO_HYDRATION_hydrating_interval) && !this->hydrating) || this->force) {
		this->force = false;
		//if (modules::Manager->findObj(LIGHTMETER_ID)->getBool("lighting")) {
			//EEPROM.update(0x00, 1);

			this->hydrating = true;
			relay::enable();
			this->oldTimer = millis();
			if(this->over) this->over = 0;
		//} else Serial.println(F("Watering processing : watering start when the light starts"));
	} 

	/*if(!this->hydrating ) {
		//if(modules::Manager->findObj(LIGHTMETER_ID)->getBool("lighting")) {
			
			String tmp = "Next watering : " + getTime(HYDRO_HYDRATION_hydrating_interval - (this->curTimer - this->oldTimer));
			static char* str = new char [tmp.length()+5];
			strcpy(str, tmp.c_str());
			//Screen->write(str);
			Serial.println(str);
		
			
		//} else Serial.println(F("Next watering : after start light"));
	} else {

		String tmp = "Watering processing : " + getTime(HYDRO_HYDRATION_hydrating_time - (this->curTimer - this->oldTimer));
		static char* str = new char [tmp.length()+12];
		strcpy(str, tmp.c_str());
		//Screen->write(str);
		Serial.println(str);
	}*/

	//lock le timer la nuit, donc l'inondation est toujours a heur fix apres allumage
	/*if(!HBox->light) this->oldTimer = this->curTimer;*/


	/*this->rollOver = millis();*/

	return relay::update();
}

/*bool relay::getStatus(){
	return relay::getStatus();
}

*/
#endif