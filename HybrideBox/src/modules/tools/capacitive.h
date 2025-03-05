
#ifndef capacitivee_H
#define capacitivee_H

#include "../../../configuration.h"
#if CAPACITIVE

	#include <Arduino.h>
	#include <CapacitiveSensor.h>

	#include "../modules.h"

	class capacitive : public modules {
		public:

			capacitive(int, int);
			

			void update();
		
	};


#endif 
#endif 