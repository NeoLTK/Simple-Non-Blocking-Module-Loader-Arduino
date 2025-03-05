#ifndef Service_h
#define Service_h

struct sList {
	void *prev;
	void *object;
	void *next;
};

class service {
	public:
		service();
		~service();

		void add(void*);
		void rm(void*);
		void view(void*);

	private:
		sList *list;
};