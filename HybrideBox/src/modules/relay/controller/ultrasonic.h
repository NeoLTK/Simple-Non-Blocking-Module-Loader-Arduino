#ifndef Ultrasonic_h
#define Ultrasonic_h

#include "../relay.h"
#include "../../../../configuration.h"
#if ULTRASONIC

class ultrasonic : public relay {
	//using relay::relay;

	public:
		ultrasonic(int pinout) : relay(pinout) {};
		~ultrasonic();

		void update();

		/*bool getStatus() override;*/

	private :
		bool active;


};

#endif
#endif