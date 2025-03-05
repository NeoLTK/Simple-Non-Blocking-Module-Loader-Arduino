
#ifndef Screen_h
#define Screen_h
#include "../../../../configuration.h"

#if SCREEN 

	#include "../../../core/structure.h"
	#include "../../../core/fonts.h"
	#include "../../modules.h"

	struct animation  {
		const void **frame;
		int frames;
		int curFrame = 1;
		int interval = 250;
		int time = 0;
		int curTime = 0;
		int width;
		int height;
	};

	struct header {
		void *Prev;
		void *Animation;
		void *Next;
		
		int id;
	};

	struct Buffer {
		int line;
		char* str;
		Buffer* next;
	};

	class Items {
		public:
			String name;
			void* func;
			void* obj;


			Items(const String &str) : name(str), func(nullptr), obj(nullptr) {}
			Items(const String &str, void* callback) : name(str), func(callback), obj(nullptr) {}
			Items(const String &str, void* callback, void* obj) : name(str), func(callback), obj(obj) {}
			
	};

	class Menu {
		public:
			String name;
			Items** _Items;

			Menu(String str) : name(str){}
			Menu(String str, Items** it) : name(str), _Items(it){}
	};

	class screen : public modules {
		public:
			screen();
			~screen();
			
			void update();
			void drawNotes();
			void drawDialog();
			void drawMenu();
			void drawHeader();
			void write(char*);
			void draw();
			
			Menu** _Menu;
			Items* curMenu;

			int MIndex;
			int IIndex;
			int level = 0;

			void control(int&, int&, int&);

		private:
			char* floatToChar(float, char[]);
			char* intToChar(int, char[]);
			bool menuDraw;
			HybrideBox *HBox;
			animation *Animations[10] = {};
			header *Header;
			char** hBuffer;
			void loadMenu();
			void loadAnime();	

			//const void* animate(animation*);
	};

#endif
#endif
