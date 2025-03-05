#include "screen.h"
#if SCREEN
#include <Arduino.h>


#define UU8G  2

#if UU8G
	#include <U8glib.h>

	#if defined(SCREEN_SH1106)
		U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE); 
	#elif defined(SCREEN_SSD1306)
		U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_FAST|U8G_I2C_OPT_FAST);  
		//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);
	#endif
#endif

#if UU8G2
	#include <U8g2lib.h>
	#include <Wire.h>
	
	#if defined(SCREEN_SSD1306)
		U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);
	#endif
#endif


screen::screen() {
	#if UU8G2
		u8g.begin();
		u8g.clearBuffer();	
		u8g.drawXBMP(30, 0, 67, 64, boot);
 		u8g.sendBuffer();
	#endif

	#if UU8G
		//u8g.setRot180();
		u8g.firstPage(); 
		do {
	   	u8g.drawXBMP(30, 0, 67, 64, boot);
		} while( u8g.nextPage() );
	#endif

	for(int i = 0; i < 3; i++){
		this->Animations[i] = new animation;
		this->Animations[i]->frames = 2;
		this->Animations[i]->frame = new const void*[this->Animations[i]->frames]();
		//this->Animations[i]->frame = (unsigned char) malloc(sizeof(mini_light1) * this->Animations[0]->frames);
	}


	this->Animations[0]->frame[0] = &mini_light1;
	this->Animations[0]->frame[1] = &mini_light2;
	this->Animations[0]->height = mini_light1_height;
	this->Animations[0]->width = mini_light1_width;
	this->Animations[0]->interval = 500;

	this->Animations[1] = new animation; 
	this->Animations[1]->frames = 2;
	this->Animations[1]->frame = new const void*[this->Animations[1]->frames]();
	//this->Animations[1]->frame = (unsigned char) malloc(sizeof(mini_ultrasonic1) * this->Animations[1]->frames);
	this->Animations[1]->frame[0] = &mini_ultrasonic1;
	this->Animations[1]->frame[1] = &mini_ultrasonic2;
	this->Animations[1]->height = mini_ultrasonic1_height;
	this->Animations[1]->width = mini_ultrasonic1_width;
	this->Animations[1]->interval = 300;

	this->Animations[2] = new animation;
	this->Animations[2]->frames = 2;
	this->Animations[2]->frame = new const void*[this->Animations[2]->frames]();
	//this->Animations[2]->frame = (unsigned char) malloc(sizeof(mini_heater1) * this->Animations[2]->frames);
	this->Animations[2]->frame[0] = &mini_heater1;
	this->Animations[2]->frame[1] = &mini_heater2;
	this->Animations[2]->height = mini_heater1_height;
	this->Animations[2]->width = mini_heater1_width;
	this->Animations[2]->interval = 250;

	/*this->Header = malloc(sizeof(header));*/
  this->Header = new header;
	this->Header->Next = nullptr;
	this->Header->Prev = nullptr;
	this->Header->id = NULL;

	//this->func = *(modules*) &this->update;
/*	modules::setVoid("obj", (screen*) this);
	modules::setVoidArr("hb", (char**)  &hBuffer);*/
	//hBuffer = (char **) malloc(10*sizeof(char*));
	hBuffer = (char **) new char*[10](nullptr);
	screen::loadMenu();
}

bool headerSearch(header *Header, int id){
  header *tmp = Header;
	tmp = Header;

	while(tmp) {
		if(tmp->id == id) {
			return true;
		} 
		
		tmp = (header*)(tmp->Next); 
	}

	if(!tmp) free(tmp);

	return false;
}

void headerAdd(header *cur, int id, animation *Animation){	
	if(headerSearch(cur, id)) return;

	if (!cur->id) {
		cur->Animation = Animation;
		cur->id = id;
		cur->Prev = NULL;
		cur->Next = NULL;
	} else {
		while(cur->Next) cur = (header *)(cur->Next);

    header *newH = new header;
		newH->Animation = Animation;
		newH->Prev = cur;
		newH->id = id;
		newH->Next = NULL;

		cur->Next = newH;
	} 
}

