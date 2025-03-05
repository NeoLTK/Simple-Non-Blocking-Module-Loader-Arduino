#include "ultrasonic.h"
#if ULTRASONIC

void ultrasonic::update() {
	static unsigned long int lastTime = millis();
	modules* DHTSensor = modules::Manager->findObj(DHT_ID);
	modules* lightMeter = modules::Manager->findObj(LIGHTMETER_ID);

	float temperature = (DHTSensor ? DHTSensor->getFloat("temperature") : 0);
	float humidity = (DHTSensor ? DHTSensor->getFloat("humidity") : 0);
	bool light = (lightMeter ? lightMeter->getBool("lighting") : false);

	if ((temperature > ULTRASONIC_overtemp_trigger || (humidity < ULTRASONIC_low_trigger && temperature > HEATER_low_trigger)) && light ) {
		relay::enable();
	} else if (humidity > ULTRASONIC_hight_trigger || !light || temperature < HEATER_low_trigger) {
		relay::disable();
	}	
	else  {
		relay::disable();
	}

	if ((millis() - lastTime ) > ULTRASONIC_reset_time) {
		relay::disable();
		lastTime = millis();
	}

	modules::setBool("enabled", relay::enabled);
	return relay::update();
}

/*bool ultrasonic::getStatus(){
	return relay::getStatus();
}*/

#endif