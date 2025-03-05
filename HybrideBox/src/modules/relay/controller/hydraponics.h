#ifndef Hydraponics_H
#define Hydraponics_H

#include "../../../../configuration.h"
#if HYDRO
#include "../relay.h"


class hydraponics : public relay {
	//using relay::relay;

	public:
		hydraponics(int pinout);

		~hydraponics();

		void update();
		/*bool getStatus() override;*/

	private: 
		unsigned long int curTimer;
		unsigned long int oldTimer;
		unsigned long int hydrateTime; 
		unsigned long int over;
		unsigned long int rollOver;
		bool hydrating;
		bool force;
		


		

};

#endif
#endif