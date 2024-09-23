#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>
#include <exception>

using namespace std;

Multime::Multime() {
    this->vect = new TElem [100]; ///vector dinamic cu 100 de elem
    this->capacitate = 10;
    this->nr_elemente = 0;
    //for(int i=1;i<=this->capacitate; i++) this->vect[i]=0;

}


bool Multime::adauga(TElem elem) {
    //elem se adauga la final
    this->resize();
    if(!cauta(elem)) {
        this->nr_elemente++;
        this->vect[this->nr_elemente]=elem;
        return true;
    }
    return false;
}


bool Multime::sterge(TElem elem) {

    for(int i=1;i<=this->nr_elemente;i++)
        if(this->vect[i]==elem) {
            for(int j=i+1;j<=this->nr_elemente;j++)
                this->vect[j-1]=this->vect[j];
            this->nr_elemente--;
            return true;
        }
    return false;
}


bool Multime::cauta(TElem elem) const {
    for(int i=1;i<=this->nr_elemente;i++)
        if(this->vect[i]==elem)
            return true;
    return false;
}


int Multime::dim() const {
    if(this->nr_elemente > 0) return this->nr_elemente;
    return 0;
}

bool Multime::vida() const {
    if(this->nr_elemente > 0) return false;
    return true;
}


Multime::~Multime() {
    delete[] this->vect;
}



IteratorMultime Multime::iterator() const {
    return IteratorMultime(*this);
}

void Multime::resize(){
    if(this->nr_elemente == this->capacitate) {
        TElem *vector_nou = new TElem[2 * this->capacitate];
        for (int i = 1; i <= this->nr_elemente; i++) {
            vector_nou[i] = this->vect[i];
        }
        delete[] this->vect;
        this->vect = vector_nou;
        this->capacitate *= 2;
    }
}