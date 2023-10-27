#ifndef TRADUCTIONCPP_SET_H
#define TRADUCTIONCPP_SET_H

#include "Entry.h"

class Set {
public:
    unsigned int mask;
    unsigned int size;
    Entry* data;

    Set();
    ~Set();

    bool add(unsigned int key, unsigned int depth);

private:
    static unsigned int hash(unsigned int key);
};

#endif //TRADUCTIONCPP_SET_H
