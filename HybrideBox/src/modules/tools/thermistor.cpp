#include "thermistor.h"
#if THERMISTOR


bool integer(float k)
{
    return k == (float)(int)k;
}


thermistor::thermistor(int pinout){
	this->pinout = pinout;
/*  modules::setVoid("temperature", (float*) &this->temperature);*/
}



float thermistor::SteinhartHart(float R)
{

  float equationB1 = this->B_1 * log(R/this->Rref);
  float equationC1 = this->C_1 * pow(log(R/this->Rref), 2);
  float equationD1 = this->D_1 * pow(log(R/this->Rref), 3);
  float equation = this->A_1 + equationB1 + equationC1 + equationD1;
  return pow(equation, -1);
}
void thermistor::setup(){
  modules::setVoid("temperature", (float*) &this->temperature);
}

void thermistor::update(){
  static bool first = true;
/*
  if (first) {
    first = false; 
    thermistor::setup();
  }*/

  int delay = 2000;
  static long int timer = millis();
  static float *buffer = (float*) malloc(sizeof(float) * ( delay /  DELAY));


  if(millis()-timer > delay + 100) {
    float total = 0;
    int i = 0;

    for(i;  i <= ( delay /  DELAY) -1; i++){
      total += buffer[i];
      buffer[i] = 0;
    }

    float moyenne = (float) total / (int) i;
    float V =  moyenne / 1024 * this->V_IN;
    float Rth = (this->Rref * V ) / (this->V_IN - V);
    float kelvin = this->SteinhartHart(Rth);
    float celsius = kelvin - 273.15;

    this->temperature = celsius - 6;
    modules::setVoid("temperature", (float*) &this->temperature);
    /*

    this->HBox->thermistorTempF = kelvin;*/
    timer = millis();
  } else {
    int i = 0;
    for(i; i <= ( delay /  DELAY) && buffer[i] > 1; i++) {}
    buffer[i] = analogRead(this->pinout);
  }


  
}

float thermistor::getTemperature(){
  return this->temperature;
}
#endif