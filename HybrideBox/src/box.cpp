#include "box.h"

/*void * operator new(size_t size);
void operator delete(void * ptr);
void * operator new(size_t size)
{
  return malloc(size);
}

void operator delete(void * ptr)
{
  free(ptr);
}*/

box::box(){
	this->Modules = new modulesManager();

	#if SERIALMONITOR
		this->Modules->add((modules*) new serialMonitor(), 999, 501);
	#endif

	#if SERIALTRACING
		this->Modules->add((modules*) new serialTracing());
	#endif
	
	#if LIGTHMETER
		this->Modules->add((modules*) new lightMeter(), LIGHTMETER_ID);
	#endif

	#if DHTSENSOR 
		this->Modules->add((modules*) new sht(DHT_pin), DHT_ID);
	#endif

	#if HEATER 
		this->Modules->add((modules*) new heater(HEATER_pin), HEATER_ID); 
	#endif

	#if FRIDGE 
		this->Modules->add((modules*) new fridge(FRIDGE_pin), FRIDGE_ID); 
	#endif

	#if ULTRASONIC
		this->Modules->add((modules*) new ultrasonic(ULTRASONIC_pin), ULTRASONIC_ID);
	#endif

    #if HYDRO
    	this->Modules->add((modules*) new hydraponics(HYDROPONIC_pin), HYDROPONICS_ID);
    #endif

	#if ROTARY
		this->Modules->add((modules*) new rotary(PHOTORESISTOR_pin, PHOTORESISTOR_pin), ROTARY_ID, 0);
	#endif

	#if SCREEN
		this->Modules->add((modules*) new screen(), SCREEN_ID, 100);
	#endif

    #if MOISTURE || HYDRATION
		/*for (int i = 0; i != (int) PMax; i++)
	    	this->Modules->add((modules*) new pot(HBox, A0+i, 9+i));*/
		this->Modules->add((modules*) new moisture(MOISTURE_pin), MOISTURE_ID);
	#endif

	#if TDS   
		this->Modules->add((modules*) new tdsMeter(TDS_pin), TDS_ID);
	#endif

	#if PH   
		this->Modules->add((modules*) new phMeter(PH_pin), PH_ID);
	#endif

	#if THERMISTOR
		this->Modules->add((modules*) new thermistor(THERMISTOR_pin), THERMISTOR_ID);
	#endif

    #if CAPACITIVE
		this->Modules->add((modules*) new capacitive(CAPACITIVE_SEND_pin, CAPACITIVE_RECV_pin), CAPACITIVE_ID);
	#endif

	#if DIGITALTHERMO
		this->Modules->add((modules*) new digitalThermo(DIGITALTHERMO_pin), DIGITALTHERMO_ID);
	#endif

	#if PHOTORESISTOR
		this->Modules->add((modules*) new photoResistor(PHOTORESISTOR_pin), PHOTORESISTOR_ID, 100);
	#endif


	#if LIGHT
		this->Modules->add((modules*) new light(LIGHT_pin), LIGHT_ID);
	#endif
}	

void box::update(){
	this->Modules->update();
	// Modifie pointer Bridge
	// 
	//modules* Rotary = this->Modules->find(ROTARY_ID);
	//int* pos = Rotary->getVoid("pos");
	//*pos = *pos + 1; 

	//Assing pointer
	// /!\ Require header object
	screen* Screen =  (screen*) this->Modules->find(SCREEN_ID);
	Screen->write("qsdsqdqs");
	


	modules* Rotary = this->Modules->find(ROTARY_ID);
	int pos_int = *(int*) Rotary->getVoid("pos");

	char buffer[5]; 
	sprintf(buffer, "%d", pos_int); 
	Screen->write(buffer);

	char str[5];
	sprintf(str, "%lu", millis() % 1000);
	Screen->write(str);

	int state = *(int*) Rotary->getVoid("state");
	char buff[5]; 
	sprintf(buff, "%d", state); 
	Screen->write(buff);

	//Modifie  pointerArray Bridge
	//
	/*modules* Sscreen = this->Modules->find(SCREEN_ID);
	char** hBuffer = (char**) Sscreen->getVoidArr("hb");
	(*hBuffer)[0] = "tsses2t";*/

	//eprom::load()->available();

}
/*
void hydroponicsSystem(){
	static modules *waterThermistor = this->Modules->find("thermistor");
	static modules *waterPH = this->Modules->find("ph");
	static modules *waterTDS = this->Modules->find("tds");
	static modules *waterFridge = this->Modules->find("fridge");
	static modules *airHeater = this->Modules->find("heater");
	static modules *airValue = this->Modules->find("dht");
	static modules *LightMeter = this->Modules->find("lightmeter");
	static modules *Ultrasonic = this->Modules->find("ultrasonic");
	static modules *ebbflow = this->Modules->find("ebb&flow");
	static unsigned long int time = millis();

	if(airValue->curTemp <= HEATER_low_trigger)
		airHeater->enable();
	else if (airValue->curTemp >= HEATER_higt_trigger)
		airHeater->disable();

	if(waterThermistor->curTemp >= FRIDGE_hight_trigger)
		waterFridge->enable();
	else if (waterThermistor->curTemp <= FRIDGE_hight_trigger)
		waterFridge->disable();

	if(LightMeter->light == true) {
		if(airValue->curHumi <= HEATER_low_trigger)
			airHeater->enable();
		else if(airValue->curHumi >= HEATER_higt_trigger) 
			airHeater->disable();


	}

}*/