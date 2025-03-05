#include "light.h"
#if LIGHT

	void light::update() {
		int light_id = 0;
		int lux = modules::Manager->findObj(PHOTORESISTOR_ID)->getInt("lux");

		#if LIGHTMETER 
			light_id = LIGHTMETER_ID;
		#endif

		#if PHOTORESISTOR
			light_id = PHOTORESISTOR_ID;
		#endif



		if(slave) {
			/*Serial.println(F("SubLight: slave[on]"));*/
			if (lux > 0 && (millis() - lastTime2) > 5000) {
				this->lastTime = millis();
				relay::enable();
			} else if(lux == 0 && (millis() - lastTime) > 5000) {
				this->lastTime2 = millis();
				relay::disable();
			}
		}

		//return relay::update();
	}

#endif 