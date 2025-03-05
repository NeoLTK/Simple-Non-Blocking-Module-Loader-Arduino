#ifndef Sht_h
#define Sht_h

#include "../../../configuration.h"
#if DHTSENSOR
	#include "../modules.h"

	#include <DHTStable.h>

	class sht : public modules {
		public:
			float curHumi;
			float curTemp;

			sht(int);
			~sht();

			void update();

			float getHumidity();
			float getTemperature();

		private:
			int interval;
			int curTime;
			int checkTime;

			int pin;
			char *type;

			float calHumi[8] = {20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 75.0, 80.0};
			float calHumiDHT[8] = {15.0, 28.0, 39.0, 51.0, 63.0, 75.0, 84.0, 89.0};
			float *calTemp;
			float *calTempDHT;

			DHTStable DHT;

			float getHumi();
			
	};

#endif
#endif
