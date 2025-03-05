#ifndef fridge_h
#define fridge_h


#include "../relay.h"
#include "../../../../configuration.h"
#if FRIDGE

class fridge : public relay {
	//using relay::relay;

	public:
		 fridge(int pinout) : relay(pinout) {};
		~fridge();

		void update() override;
		/*bool getStatus() override;*/
};

#endif	
#endif	