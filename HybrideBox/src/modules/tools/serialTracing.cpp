#include "serialTracing.h"
#if SERIALTRACING

serialTracing::serialTracing(){
	Serial.begin(BAUDRATE); 
}

void serialTracing::add(char* name, void* addr){
  instruction *New = (instruction*) malloc(sizeof(instruction));
  New->next = NULL;

  instruction *cur =  this->Instruction;   

  while(cur->next) 
    cur = cur->next;

  cur->next = New;
  cur->name = name;
  cur->addr = addr;
}

void serialTracing::update(){
  instruction *tmp = this->Instruction; 
  do {    
    if(tmp->next) {
      Serial.print(tmp->name);  
      if(tmp->type == "int")
        Serial.print(*(int*) tmp->addr);  
      else if (tmp->type =="float")
        Serial.print(*(float*) tmp->addr);  

      Serial.println(" <--");
    } 
    if(tmp->next) tmp = tmp->next;
  } while(tmp->next);
 
}
#endif