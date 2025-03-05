#include "screen.h"
#if SCREEN
#include <Arduino.h>


// declaration U8 crash 
#define UU8G  2

#if UU8G
	#include <U8glib.h>

	#if defined(SCREEN_SH1106)
		U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE); 
	#elif defined(SCREEN_SSD1306)
		U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);  
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



	this->Animations[0] = new animation;
	this->Animations[0]->frames = 2;
	this->Animations[0]->frame = new void*[this->Animations[0]->frames](NULL);
	//this->Animations[0]->frame = (unsigned char) malloc(sizeof(mini_light1) * this->Animations[0]->frames);
	this->Animations[0]->frame[0] = &mini_light1;
	this->Animations[0]->frame[1] = &mini_light2;
	this->Animations[0]->height = mini_light1_height;
	this->Animations[0]->width = mini_light1_width;
	this->Animations[0]->interval = 500;

	this->Animations[1] = new animation; 
	this->Animations[1]->frames = 2;
	this->Animations[1]->frame =   new void*[this->Animations[1]->frames](NULL);
	//this->Animations[1]->frame = (unsigned char) malloc(sizeof(mini_ultrasonic1) * this->Animations[1]->frames);
	this->Animations[1]->frame[0] = &mini_ultrasonic1;
	this->Animations[1]->frame[1] = &mini_ultrasonic2;
	this->Animations[1]->height = mini_ultrasonic1_height;
	this->Animations[1]->width = mini_ultrasonic1_width;
	this->Animations[1]->interval = 300;

	this->Animations[2] = new animation;
	this->Animations[2]->frames = 2;
	this->Animations[2]->frame =   new void*[this->Animations[2]->frames](NULL);
	//this->Animations[2]->frame = (unsigned char) malloc(sizeof(mini_heater1) * this->Animations[2]->frames);
	this->Animations[2]->frame[0] = &mini_heater1;
	this->Animations[2]->frame[1] = &mini_heater2;
	this->Animations[2]->height = mini_heater1_height;
	this->Animations[2]->width = mini_heater1_width;
	this->Animations[2]->interval = 250;

	/*this->Header = malloc(sizeof(header));*/
    this->Header = new header;
	this->Header->Next = NULL;
	this->Header->Prev = NULL;
	this->Header->id = NULL;

	this->menuDraw = false;
	this->curMenu = NULL;
	//this->func = *(modules*) &this->update;
/*	modules::setVoid("obj", (screen*) this);
	modules::setVoidArr("hb", (char**)  &hBuffer);*/
	//hBuffer = (char **) malloc(10*sizeof(char*));
	hBuffer = (char **) new char*[10](NULL);
}

bool headerSearch(header *Header, int id){
	/*header *tmp = malloc(sizeof(header));*/
    header *tmp = Header;
	tmp = Header;

	while(tmp) {
		if(tmp->id == id) {
			return true;
		} 
		
		tmp = tmp->Next;
	}

	if(!tmp) free(tmp);/**/

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
		while(cur->Next) cur = cur->Next;

		/*header *newH = malloc(sizeof(header));*/
        header *newH = new header;
		newH->Animation = Animation;
		newH->Prev = cur;
		newH->id = id;
		newH->Next = NULL;

		cur->Next = newH;
	} 

}


void headerRemove(header *Header, int id){
	header *tmp = Header; /*malloc(sizeof(header));*/

	while(Header) {
		if(Header->id == id) {
			if(Header->Next && Header->Prev) {
				tmp = Header->Prev;
				tmp->Next = Header->Next;
			} else if (!Header->Next && Header->Prev)  {
				tmp = Header->Prev;
				tmp->Next = NULL;
			} else if (Header->Next && !Header->Prev) {
				tmp = Header->Next;
				tmp->Prev = NULL;
			}

			if (!Header->Next && !Header->Prev) {
				Header->Animation = NULL;
				Header->id = NULL;
				Header->Next = NULL;
				/*free(tmp);*/
			} else {
				/*free(Header);*/
                delete Header;
				Header = tmp;
			}

			return;
		} 

	    Header = Header->Next;
	}

	/*free(tmp);*/
	return;
}