void headerRemove(header *Header, int id){
	header *tmp = Header;

	while(Header) {
		if(Header->id == id) {
			if(Header->Next && Header->Prev) {
				tmp = (header *)(Header->Prev);
				tmp->Next = (header *)(Header->Next);
			} else if (!Header->Next && Header->Prev)  {
				tmp = (header *)(Header->Prev);
				tmp->Next = NULL;
			} else if (Header->Next && !Header->Prev) {
				tmp = (header *)(Header->Next);
				tmp->Prev = NULL;
			}

			if (!Header->Next && !Header->Prev) {
				Header->Animation = NULL;
				Header->id = NULL;
				Header->Next = NULL;
			} else {
        delete Header;
				Header = tmp;
			}

			return;
		} 

	    Header = (header *)(Header->Next);
	}

	return;
}

const void* animate(animation *Animation){
	Animation->time = millis();

	if (Animation->curFrame > Animation->frames)
		Animation->curFrame = 1;

	const void* tmp = Animation->frame[Animation->curFrame - 1];
	if((Animation->time-Animation->curTime) > Animation->interval){
		Animation->curFrame = Animation->curFrame + 1;
		Animation->curTime = Animation->time;
	}
	
	return tmp;
}

/*void screen::write(char* str ){
	for (int i = 0; (sizeof(hBuffer) / sizeof(hBuffer[0])); i++){
		if (!hBuffer[i] || strcmp(hBuffer[i], "") == 0 || hBuffer[i] == str){
			hBuffer[i] = str;
			break;
		}
	}
}*/

void screen::write(char* str){
	for(int i = 0; i <= 10; i++){
		if ((void*)(&hBuffer[i]) == (void*)(str)) {
			return;
		}
	}

	for(int i = 0; i <= 10; i++){
		if(!strcmp(hBuffer[i], str)) {
			hBuffer[i] = str;
			return;
		} else if(!hBuffer[i] || !strcmp(hBuffer[i], "") || hBuffer[i] == str) {
			hBuffer[i] = str;
			return;
		} 
	}
}

/*void screen::write(char* str ){
	for (int i = 0; i < 9; i++){
		if (!hBuffer[i] || strcmp(hBuffer[i], "") == 0 || strcmp(hBuffer[i], str) == 0){
			if(hBuffer[i]) delete[] hBuffer[i];
			hBuffer[i] = strdup(str);
			hBuffer[i] = str;
			break;
		}
	}
}*/

void screen::drawHeader(){
	modules* LightMeter = modules::Manager->findObj(LIGHTMETER_ID);
	modules* PhotoResistor = modules::Manager->findObj(PHOTORESISTOR_ID);
  modules* DHTSensor = modules::Manager->findObj(DHT_ID);
  modules* Ultrasonic = modules::Manager->findObj(ULTRASONIC_ID);
  modules* Heater = modules::Manager->findObj(HEATER_ID);

	/*static header *tmp = malloc(sizeof(header));*/
    static header *tmp = new header;
	/*static animation *Animation = malloc(sizeof(animation)+1);*/
    static animation *Animation = new animation;
	u8g.setColorIndex(1);

	headerAdd(this->Header, 1, screen::Animations[0]);
	headerAdd(this->Header, 2, screen::Animations[2]);
	headerAdd(this->Header, 3, screen::Animations[1]);

	/*if(LightMeter && LightMeter->getBool("lighting")) headerAdd(this->Header, 1, screen::Animations[0]);
	else headerRemove(this->Header,1);*/

	/*if(PhotoResistor && PhotoResistor->getInt("lux") > 0) headerAdd(this->Header, 1, screen::Animations[0]);
	else headerRemove(this->Header,1);*/
	
	/*if(Heater && Heater->getBool("heating")) headerAdd(this->Header, 2, screen::Animations[2]);
	else headerRemove(this->Header, 2);
	
	if(Ultrasonic && Ultrasonic->getBool("enabled")) headerAdd(this->Header, 3, screen::Animations[1]);
	else headerRemove(this->Header, 3);*/

	tmp = this->Header;
	u8g.setFont(u8g_font_u8glib_4);
	char str[10];
	int pos = 0;
	
	while (tmp && tmp->id > 0) { 
		Animation =  (animation*) tmp->Animation;

		u8g.drawXBMP(pos, 0, Animation->width, Animation->height, (const u8g_pgm_uint8_t*) animate(Animation));
		pos = pos + 17;

		tmp = (header*)(tmp->Next);
	} 

	u8g.drawXBMP( mini_light1_width + 10 + mini_ultrasonic1_width + 10 + mini_heater1_width  + 15 , 0, mini_humidity_width, mini_humidity_height, mini_humidity);
  u8g.drawStr(75, 6, ( DHTSensor ? strcat(this->intToChar(DHTSensor->getFloat("humidity"),  str),"%") : 0));
	
	u8g.drawXBMP( mini_light1_width + 10 + mini_ultrasonic1_width + 10 + mini_heater1_width  + 15 + mini_humidity_width + 25, 0, mini_temp_width, mini_temp_height, mini_temp);
	
	#if UU8G 
		u8g.setPrintPos(103, 6);
	#else 
		u8g.setCursor(103, 6);
	#endif
	
	u8g.print(( DHTSensor ? this->floatToChar(DHTSensor->getFloat("temperature"),  str) : 0));
	u8g.write(0xB0);
	u8g.print("c ");
	u8g.drawLine(0, 11, 130, 11);
}

