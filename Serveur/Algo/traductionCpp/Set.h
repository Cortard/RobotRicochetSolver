#ifndef TRADUCTIONCPP_SET_H
#define TRADUCTIONCPP_SET_H

#include "Entry.h"

class Set {
public:
    unsigned int mask;
    unsigned int size;
    Entry *data;
};

#endif //TRADUCTIONCPP_SET_H
