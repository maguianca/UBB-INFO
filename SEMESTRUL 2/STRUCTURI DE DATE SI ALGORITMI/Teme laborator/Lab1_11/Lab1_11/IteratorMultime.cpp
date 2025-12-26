#include "IteratorMultime.h"
#include "Multime.h"


IteratorMultime::IteratorMultime(const Multime& m) : multime(m){
    this->prim(); ///referinta catre primul element din colectie
}


void IteratorMultime::prim() {
    //if(multime.nr_elemente>0)

    index = 1;
}


void IteratorMultime::urmator() {
        index++;
}

void IteratorMultime::anterior() {
    index--;
}

TElem IteratorMultime::element() const {
    return multime.vect[index];
}

bool IteratorMultime::valid() const {
    //index merge pana la capacitate-1

    if(multime.vida())
        return false;
    if(index <= multime.nr_elemente&&index>=1)
        return true;

    return false;
}
