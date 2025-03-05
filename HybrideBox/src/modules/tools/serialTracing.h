#ifndef	serialTracing_H
#define serialTracing_H

#include "../../../configuration.h"

#if SERIALTRACING
#include <Arduino.h>
#include "../modules.h"

struct instruction {
	char* name;
	char* type;
	void* addr;

	void* next;
	void* prev;
};

class serialTracing : public modules{
	public: 
		serialTracing();
		~serialTracing();

		void update();
		void add(char*, void*);

	private:
		instruction* Instruction;
};

#endif
#endif