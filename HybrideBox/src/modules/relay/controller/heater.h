#ifndef Heater_h
#define Heater_h

#include "../relay.h"
#include "../../../../configuration.h"
#if HEATER

class heater : public relay {
	//using relay::relay;

	public:
		 heater(int pinout) : relay(pinout) {};
		~heater();

		void update();

		/*bool getStatus() override;*/

		

};

#endif	
#endif	