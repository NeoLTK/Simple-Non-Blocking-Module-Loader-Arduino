#include "fridge.h"
#if FRIDGE
char* getTimee(unsigned long int ms){

	unsigned long int milliseconds = ms;
	unsigned long int seconds = milliseconds / 1000;
	milliseconds %= 1000;

	int minutes = seconds / 60;
	seconds %= 60;

	unsigned long int hours = minutes / 60;
	minutes %= 60;

	char tmp[21];
	sprintf(tmp, "%d:%d:%d\0", hours, minutes, seconds);

	Serial.print(hours);
	Serial.print(":");
	Serial.print(minutes);
	Serial.print(":");
	Serial.print(seconds);

	return tmp;
}

void fridge::update() {
	static unsigned long int time = millis();
	modules* Thermistor = modules::Manager->findObj(THERMISTOR_ID);
	modules* LightMeter = modules::Manager->findObj(LIGHTMETER_ID);
	modules* DigitalThermo = modules::Manager->findObj(DIGITALTHERMO_ID);

	float temperature = (DigitalThermo ? DigitalThermo->getFloat("temperature") : 0);
	bool light = (LightMeter ? LightMeter->getBool("lighting") : false);


	if (temperature > FRIDGE_hight_trigger && light){
		relay::enable();
		Serial.print(F("Water fridge : "));
		Serial.println(getTimee(millis()-time));

	} else if(temperature < FRIDGE_low_trigger || !light) {
		relay::disable();
		time = millis();
	}

	modules::setBool("fridging", relay::enabled);

	return relay::update();
}

/*bool fridge::getStatus(){
	return relay::getStatus();
}*/

#endif