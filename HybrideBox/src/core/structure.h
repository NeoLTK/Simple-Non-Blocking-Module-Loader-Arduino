#ifndef Structure_h
#define Structure_h

#include "../../configuration.h"

struct Pots {
	int moisture;
	int moistureValue;
	int hydrateCycle;

	bool stabilized;
	bool isConnected;
};




struct HybrideBox{
	bool bloom;
	bool grow;
	
    float temperature;
    float humidity;
    float lux;

    bool light;
    bool heater;
    bool ultrasonic;

    bool fridge;

    double thermistorValue;
    double thermistorTempC;
    double thermistorTempF;

    float waterEC;
    float waterPH;


    Pots pot[PMax];
} ;


#endif