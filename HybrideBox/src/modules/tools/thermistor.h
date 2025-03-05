#ifndef thermistor_h
#define thermistor_h
#include "../../../configuration.h"

#if THERMISTOR
	#include "../modules.h"
	#include <Arduino.h>
	#include <math.h>


	class thermistor : public modules {
		public :
			thermistor(int);

			void update(	);

			float getTemperature();
			void setup();

		private :
			//float Rref = 47000.0; //Résistance de référence à 25°C
			float Rref = 10000.0; //Résistance de référence à 25°C
			float V_IN = 5.0; //Alimentation électrique
			float A_1 = 3.354016E-3;
			float B_1 = 2.569850E-4;
			float C_1 = 2.620131E-6;
			float D_1 = 6.383091E-8;

			int pinout;

			float temperature;

			float SteinhartHart(float R);
	};		

#endif
#endif