void screen::loadMenu() {
		screen::_Menu = new void*;
    screen::_Menu[0] = new Menu("MainMenu");

		screen::_Menu[0]->_Items = new Items*[5];
    screen::_Menu[0]->_Items[0] = new Items("Home"/*, (int*) &(this->level)*/);
    /**((bool*)screen::_Menu[screen::MIndex]->_Items[screen::IIndex]->action) = false;*/
    screen::_Menu[0]->_Items[1] = new Items("Modules");
    screen::_Menu[0]->_Items[2] = new Items("DgTest", &screen::drawDialog, *this);
    screen::_Menu[0]->_Items[3] = new Items("Temp");
    screen::_Menu[0]->_Items[4] = new Items("light");    
}

bool toggle = false;
void screen::drawDialog(){
	modules* Rotary = modules::Manager->findObj(ROTARY_ID);
	Rotary->setBool("state", false);
	if(screen::level != 2) {
		screen::level = 2;

		return;
	}

  u8g.setColorIndex(0);
  u8g.drawBox(5, 5, 118, 54);

  // Draw the static text
  u8g.setColorIndex(1);
  u8g.drawFrame(4, 4, 119, 55);
  u8g.setFont(u8g_font_6x10);
  u8g.drawStr(20, 35, "test");
  
  if (millis() % 1000 > 900)
    toggle = !toggle;
  
  
  u8g.setColorIndex(toggle ? 0 : 1); 
  u8g.drawBox(65, 30, 30, 8);
  u8g.setColorIndex(!toggle ? 0 : 1);
  u8g.drawStr(70, 35, "125");
  u8g.setColorIndex(1);
  u8g.setFont(u8g_font_u8glib_4);
}

