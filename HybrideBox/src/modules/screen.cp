#include "screen.h"
#include <Arduino.h>


// declaration U8 crash 


#if defined(SCREEN_SH1106)
	U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE); 
#elif defined(SCREEN_SSD1306)
	U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);  
#endif


screen::screen(HybrideBox *HBox) {

	//u8g.setRot180();
	u8g.firstPage(); 

	do {
     	u8g.drawXBMP(30, 0, 67, 64, boot);
  	} while( u8g.nextPage() );

	this->HBox = HBox; 

	this->Animations[0] = new animation;
	this->Animations[0]->frames = 2;
	this->Animations[0]->frame = new void*[this->Animations[0]->frames];
	this->Animations[0]->frame[0] = &mini_light1;
	this->Animations[0]->frame[1] = &mini_light2;
	this->Animations[0]->height = mini_light1_height;
	this->Animations[0]->width = mini_light1_width;
	this->Animations[0]->interval = 500;

	this->Animations[1] = new animation; 
	this->Animations[1]->frames = 2;
	this->Animations[1]->frame =   new void*[this->Animations[1]->frames];
	this->Animations[1]->frame[0] = &mini_ultrasonic1;
	this->Animations[1]->frame[1] = &mini_ultrasonic2;
	this->Animations[1]->height = mini_ultrasonic1_height;
	this->Animations[1]->width = mini_ultrasonic1_width;
	this->Animations[1]->interval = 300;

	this->Animations[2] = new animation;
	this->Animations[2]->frames = 2;
	this->Animations[2]->frame =   new void*[this->Animations[2]->frames];
	this->Animations[2]->frame[0] = &mini_heater1;
	this->Animations[2]->frame[1] = &mini_heater2;
	this->Animations[2]->height = mini_heater1_height;
	this->Animations[2]->width = mini_heater1_width;
	this->Animations[2]->interval = 250;

	this->Header = malloc(sizeof(header));
	this->Header->Next = NULL;
	this->Header->Prev = NULL;
	this->Header->id = NULL;

}

bool headerSearch(header *Header, int id){
	header *tmp = malloc(sizeof(header));
	tmp = Header;

	while(tmp) {
		if(tmp->id == id) {
			return true;
		} 
		
		tmp = tmp->Next;
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
		while(cur->Next) cur = cur->Next;

		header *newH = malloc(sizeof(header));
		newH->Animation = Animation;
		newH->Prev = cur;
		newH->id = id;
		newH->Next = NULL;

		cur->Next = newH;
	} 

}


void headerRemove(header *Header, int id){
	header *tmp = malloc(sizeof(header));

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
				free(tmp);
			} else {
				free(Header);
				Header = tmp;
			}

			return;
		} 

	    Header = Header->Next;
	}

	free(tmp);
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

void screen::update(){
	Serial.println("screen on");
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
}

char* screen::floatToChar(float f, char str[]){
  sprintf(str, "%d.%01d", (int)f, (int)(f*100)%100);
  return str;
}

char* screen::intToChar(int i, char str[]){
  sprintf(str, "%d", i);
  return str;
}
