#include "modules.h"

modulesManager::modulesManager()  {
	this->Modules = nullptr;
}

void modulesManager::update(){
	if(this->Modules == nullptr) return;

	modules *tmp = this->Modules; 
	do {		
		if(tmp->next) {
			if((millis() - tmp->lastUpdate) > tmp->ddelay){
				tmp->update();	
				tmp->lastUpdate = millis();	
			}

			tmp = tmp->next;
		} 
	} while(tmp->next);
}

modules* modulesManager::find(int id){
	modules *tmp =  this->Modules;
	do {
		if(tmp->id == id) return tmp;
		if(tmp->next) tmp = tmp->next;
	} while(tmp->next);

	return nullptr;
}

modules* modulesManager::findObj(int id){
	return modulesManager::find(id);
}

/*modules* modulesManager::add(modules *object){
	modules *New = (modules*) malloc(sizeof(modules));
	New->prev = object;
	New->next = nullptr;

	object->Manager = &(*this);

	modules *cur =  this->Modules;	 

	while(cur->next) 
		cur = cur->next;

	if(cur->prev) { 
		modules *Prev = cur->prev;  
		object->prev = Prev; 

		Prev->next =  object; 
		free(cur);
	} else {
		cur = object;
		this->Modules = object;
	}

	object->next = New;
	return object;
}*/



modules* modulesManager::add(modules *object) {
    if (this->Modules == nullptr) {
        this->Modules = object;
        object->prev = nullptr;
        object->next = nullptr;
    } else {
        modules *cur = this->Modules;
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = object;
        object->prev = cur;
        object->next = nullptr;
    }
    object->Manager = this;
    return object;
}

void modulesManager::add(modules *object, int id){
	modules *Modules = this->add(object);
	Modules->id = id;
}

void modulesManager::add(modules *object, int id, int ddelay){
	modules *Modules = this->add(object);
	Modules->ddelay = ddelay;
	Modules->id = id;
}

/*bridge* modules::findBridgeVar(bridge* Bridge, char* var){
	if(this->Bridge == nullptr) modules::initBridge();

	while(Bridge->next) {
		if(!strcmp(Bridge->var, var)) 
			return Bridge;

		if(Bridge->next) Bridge = Bridge->next;
	}

	return NULL;
}

bridge* modules::findBridgeNewVar(bridge* Bridge, char* var){
	bridge* cur = modules::findBridgeVar(Bridge, var);

	if (!cur) {
		bridge* New = (bridge*) malloc(sizeof(bridge));

		New->var = NULL;
		New->next = NULL;
		
		cur = this->Bridge;

		if(!cur->var){
			free(New);
			return cur;
		} else {
			while(cur->next) 
				cur = cur->next;

			cur->next = New;
		}
		
		return New;
	}

	return cur;
}*/

/*bridge* modules::findBridgeVar(bridge* Bridge, char* var){
	if(this->Bridge == nullptr) modules::initBridge();

	while(Bridge->next) {
		if(!strcmp(Bridge->var, var)) 
			return Bridge;

		if(Bridge->next) Bridge = Bridge->next;
	}

	return nullptr;
}

bridge* modules::findBridgeNewVar(bridge* Bridge, char* var){
	bridge* cur = modules::findBridgeVar(Bridge, var);

	if (!cur) {
		bridge* New = new bridge;

		New->var = nullptr;
		New->next = nullptr;
		
		cur = this->Bridge;

		if(!cur->var){
			delete New;
			return cur;
		} else {
			while(cur->next) 
				cur = cur->next;

			cur->next = New;
		}
		
		return New;
	}

	return cur;
}*/


bridge* modules::findBridgeVar(bridge* Bridge, const char* var) {
	if (this->Bridge == nullptr) modules::initBridge();

	while (Bridge != nullptr) {
		if (!strcmp(Bridge->var, var)) 
			return Bridge;

		Bridge = Bridge->next;
	}

	return nullptr;
}

bridge* modules::findBridgeNewVar(bridge* Bridge, const char* var) {
	bridge* cur = modules::findBridgeVar(Bridge, var);

	if (cur == nullptr) {
		bridge* New = new bridge;

		New->var = nullptr;
		New->next = nullptr;

		if (this->Bridge == nullptr) {
			this->Bridge = New;
			return New;
		}

		cur = this->Bridge;

		while (cur->next != nullptr) 
			cur = cur->next;

		cur->next = New;
		return New;
	}

	return cur;
}



void* modules::getVoid(const char* var) { 
	bridge* Bridge  = modules::findBridgeVar(this->Bridge, var);

	if(Bridge->addr){
		void *addrVal =  Bridge->addr;
		return addrVal;
	}
	else return nullptr;
}

/*void** modules::getVoidArr(char* var) { 
	bridge* Bridge  = modules::findBridgeVar(this->Bridge, var);

	if(Bridge->addr){
		//void **addrVal =  Bridge->arr;
		//return addrVal;
	}
	else return nullptr;
}*/

int modules::getVoidInt(const char* var) { 
	 return *(int*) modules::getVoid(var);
}

int modules::getInt(const char* var) { 
	return modules::getVoidInt(var);
}

float modules::getVoidFloat(const char* var) { 
	return *(float*) modules::getVoid(var);
}

float modules::getFloat(const char* var) {
	return modules::getVoidFloat(var);
}

bool modules::getVoidBool(const char* var){
	return *(bool*) modules::getVoid(var);
}

bool modules::getBool(const char* var) {
	return modules::getVoidBool(var);
}

void modules::initBridge(){
	this->Bridge = new bridge;
	this->Bridge->var = nullptr;
	this->Bridge->next = nullptr;	
}

void modules::setVoid(const char* var, void* addr) {
	bridge* cur = modules::findBridgeNewVar(this->Bridge, var);

	cur->addr = addr;
	cur->var = var;
}
/*
void modules::setVoidArr(char* var, void** addr) {
	bridge* cur = modules::findBridgeNewVar(this->Bridge, var);

	//cur->arr = addr;
	cur->var = var;
}*/

void modules::setInt(const char* var, int value) {
	bridge* Bridge  = modules::findBridgeVar(this->Bridge, var);
	if (Bridge) delete (int*) Bridge->addr;

	int *ptr = new int;
	*ptr = value;

	modules::setVoid(var, (int*) &(*ptr));
}

void modules::setFloat(const char* var, float value) {
	bridge* Bridge  = modules::findBridgeVar(this->Bridge, var);
	if (Bridge) delete (float*) Bridge->addr;
		
	float *ptr = new float;
	*ptr = value;

	modules::setVoid(var, (float*) &(*ptr));
}

void modules::setBool(const char* var, bool value) {
	bridge* Bridge  = modules::findBridgeVar(this->Bridge, var);
	if (Bridge) delete (bool*) Bridge->addr;
	
	bool *ptr = new bool;
	*ptr = value;

	modules::setVoid(var, (bool*) &(*ptr));
}




	/*modules* findType(char *type){
		modules *tmp = this;
		do {
			if(typeid(tmp->object).name() == type) return tmp;
			if(tmp->next) tmp = tmp->next;
		} while(tmp->next);

		return;	
	}*/