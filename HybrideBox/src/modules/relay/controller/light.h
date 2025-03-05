#ifndef light_h
#define light_h


#include "../relay.h"
#include "../../../../configuration.h"
#if LIGHT

class light : public relay {
	//using relay::relay;

	public:
		 light(int pinout) : relay(pinout), slave(LIGHT_SLAVE), lastTime(millis()),  lastTime2(millis()) {};
		~light();

		void update() override;
		int slave;

		unsigned long int lastTime;
		unsigned long int lastTime2;
};

#endif	
#endif	