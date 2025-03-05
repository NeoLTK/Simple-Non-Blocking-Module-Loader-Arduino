
#ifndef Moisture_H
#define Moisture_H

#include "../../../configuration.h"
#if MOISTURE
	#include <Arduino.h>
	#include "../modules.h"

	class moisture : public modules {
		public:
			moisture(int);
			bool stabilized;
			bool disconnected;

			int getPercentValue();
			int getValue();
			void update();
			
			int qualibrate();
			int getError();

		private:
			int pinout;

			int error;
			int airVal;
			int waterVal;
			int moistureVal;
			int moisturePercent;
			int stableTime;
			int stableTimer;
			int oldMoisture;

			int curTimer;
			int oldTimer;
			int warn;

			int *wire;
			int wireTimer;

			int phaze;
			bool p1;
			bool p2;
	};

#endif
#endif
