#ifndef Hydration_H
#define Hydration_H

#include "../../../../configuration.h"
#if HYDROTION
#include "../relay.h"
#include "../../tools/moisture.h"

class hydration : public relay {
	//using relay::relay;

	public:
		hydration(int pinout, moisture*);
		hydration(int pinout);

		~hydration();

		void update(int);
		
		int process();

	private: 
		moisture *MoistureProp;
		unsigned int curTimer;
		unsigned int oldTimer;
		unsigned int hydrateTime; 
		bool hydrating;
		bool hydrateProcess;
		int fatalError;


		int hydrate(int);
		void setup();

		void enable() override;

};

#endif
#endif