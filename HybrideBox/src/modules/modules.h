#ifndef Modules_h
#define Modules_h
//#include <avr_stl.h>
#include <Arduino.h>
#include "../core/structure.h"
//#include <Arduino_AVRSTL.h>
//#include <new>


struct modules;
struct bridge {
	char* var;
	void* addr;
    bridge *next;
};

class modulesManager {
	public:
		modulesManager();
		~modulesManager();

		void update();

		modules* find(int);
		modules* findObj(int);
		modules* add(modules*);
		void add(modules*, int);
		void add(modules*, int, int);


	/*	void initBridge(modules*);
		bridge* findBridgedModules(int);
		bridge* findBridgeVar(int, char*);
		bridge* findBridgeNewVar(int, char*);

		void setVoid(int, char*, void*);
		void setInt(int, char*, int);
		void setFloat(int, char*, float);
		void setBool(int, char*, bool);

		void* getVoid(int, char*);
		int getVoidInt(int, char*);
		int getInt(int, char*);
		float getVoidFloat(int, char*);
		float getFloat(int, char*);
		bool getVoidBool(int, char*);
		bool getBool(int, char*);*/
	
	private:
		modules *Modules;
 	
};


class modules {
	public:
		bool active;
		int id;
		unsigned long int ddelay;
		unsigned long int lastUpdate;

		modules() : active(true), lastUpdate(millis()) {
			this->Bridge = nullptr;
			this->ddelay = 500;
		};

		virtual void update() = 0;

		bridge* Bridge;

		void initBridge();
		void setInt(const char*, int);
		void setFloat(const char*, float);
		void setBool(const char*, bool);

		virtual void setVoid(const char*, void*);
		//virtual void setVoidArr(char*, void**);

		int getInt(const char*);
		float getFloat(const char*);
		bool getBool(const char*);
		void* getVoid(const char*);
		//void** getVoidArr(char*);
		int getVoidInt(const char*);
		float getVoidFloat(const char*);
		bool getVoidBool(const char*);

		modulesManager* Manager;
	
		modules *prev;
		modules *next;

	private:
		bridge* findBridgeVar(bridge*, const char*);
		bridge* findBridgeNewVar(bridge*, const char*);

	
};

//modules* modulesManager::Modules = (modules*) ./

#endif