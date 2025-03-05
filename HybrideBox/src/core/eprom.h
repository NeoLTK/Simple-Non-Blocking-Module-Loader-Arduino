#ifndef Eeprom_h
#define Eeprom_h
#include "../../configuration.h"
#if EPROMM

#include <EEPROM.h>
#include <Arduino.h>

class eprom {

	public:
		eprom(int);
		eprom();

		int writeLongInt(int);
		int readLongInt(int);
		int updateLongInt(int, int);
		int writeStruct(void*);
		int available();

		void readStruct(int);

		static eprom* Eprom;
		static eprom *load();

	private:
		int bites;
		int curBite;
		int curIndex;
    	int *eeVar;

};

#endif
#endif
