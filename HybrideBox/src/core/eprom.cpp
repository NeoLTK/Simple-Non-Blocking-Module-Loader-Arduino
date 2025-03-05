#include "eprom.h"
#if EPROMM

eprom* eprom::Eprom = nullptr;

eprom::eprom() {
    this->bites = 1024;
    this->eeVar = new int[this->bites];
    this->curBite = 0;
    this->curIndex = 1;
}

eprom::eprom(int bites) {
    this->bites = bites;
    this->eeVar = new int[this->bites];
    this->curBite = 0;
    this->curIndex = 1;
}

eprom::~eprom() {
    delete[] this->eeVar;
}

eprom* eprom::load() {
    if (eprom::Eprom != nullptr)
        return eprom::Eprom;
    else {
        eprom::Eprom = new eprom();
        return eprom::Eprom;
    }
}

int eprom::writeLongInt(int val) {
    int tmp = this->curBite;
    float sVal = (val / 255.0);

    if ((tmp + sizeof(sVal)) > this->bites) return 0;

    eeprom_write_float(this->curBite, sVal);

    this->eeVar[this->curIndex] = this->curBite;
    this->curIndex = this->curIndex + 1;
    this->curBite = (this->curBite + sizeof(sVal));

    return tmp;
}

int eprom::writeStruct(void* structure, size_t size) {
    int tmp = this->curBite;

    EEPROM.put(this->curBite, structure);
    this->eeVar[this->curIndex] = this->curBite;
    this->curIndex = this->curIndex + 1;
    this->curBite = (this->curBite + size);

    return this->curIndex;
}

int eprom::updateLongInt(int index, int val) {
    float sVal = (val / 255.0);

    eeprom_update_float(this->eeVar[index], sVal);
    return 1;
}

int eprom::available() {
    return (this->bites - this->curBite);
}

int eprom::readLongInt(int index) {
    float tmp = eeprom_read_float(this->eeVar[index]);
    return (int)(tmp * 255);
}

void eprom::readStruct(int index, void* structure, size_t size) {
    EEPROM.get(this->eeVar[index], structure);
}

#endif
