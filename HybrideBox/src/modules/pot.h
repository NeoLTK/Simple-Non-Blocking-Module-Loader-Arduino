#if POT
#ifndef Pot_h
#define Pot_h

#include "../core/structure.h"

#include "tools/moisture.h"
#include "relay/controller/hydration.h"

#include "modules.h"

class pot : public modules {
	public:
		int hydrateCycle;
		
		pot(struct HybrideBox*, int, int);
		~pot();

		int update(int);
		void update();

		int getMoisturePercent();
		int getMoistureValue();
		bool isStabilized();
		bool isConnectedMoisture();

	private:
		moisture *Moisture;
		hydration *Hydration;

		int curTime;
		int lasHydTime;

		int hydrationInterval;

		HybrideBox *HBox;
	
};

#endif
#endif