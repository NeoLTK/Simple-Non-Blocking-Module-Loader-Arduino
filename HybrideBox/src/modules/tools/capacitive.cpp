#include "capacitive.h"
#if CAPACITIVE

CapacitiveSensor   cs_4_2 = CapacitiveSensor(3,8);  

capacitive::capacitive(int pin1, int pin2) {                
   //cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);   
   //cs_4_2.set_CS_Timeout_Millis(100);    
}
void capacitive::update(){
    long start = millis();
    long total1 =  cs_4_2.capacitiveSensor(100);

    Serial.print(millis() - start);        
    Serial.print("\t");                    

    Serial.print(total1);                  
   
}
#endif