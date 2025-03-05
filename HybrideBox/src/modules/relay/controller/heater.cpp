#include "heater.h"
#if HEATER

void heater::update() {
	modules* DHTSensor = modules::Manager->findObj(DHT_ID);

	float temperature = (DHTSensor ? DHTSensor->getFloat("temperature") : 0);

	if (temperature < HEATER_low_trigger){
		relay::enable();
	} else if(temperature > HEATER_hight_trigger) {
		relay::disable();
	}

	return relay::update();
}

/*bool relay::getStatus(){
	return relay::getStatus();
}*/

#endif