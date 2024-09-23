#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;
//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
bool rel(TElem e1, TElem e2) {
	return e1 <= e2;
}
//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
bool cond(TElem e){
    if (e <=10)
        return true;
    return false;
}
//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
Nod::Nod(Pereche e, PNod urm) {
    /// constructor
    this->e = e;
    this->urm = urm;
}
//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
Pereche Nod::element() {
    return e;
}
//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
Colectie::Colectie() {
    this->prim = nullptr;
    this->size = 0;
    this->total = 0;
}
//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
PNod Nod::urmator() {
    return urm;
}
//CF:Theta(1)-daca exista si e pe prima pozitie
//CD:Theta(n)
//CT:Theta(n)
void Colectie::adauga(TElem e) {
    // Verificam dacă elementul exista deja și actualizam frecventa
    PNod p = this->prim;
    while (p != nullptr) {
        if (p->element().valoare == e) {
            p->e.frecventa++;
            this->total++;
            return;
        }
        p = p->urmator();
    }

    // Daca nu exista cream un nou nod cu elementul dat
    Pereche x;
    x.valoare = e;
    x.frecventa = 1;
    PNod nouNod = new Nod(x, nullptr);

    // Daca lista este goala sau elementul trebuie adaugat la inceputul listei
    if (this->prim == nullptr || rel(e, this->prim->element().valoare)) {
        nouNod->urm = this->prim;
        this->prim = nouNod;
        this->size++;
        this->total++;
        return;
    }

    // Parcurgem lista pana la nodul dupa care trebuie adaugat noul nod
    p = this->prim;
    while (p->urmator() != nullptr && !rel(e, p->urmator()->element().valoare)) {
        p = p->urmator();
    }

    // Adaugam noul nod dupa nodul p
    nouNod->urm = p->urm;
    p->urm = nouNod;
    this->size++;
    this->total++;
}
//CF:Theta(1) -daca nu se afla in lista sau este primul
//CD:Theta(n)
//CT:O(n)
bool Colectie::sterge(TElem e) {
    if (!cauta(e))
        return false;

    // Primul element este cel care trebuie sters
    if (prim->element().valoare == e) {
        if (prim->element().frecventa > 1) {
            prim->e.frecventa--;
            total--;
            return true;
        }
        else {
            PNod sters = this->prim;
            prim = prim->urmator();
            delete sters;
            size--;
            total--;
            return true;
        }
    }

    PNod p = this->prim;
    while (p->urmator() != nullptr && p->urmator()->element().valoare != e) {
        p = p->urmator();
    }

    PNod urm = p->urmator();
    if (urm->element().frecventa > 1) {
        urm->e.frecventa--;
        total--;
        return true;
    }
    else {
        p->urm = urm->urmator();
        delete urm;
        size--;
        total--;
        return true;
    }

    return false;
}
//CF:Theta(1)-primul element
//CD:Theta(n)-nu se gaseste sau ultimul element
//CT:O(n)
bool Colectie::cauta(TElem elem) const {
    if (size == 0)
        return false;
    PNod p = this->prim;
    while (p != nullptr)
    {
        if (p->element().valoare == elem)
            return true;
        p = p->urmator();
    }
	return false;
}
//CF:Theta(1)-este aflat pe prima pozitie
//CD:Theta(n)
//CT:O(n)
int Colectie::nrAparitii(TElem elem) const {
    PNod p = prim;
    while (p != nullptr)
    {
        if (p->element().valoare == elem)
            return p->element().frecventa;
        p = p->urmator();
    }
	return 0;
}

//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
int Colectie::dim() const {
    return total;
}
//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
bool Colectie::vida() const {
    if (size == 0)
        return true;
    else
        return false;
}
//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}

//CF:Theta(n)
//CD:Theta(n)
//CT:Theta(n)
Colectie::~Colectie() {
    
    while (this->prim!= nullptr)
    {
        PNod p = this->prim;
        this->prim = this->prim->urm;
        delete p;
    }
}

//CF:Theta(n)
//CD:Theta(n)
//CT:Theta(n)
void Colectie::filtreaza() {
    //verificam daca primul element trb sters
    while (prim != nullptr && !cond(prim->element().valoare)) {
        total -= prim->element().frecventa;
        PNod sters = prim;
        prim = prim->urmator();
        delete sters;
        size--;
    }

    // parcurgem in continuare lista si stergerem elem care nu respecta cond.
    PNod p = prim;
    while (p != nullptr && p->urmator() != nullptr) {
        if (!cond(p->urmator()->element().valoare)) {
            total -= p->urmator()->element().frecventa;
            PNod sters = p->urmator();
            p->urm = sters->urmator();
            delete sters;
            size--;
        }
        else {
            //continuam parcurgerea
            p = p->urmator();
        }
    }
}
