#ifndef photoresistor_h
#define photoresistor_h

#include "../../../configuration.h"

#if PHOTORESISTOR
	#include "../modules.h"
	#include <Arduino.h>
	#include <math.h>


	class photoResistor : public modules {
		public :
			photoResistor(int);

			void update();

		private :
			int pinout;
			int lux;

	};		

#endif
#endif