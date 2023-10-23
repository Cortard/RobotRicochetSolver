#ifndef TRADUCTIONCPP_SET_H
#define TRADUCTIONCPP_SET_H

#include "Entry.h"

class Set {
public:
    unsigned int mask;
    unsigned int size;
    Entry* data;

    Set(){
        mask= 0xfff;//4095
        size= 0;
        data = new Entry[mask+1];//4096
    }

    ~Set(){
        delete[] data;
    }
};

#endif //TRADUCTIONCPP_SET_H