/*void screen::control(int &selected, int &offsetOver, int &maxLine){
	modules* Rotary = modules::Manager->findObj(ROTARY_ID);

	static int lastpos = Rotary->getInt("pos");
	static unsigned long int timee = millis();

	int r = Rotary->getInt("pos");
	if(r != lastpos) timee = millis();

	screen::MIndex = 0;

	int maxScreenLine = 2;

	if (r > lastpos) {
		if((selected + offsetOver) == (maxLine -1)){
			selected = 0;
			offsetOver = 0;

		} else {
			if(selected >= maxScreenLine && (offsetOver + selected ) < (maxLine-1)) offsetOver=offsetOver+1;
			else if (selected < maxScreenLine ) selected=selected+1;
		}

		lastpos = r;
	} else if (r < lastpos) {
		if((selected + offsetOver) == 0){
			selected = maxScreenLine;
			offsetOver = (maxLine -1) - maxScreenLine;
		} else {
			if (selected > 0 && offsetOver > 0 ) selected = selected-1;
			else if (selected == 0 && offsetOver > 0) offsetOver = offsetOver-1;
			else if (selected > 0 && offsetOver == 0) selected = selected-1;
		}

		lastpos = r;
	}

	screen::IIndex = selected+offsetOver;

	if ((Rotary && (Rotary->getBool("state") && !Rotary->getBool("istState"))) && screen::_Menu[screen::MIndex]->_Items[screen::IIndex]->action != nullptr) {
		 *((int*)screen::_Menu[screen::MIndex]->_Items[screen::IIndex]->action) = 0;
		 // *(void (*)()) screen::_Menu[screen::MIndex]->_Items[screen::IIndex]->action(); 
		 //(*(void (*)()) screen::_Menu[screen::MIndex]->_Items[screen::IIndex]->action)();

		 // void (*action)() = screen::_Menu[screen::MIndex]->_Items[screen::IIndex]->action;
		  //action();

		Rotary->setBool("state", false);
	} else if((millis()-timee) > 10000){
	 	screen::level = 0;
	}
	Rotary->setBool("state", false);
}*/

/*void screen::control(int &selected, int &offsetOver, int &maxLine){
	modules* Rotary = modules::Manager->findObj(ROTARY_ID);

	static int lastpos = Rotary->getInt("pos");
	static unsigned long int timee = millis();

	int r = Rotary->getInt("pos");
	if(r != lastpos) timee = millis();

	screen::MIndex = 0;

	int maxScreenLine = 2;

	if (r > lastpos) {
		if((selected + offsetOver) == (maxLine -1)){
			selected = 0;
			offsetOver = 0;

		} else {
			if(selected >= maxScreenLine && (offsetOver + selected ) < (maxLine-1)) offsetOver=offsetOver+1;
			else if (selected < maxScreenLine ) selected=selected+1;
		}

		lastpos = r;
	} else if (r < lastpos) {
		if((selected + offsetOver) == 0){
			selected = maxScreenLine;
			offsetOver = (maxLine -1) - maxScreenLine;
		} else {
			if (selected > 0 && offsetOver > 0 ) selected = selected-1;
			else if (selected == 0 && offsetOver > 0) offsetOver = offsetOver-1;
			else if (selected > 0 && offsetOver == 0) selected = selected-1;
		}

		lastpos = r;
	}

	screen::IIndex = selected;

	if ((Rotary && (Rotary->getBool("state") && !Rotary->getBool("istState"))) && screen::_Menu[screen::MIndex]->_Items[screen::IIndex]->action != nullptr) {
		 *((int*)screen::_Menu[screen::MIndex]->_Items[screen::IIndex]->action) = 0;
		 // *(void (*)()) screen::_Menu[screen::MIndex]->_Items[screen::IIndex]->action; action();
		  //(*(void (*)()) screen::_Menu[screen::MIndex]->_Items[screen::IIndex]->action)();

		  ((void*()) screen::_Menu[screen::MIndex]->_Items[screen::IIndex]->action)();

		Rotary->setBool("state", false);
	} else if((millis()-timee) > 10000){
	 	screen::level = 0;
	}
	Rotary->setBool("state", false);
}*/

 void screen::control(int &selected, int &offsetOver, int &maxLine){
	modules* Rotary = modules::Manager->findObj(ROTARY_ID);

	static int lastpos = Rotary->getInt("pos");
	static unsigned long int timee = millis();

	int r = Rotary->getInt("pos");
	if(r != lastpos) timee = millis();

	screen::MIndex = 0;

	int maxScreenLine = 2;

	if (r > lastpos) {
		if((selected + offsetOver) == (maxLine -1)){
			selected = 0;
			offsetOver = 0;

		} else {
			if(selected >= maxScreenLine && (offsetOver + selected ) < (maxLine-1)) offsetOver=offsetOver+1;
			else if (selected < maxScreenLine ) selected=selected+1;
		}

		lastpos = r;
	} else if (r < lastpos) {
		if((selected + offsetOver) == 0){
			selected = maxScreenLine;
			offsetOver = (maxLine -1) - maxScreenLine;
		} else {
			if (selected > 0 && offsetOver > 0 ) selected = selected-1;
			else if (selected == 0 && offsetOver > 0) offsetOver = offsetOver-1;
			else if (selected > 0 && offsetOver == 0) selected = selected-1;
		}

		lastpos = r;
	}

	screen::IIndex = selected;

	if ((Rotary && (Rotary->getBool("state") && !Rotary->getBool("istState"))) && screen::_Menu[screen::MIndex]->_Items[screen::IIndex]->func != nullptr) {
		 //*((int*)screen::_Menu[screen::MIndex]->_Items[screen::IIndex]->action) = 0;
		 // *(void (*)())screen::_Menu[screen::MIndex]->_Items[screen::IIndex]->action;
     // action();*
		 // (*(void (*)())screen::_Menu[screen::MIndex]->_Items[screen::IIndex]->action)();
		Rotary->setBool("state", false);


		//(*(void (*)()) _Menu[MIndex]->_Items[IIndex]->action)();

		void* obj = _Menu[MIndex]->_Items[IIndex]->obj;
		void (*func)(void*) = ((void (*)(void*)) _Menu[MIndex]->_Items[IIndex]->func);
		//((*(void*) func)(*(void*) obj));
		 if (func) {
	       func(obj);
	   }
		//(((*(func_type*)MyMenu[MIndex]._Items[IIndex]->func))( *(object_type*)MyMenu[MIndex]._Items[IIndex]->obj));

	} else if((millis()-timee) > 10000){
	 	screen::level = 0;
	}
	Rotary->setBool("state", false);
}

