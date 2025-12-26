#pragma once

#include "Matrice.h"

#include <stack>

using namespace std;

class Matrice;

class Nod;
typedef Nod *PNod;

typedef int TElem;

class IteratorMatrice {
    friend class Matrice;
private:
    // constructorul primeste o referinta catre Container
    // iteratorul va referi primul element din container
    IteratorMatrice(const Matrice& m,int linia);

    // contine o referinta catre containerul pe care il itereaza
    const Matrice& m;
    int l;
    PNod rl;
    PNod curent;
    stack<PNod> st;
public:
    // reseteaza pozitia iteratorului la inceputul containerului
    void prim();

    // muta iteratorul in container
    // arunca exceptie daca iteratorul nu e valid
    void urmator();

    // verifica daca iteratorul e valid (indica un element al containerului)
    bool valid() const;

    // returneaza valoarea elementului din container referit de iterator
    // arunca exceptie daca iteratorul nu e valid
    TElem element();
};