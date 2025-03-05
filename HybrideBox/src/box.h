#ifndef Box_h	
#define Box_h
#include "core/structure.h"
#include "../configuration.h"
#include "modules/modules.h"
#include "core/eprom.h"

#if SERIALMONITOR 
	#include "core/serialMonitor.h"
#endif

#if SERIALTRACING
	#include "modules/tools/serialTracing.h"
#endif

#if DHTSENSOR 
	#include "modules/tools/sht.h"
#endif

#if LIGTHMETER
	#include "modules/tools/lightMeter.h"
#endif

#if ROTARY
	#include "modules/tools/screen/rotary.h"
#endif

#if SCREEN
	#include "modules/tools/screen/screen.h"
#endif

#if TDS
	#include "modules/tools/tdsMeter.h"
#endif

#if PH
	#include "modules/tools/phMeter.h"
#endif

#if THERMISTOR
	#include "modules/tools/thermistor.h"
#endif

#if HEATER
	#include "modules/relay/controller/heater.h"
#endif

#if FRIDGE
	#include "modules/relay/controller/fridge.h"
#endif

#if ULTRASONIC
	#include "modules/relay/controller/ultrasonic.h"
#endif

#if HYDRO
	#include "modules/relay/controller/hydraponics.h"
#endif

#if MOISTURE || HYDRATION
	//#include "modules/pot.h"
	#include "modules/tools/moisture.h"
#endif

#if CAPACITIVE
	#include "modules/tools/capacitive.h"
#endif

#if DIGITALTHERMO
	#include "modules/tools/digitalThermo.h"
#endif

#if PHOTORESISTOR
	#include "modules/tools/photoresistor.h"
#endif

#if LIGHT
	#include "modules/relay/controller/light.h"
#endif

class box {
	public:
		box();
		~box();

		void update();

	private:		
		modulesManager *Modules;
		HybrideBox *HBox;


};

#endif