unsigned char* animate(animation *Animation){
	Animation->time = millis();

	if (Animation->curFrame > Animation->frames)
		Animation->curFrame = 1;

	unsigned char* tmp = Animation->frame[Animation->curFrame - 1];
	if((Animation->time-Animation->curTime) > Animation->interval){
		Animation->curFrame = Animation->curFrame + 1;
		Animation->curTime = Animation->time;
	}
	
	return tmp;
}

/*void screen::update(){

	header *tmp = malloc(sizeof(header));
	animation *Animation = malloc(sizeof(animation)+1);

	if(HBox->light) headerAdd(this->Header, 1, screen::Animations[0]);
	else headerRemove(this->Header,1);
	
	if(HBox->heater) headerAdd(this->Header, 2, screen::Animations[2]);
	else headerRemove(this->Header, 2);
	
	if(HBox->ultrasonic) headerAdd(this->Header, 3, screen::Animations[1]);
	else headerRemove(this->Header, 3);

	tmp = this->Header;

	u8g.firstPage(); 
	do {
		u8g.setFont(u8g_font_u8glib_4);
		char str[10];
		int pos = 0;
		
		while (tmp && tmp->id > 0) { 
			Animation =  tmp->Animation;

			u8g.drawXBMP(pos, 0, Animation->width, Animation->height, animate(Animation));
			pos = pos + 17;

			tmp = tmp->Next;
		} 

		u8g.drawXBMP( mini_light1_width + 10 + mini_ultrasonic1_width + 10 + mini_heater1_width  + 15 , 0, mini_humidity_width, mini_humidity_height, mini_humidity);
	  	u8g.drawStr(75, 6, strcat(this->intToChar(HBox->humidity,  str),"%"));
		
		u8g.drawXBMP( mini_light1_width + 10 + mini_ultrasonic1_width + 10 + mini_heater1_width  + 15 + mini_humidity_width + 25, 0, mini_temp_width, mini_temp_height, mini_temp);
		u8g.setPrintPos(103, 6);
		u8g.print(this->floatToChar(HBox->temperature,  str));
		u8g.write(0xB0);
		u8g.print("c ");
		u8g.drawLine(0, 11, 130, 11);

		for (int i = 0; i != (int) PMax; i++) {
			u8g.setPrintPos(0, 20+(i*9));
			u8g.print("[");
			u8g.print(screen::intToChar(i, str));
			if(!HBox->pot[i].isConnected) {
				u8g.print("] ");
				u8g.print(screen::intToChar(HBox->pot[i].moisture, str));
				u8g.print("%");
				u8g.print(" (");
				u8g.print(screen::intToChar(HBox->pot[i].moistureValue, str));
				u8g.print(") ");
				if(HBox->pot[i].stabilized)  u8g.print(" | stable ");
				else u8g.print(" | unstable ");
				u8g.print("| Cycle : ");
				u8g.println(screen::intToChar(HBox->pot[i].hydrateCycle, str));
		    } else  u8g.println("] Disconnected");

		}
  	} while( u8g.nextPage());
}*/



void screen::write(char* str ){
	for (int i = 0; (sizeof(hBuffer) / sizeof(hBuffer[0])); i++){
		if (!hBuffer[i] || hBuffer[i] == "" || hBuffer[i] == str){
			hBuffer[i] = str;
			break;
		}
	}
}

