#include "serialMonitor.h"
#if SERIALMONITOR
const char *spiner[] = {" -", " \\", " -", " /"};
int a = 0;

serialMonitor::serialMonitor(){
	Serial.begin(BAUDRATE); 
}

char* getTiime(unsigned long int ms){

  unsigned long int milliseconds = ms;
  unsigned long int seconds = milliseconds / 1000;
  milliseconds %= 1000;

  int minutes = seconds / 60;
  seconds %= 60;

  unsigned long int hours = minutes / 60;
  minutes %= 60;

  char tmp[21];
  sprintf(tmp, "%d:%d:%d\0", hours, minutes, seconds);
  Serial.print(hours);
    Serial.print(":");
    Serial.print(minutes);
    Serial.print(":");
    Serial.print(seconds);
  return tmp;
} 

void serialMonitor::update(){
  static unsigned long int oldTime = millis();

  modules* LightMeter = modules::Manager->findObj(LIGHTMETER_ID);
  modules* Thermistor = modules::Manager->findObj(THERMISTOR_ID);
  modules* DHTSensor = modules::Manager->findObj(DHT_ID);
  modules* TDSMeter = modules::Manager->findObj(TDS_ID);
  modules* PHMeter = modules::Manager->findObj(PH_ID);
  modules* Fridge = modules::Manager->findObj(FRIDGE_ID);
  modules* Heater = modules::Manager->findObj(HEATER_ID);
  modules* Ultrasonic = modules::Manager->findObj(ULTRASONIC_ID);
  modules* DigitalThermo = modules::Manager->findObj(DIGITALTHERMO_ID);
  modules* Rotary = modules::Manager->findObj(ROTARY_ID);


  unsigned long int exTime = (millis()-oldTime) - serialMonitor::ddelay;
  oldTime = millis();

 // for (int i = 0; i != 10; i++) 
    Serial.print("\033[2J");  // minicom clear
   

  Serial.print(F("Response : "));
  Serial.print(exTime);
  Serial.print(F("Ms | Mem : "));

  Serial.print(freeMemory());
  Serial.print(F(" | "));
  Serial.print(getTiime(millis()));
  Serial.print(F(" | "));
  Serial.println(spiner[a]);
  Serial.println(F("---------------------------------------------- "));
/*  Serial.print("Mode : ");
  Serial.print((this->HBox->grow?"Grow":(this->HBox->bloom?"bloom": "standby")));
  Serial.print(" | ");*/

  #if DHTSENSOR 
    Serial.print(F("Air Humidity : "));
    Serial.print((int) DHTSensor->getFloat("humidity"));
    Serial.print(F("% | Temp : "));
    Serial.print(DHTSensor->getFloat("temperature"));
    Serial.println(F("C"));
  #endif

  #if DIGITALTHERMO
    Serial.print(F("Water Temp : "));
    Serial.print(DigitalThermo->getFloat("temperature"));

    Serial.print(F("C "));
  #endif


  #if TDS
    Serial.print(F("| EC : "));
    Serial.print(TDSMeter->getInt("ec"));
    Serial.print("PPM ");
  #endif

  #if PH
    Serial.print("| PH : ");
    Serial.print(PHMeter->getFloat("ph"));
  #endif

  Serial.println();
  Serial.println();

  #if LIGTHMETER
    Serial.print(F("Light : "));
    Serial.print((LightMeter->getBool("lighting") ? "on" : "off"));
     Serial.print(F(" ( "));
     Serial.print(LightMeter->getInt("lux"));
     Serial.println(F(" ) "));
  #endif

  #if HEATER   
    Serial.print(" | Heater : ");
    Serial.print((Heater->getBool("heating") ? "on" : "off"));
  #endif

  #if FRIDGE
    Serial.print(F(" | fridge : "));
    Serial.print((Fridge->getBool("fridging") ? "on" : "off"));
  #endif

  #if THERMISTOR
    Serial.print(F(" | Fridge Temp : "));
    Serial.print(Thermistor->getFloat("temperature"));
    Serial.print(F("C "));
  #endif

  #if ULTRASONIC  
    Serial.print(F(" | Ultrasonic : "));
    Serial.println((Ultrasonic->getBool("enabled") ? "on" : "off"));
  #endif

  Serial.println(F("---------------------------------------------- "));
/*
  for (int i = 0; i != (int) PMax; i++) {
    Serial.print("Pot [");
    Serial.print(i+1);
    if(!this->HBox->pot[i].isConnected) {
      Serial.print("] Moisture : ");
      Serial.print(this->HBox->pot[i].moisture);
      Serial.print("%");
      Serial.print(" - (");
      Serial.print(this->HBox->pot[i].moistureValue);
      Serial.print(") ");
      if(this->HBox->pot[i].stabilized)  Serial.print(" | stabilized ");
      else Serial.print(" | unstable ");
      Serial.print("| Hydra²te Cycle : ");
      Serial.println(this->HBox->pot[i].hydrateCycle);
    } else  Serial.println("] Disconnected");
  }*/
  Serial.println(F(""));
  Serial.println(F("Activity"));
  Serial.println(F("---------------------------------------------- "));

  a = a + 1;
  if (a > 3) a = 0;

}
/*

void serialMonitor::update(modulesManager* ModManager){ 
  modules::update(ModManager); 
}*/
#endif