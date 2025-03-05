
#ifndef PHMeter_h
#define PHMeter_h

#include "../../../configuration.h"
#if PH
	#include "../modules.h"

	#include <Arduino.h>
	#include <DFRobot_PH.h>


	class phMeter : public modules {
		public: 
			phMeter(int pinout);
			
			void update();

			float getPh();

		private:
			DFRobot_PH ph;
			int pinout;

			float phValue;
	};

#endif
#endif
