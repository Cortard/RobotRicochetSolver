#include "Set.h"

Set::Set() {
    mask= 0xfff;//4095 0b1111 1111 1111
    size= 0;
    data = new Entry[mask+1];//4096
}

Set::~Set() {
    delete[] data;
}

bool Set::add(unsigned int key, unsigned int depth) {
    unsigned int index = hash(key) & mask; //index de la clé
    Entry *entry = data + index; //pointeur sur l'addresse de la clé
    while (entry->key && entry->key != key){ //tant que la clé n'est pas vide et qu'elle est différente de la clé
        index = (index + 1) & mask; //on incrémente l'index
        entry = data + index; //on met à jour l'addresse
    }


    return false;
}

unsigned int Set::hash(unsigned int key)  {
    key = ~key + (key << 15);
    key = key ^ (key >> 12);
    key = key + (key << 2);
    key = key ^ (key >> 4);
    key = key * 2057;
    key = key ^ (key >> 16);
    return key;
}
