#ifndef dthermo_h
#define dthermo_h
#include "../../../configuration.h"

#if DIGITALTHERMO
	#include "../modules.h"
	
	#include <OneWire.h> 
	#include <DallasTemperature.h>

	class digitalThermo : public modules {
		public :
			digitalThermo(int);

			void update();


		private :
			int pinout;
			OneWire oneWire;
			DallasTemperature sensors;
	};		

#endif
#endif