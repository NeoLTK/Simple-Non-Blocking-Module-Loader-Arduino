#ifndef ROTARY_H
#define ROTARY_H
#include "../../../../configuration.h"


#if ROTARY 
#include <Arduino.h>
#include "../../modules.h"
	
	class rotary : public modules {
		public:
			static bool state;
			rotary(int, int);

			void update();

		private:
			static void ISR_encoderChange();
			static void ISR_encoderSwitch();
			volatile static int counter;
			static int switchState;

	};


#endif
#endif