void screen::drawMenu() {
	static int offsetOver = 0;
	static int selected = 0;
	int maxLine = 5;

	u8g.setFont(u8g_font_u8glib_4);

	for (int i = offsetOver; i < maxLine; i++){
		int offsetSelected = (i - offsetOver);
		if(selected == offsetSelected) {
      u8g.setColorIndex(1);
      u8g.drawBox(0, (15 * (selected+1)), 128, 10);
    }

    u8g.setColorIndex((selected == offsetSelected ? 0 : 1));
    u8g.drawStr(0, (15 * (offsetSelected+1)) + 7, screen::_Menu[screen::MIndex]->_Items[i]->name.c_str());
	}

	screen::control(selected, offsetOver, maxLine);
}

void screen::draw(){
	modules* Rotary = modules::Manager->findObj(ROTARY_ID);
	
 	if ((Rotary && (Rotary->getBool("state") && !Rotary->getBool("istState"))) && !screen::level)  {
 		screen::level = 1;
 		Rotary->setBool("state", false);
 	}

	 #if UU8G 
		u8g.firstPage(); 
		do {
			this->drawHeader();
			switch(screen::level){
				case 0:
					this->drawNotes();
					break;

				case 1:
					this->drawMenu();
					break;

				case 4:
					this->drawDialog();
					break;
			}

	  } while(u8g.nextPage());
	 #endif


	 #if UU8G2
	  u8g.clearBuffer();
	  this->drawHeader();
	  this->drawNotes();
	  u8g.sendBuffer();	
	 #endif
}

void screen::update(){
	const char *spiner[] = {" -", " \\", " -", " /"};
	static int a = 0;
	screen::write((char *)spiner[a]);
	a = a + 1;
  if (a > 3) a = 0;

	screen::draw();

	for (int i = 0;i < 10 && hBuffer[i] != nullptr; i++ )
		hBuffer[i]= "";
}

void screen::drawNotes(){
	for (int i = 0;  i < 10 && hBuffer[i] != nullptr; i++ ){
		if(hBuffer[i]) {
			u8g.drawStr(0, 15 +(10 * (i)+5), hBuffer[i]);
		#if UU8G2
			hBuffer[i] = "";
		#endif
		}
	}
}

char* screen::floatToChar(float f, char str[]){
  sprintf(str, "%d.%01d", (int)f, (int)(f*100)%100);
  return str;
}

char* screen::intToChar(int i, char str[]){
  sprintf(str, "%d", i);
  return str;
}

#endif