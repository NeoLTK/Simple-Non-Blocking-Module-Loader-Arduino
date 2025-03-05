#ifndef	serialMonitor_H
#define serialMonitor_H


#include "../../configuration.h"
#if SERIALMONITOR
#include <Arduino.h>
#include "structure.h"
#include "MemoryFree.h"
#include "../modules/modules.h"

class serialMonitor : public modules{
	public: 
		serialMonitor();
		~serialMonitor();

		void update();

	private:
		HybrideBox* HBox;
};

#endif
#endif