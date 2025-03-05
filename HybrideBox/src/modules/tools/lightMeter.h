
#ifndef LightMeter_H
#define LightMeter_H

#include "../../../configuration.h"

#if LIGTHMETER

	#include <Arduino.h>
	#include <Wire.h>
	#include <BH1750.h>


	#include "../modules.h"

	class lightMeter : public modules {

		public:
			lightMeter();
			int setup();
			
			void update();
			
			int getLux();
			bool getStatus();

			float lux;
			bool light;

		private:
			BH1750 *Meter = new BH1750(0x23);
			
	};

#endif
#endif