void screen::menu(){
		#if UU8G 
			u8g.firstPage(); 
			do {
				this->drawHeader();
				this->drawMenu();
		  } while( u8g.nextPage());
	 #endif

	 #if UU8G2
	  u8g.clearBuffer();
	  this->drawHeader();
	  this->drawMenu();
	  u8g.sendBuffer();	
	 #endif
}

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
/*	if(LightMeter && LightMeter->getBool("lighting")) headerAdd(this->Header, 1, screen::Animations[0]);
	else headerRemove(this->Header,1);*/
	if(PhotoResistor && PhotoResistor->getInt("lux") > 0) headerAdd(this->Header, 1, screen::Animations[0]);
	else headerRemove(this->Header,1);
	
	if(Heater && Heater->getBool("heating")) headerAdd(this->Header, 2, screen::Animations[2]);
	else headerRemove(this->Header, 2);
	
	if(Ultrasonic && Ultrasonic->getBool("enabled")) headerAdd(this->Header, 3, screen::Animations[1]);
	else headerRemove(this->Header, 3);

	tmp = this->Header;
	u8g.setFont(u8g_font_u8glib_4);
	char str[10];
	int pos = 0;
	
	while (tmp && tmp->id > 0) { 
		Animation =  tmp->Animation;

		u8g.drawXBMP(pos, 0, Animation->width, Animation->height, animate(Animation));
		pos = pos + 17;

		tmp = tmp->Next;
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


/*struct mmenu {
        String name;
        void* prev;
    };*/
mmenu** screen::loadMenu(int index) {
    if (this->menuDraw) return nullptr;

    mmenu** MReturn = new mmenu*[3];
    for (int i = 0; i != 3; i++) {
        MReturn[i] = new mmenu;
    }

    MReturn[0]->name = "Home";
    MReturn[1]->name = "Modules";
    MReturn[2]->name = "Eeprom";
    
    return MReturn;
}

void screen::drawMenu() {
		modules* Rotary = modules::Manager->findObj(ROTARY_ID);
		static int lastpos = Rotary->getInt("pos");
		static unsigned long int timee = millis();
		static unsigned int offsetOver = 0;
		static int selected = 0;

		int r = Rotary->getInt("pos");
		if(!this->menuDraw || r != lastpos) timee = millis();

		mmenu** Menu = screen::loadMenu(selected);
        if (!Menu) return;

		int maxScreenLine = 2;
		int maxLine = 3;

		if (r > lastpos) {

			if((selected + offsetOver) == (maxLine -1)){
				selected = 0;
				offsetOver = 0;

			} else {
				if(selected >= maxScreenLine && (offsetOver + selected ) < (maxLine-1))
					offsetOver++;
				else if (selected < maxScreenLine )
					selected++;
			}


			/*lastpos = r;*/
		} else if (r < lastpos) {
			if((selected + offsetOver) == 0){
				selected = maxScreenLine;
				offsetOver = (maxLine -1) - maxScreenLine;

			} else {
				if (selected > 0 && offsetOver > 0 ) 
					selected--;
				else if (selected == 0 && offsetOver > 0) 
					offsetOver--;
				else if (selected > 0 && offsetOver == 0) 
					selected--;
			}

			/*lastpos = r;*/
		}

        lastpos = r;

		u8g.setFont(u8g_font_u8glib_4);
	
		for (int i = offsetOver; i < maxLine; i++){
			int offsetSelected = (i - offsetOver);
			if(selected == offsetSelected) {
				u8g.setColorIndex(1);
				u8g.drawBox(0, (15 * (selected+1)), 128, 10);
			}

			u8g.setColorIndex((selected == offsetSelected ? 0 : 1));
            u8g.drawStr(0, (15 * (offsetSelected+1)) + 7, Menu[i]->name.c_str());
		}


		if(this->menuDraw) {
			 if (Rotary && !Rotary->getBool("bt") && (modules::getBool("relacher") == true ) && (selected - offsetOver) == 0) {
			 		this->menuDraw = false;
			 		modules::setBool("relacher", false);
			 		for(int i = 0; i!= 3; i++)
			 			delete Menu[i];

			 		delete[] Menu;
                    return;
			 }

			 if((millis()-timee) > 10000){
			 	this->menuDraw = false;
			 	for(int i = 0; i!= 3; i++)
			 		delete Menu[i];

			 	delete[] Menu;
			 }
		} else if(modules::getBool("relacher") == true){
			this->menuDraw = true;
			modules::setBool("relacher", false);
            /*for(int i = 0; i!= 3; i++)
                delete Menu[i];
            delete[] Menu;*/
		} 

}

void screen::update(){
	modules* Rotary = modules::Manager->findObj(ROTARY_ID);
	bool r = Rotary->getBool("bt");

   if(r) modules::setBool("relacher", true);


	 if (((Rotary && !r) && (modules::getBool("relacher") == true )) || this->menuDraw)  {
	 	this->menu(); 
	 } else {
		 #if UU8G 
			u8g.firstPage(); 
			do {
				this->drawHeader();
				this->drawHome();
		  } while( u8g.nextPage());
		 #endif


		 #if UU8G2
		  u8g.clearBuffer();
		  this->drawHeader();
		  this->drawHome();
		  u8g.sendBuffer();	
		 #endif
	 }

/*	if(!r) modules::setBool("relacher", false);*/
}


void screen::drawHome(){
	for (int i = 0; hBuffer[i]; i++ ){
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