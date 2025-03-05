#ifndef tdsMeter_h
#define tdsMeter_h

#include "../../../configuration.h"
#if TDS
	#include "../modules.h"

	#include <EEPROM.h>
	#include "GravityTDS.h"

	class tdsMeter : public modules {
		public :
			tdsMeter(int);
			void update();

			int getEc();

		private :
			GravityTDS gravityTds;
			int waterEC;
	};

#endif
#endif