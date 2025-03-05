#include "relay.h"

relay::relay(int pin) : pinout(pin), enabled(false), modules(){
	/*this->pinout = pin;*/

	pinMode(this->pinout, OUTPUT); 
	digitalWrite(this->pinout, HIGH);

	modules::setVoid("enabled", &this->enabled);

	this->secureMode = true;
	this->secure = false;
	this->trigMode = 1;
	this->time = millis();
}

void relay::update(modulesManager* ModManager){
	relay::update();
}

void relay::update() {
	if(this->secureMode) {
		if(!this->secure && this->enabled && (millis() - this->time) > RELAY_SECURETIME){
			this->secure = true;
			this->enabled = false;
			this->time = millis();
		} else if (this->secure && (millis() - this->time) < RELAY_SECUREWAIT) {
			this->enabled = false;
		} else this->secure = false;		
	}

	if(this->enabled) {
		digitalWrite(this->pinout, (this->trigMode ? HIGH : LOW ));
		this->time = (millis() < this->time ? millis() : this->time);
	} else {
		digitalWrite(this->pinout, (this->trigMode ? LOW : HIGH));
		if(!this->secure) this->time = millis();
	}

	if(this->secure) {
		Serial.print("Relay ");
		Serial.print(modules::id);
		Serial.println(" : secure time");
	} 
}


void relay::enable(){
	this->enabled = true;
}

void relay::disable(){
	this->enabled = false;
}

