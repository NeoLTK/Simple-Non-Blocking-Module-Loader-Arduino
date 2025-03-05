#ifndef Relay_h
#define Relay_h

#include <Arduino.h>
#include "../modules.h"

class relay : public modules {

	public:
		explicit relay(int pin);
		//virtual ~relay() = 0;
		
		//virtual int update() = 0;
		virtual void update(modulesManager*);
		void update();


	protected:
		int pinout;
		bool enabled;
		unsigned long int time;

		bool secureMode;
		bool secure;
		int  trigMode;

		virtual void enable();
		virtual void disable();

		
	
};

#endif