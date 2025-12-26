#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;

bool rel(TElem e1, TElem e2) {
    return e1 <= e2;
}
Nod::Nod(Pereche e, PNod urm) {
    /// constructor
    this->e = e;
    this->urm = urm;
}
Pereche Nod::element() {
    return e;
}
Colectie::Colectie() {
    this->prim = nullptr;
    this->size = 0;
    this->total = 0;
}
PNod Nod::urmator() {
    return urm;
}
void Colectie::adauga(TElem e) {
    // Creăm o nouă pereche cu elementul și frecvența 1
    Pereche x;
    x.valoare = e;
    x.frecventa = 1;

    // Creăm un nou nod cu perechea creată și următorul nod setat pe nullptr
    PNod newNod = new Nod(x, nullptr);

    // Verificăm dacă lista este goală
    if (this->prim == nullptr) {
        this->prim = newNod; // Dacă este, nodul nou devine primul nod din listă
        this->size = 1; // Actualizăm dimensiunea listei
        this->total = 1;
        return; // Ieșim din funcție
    }

    // Parcurgem lista pentru a verifica dacă elementul există deja
    PNod p = this->prim;
    while (p->urmator() != nullptr) {
        if (p->element().valoare == e) {
            p->e.frecventa++; // Dacă există, incrementăm frecvența și ieșim din funcție
            this->total++;
            return;
        }
        p = p->urmator(); // Trecem la următorul nod
    }

    // Dacă nu am ieșit din funcție până acum, înseamnă că elementul nu există în listă
    // Deci adăugăm un nou nod la sfârșitul listei cu frecvența 1
    p->urm = newNod;
    this->size++; // Incrementăm dimensiunea listei
    this->total++;
}

bool Colectie::sterge(TElem e) {
    if (!cauta(e))
        return false;

    // If the first element is the one to be deleted
    if (prim->element().valoare == e) {
        if (prim->element().frecventa > 1) {
            prim->e.frecventa--;
            total--;
            return true;
        }
        else {
            Nod* sters = prim;
            prim = prim->urmator();
            delete sters;
            size--;
            total--;
            return true;
        }
    }

    Nod* p = prim;
    while (p->urmator() != nullptr && p->urmator()->element().valoare != e) {
        p = p->urmator();
    }

    // Now p points to the node before the one to be deleted
    PNod urm = p->urmator();
    if (urm->element().frecventa > 1) {
        urm->e.frecventa--;
        total--;
        return true;
    }
    else {
        p->urm = urm->urm;
        delete urm;
        size--;
        total--;
        return true;
    }

    return false; // This line should not be reached
}

/*
bool Colectie::sterge(TElem e) {
    if (!cauta(e))
        return false;

    // If the first element is the one to be deleted
    if (prim->e.valoare == e) {
        if (prim->e.frecventa > 1) {
            prim->e.frecventa--;
            return true;
        }
        else {
            Nod* sters = prim;
            prim = prim->urm;
            delete sters;
            size--;
            return true;
        }
    }

    Nod* p = prim;
    while (p->urmator() != nullptr && p->urmator()->element().valoare != e) {
        p = p->urmator();
    }

    // Now p points to the node before the one to be deleted
    if (p->urmator()->element().frecventa > 1) {
        p->urmator()->element().frecventa--;
        return true;
    }
    else {
        Nod* sters = p->urmator();
        p->urm = sters->urm;
        delete sters;
        size--;
        return true;
    }

    return false; // This line should not be reached
}

bool Colectie::sterge(TElem e) {
    if (!cauta(e))
        return false;
    Nod* p = this->prim;
    if (p->element().valoare == e)
    {
        if (p->element().frecventa > 1)
        {
            p->element().frecventa--;
            return true;
        }
        else {
            prim = prim->urm;
            size--;
            delete p;
            return true;
        }
    }
    while (p->urmator()->element().valoare != e)
    {
        p = p->urmator();
    }
    //ne-am oprit pe elementul de dinainte
    if (p->urmator()->element().frecventa > 1)
    {
        p = p->urmator();
        p->element().frecventa--;
        return true;
    }
    else
    {
        Nod* sters = p->urm;
        p->urm= sters->urm;
        delete sters;
        size--;
    }
    return false;
}*/


bool Colectie::cauta(TElem elem) const {
    if (size == 0)
        return false;
    Nod* p = prim;
    while (p != nullptr)
    {
        if (p->element().valoare == elem)
            return true;
        p = p->urmator();
    }
    return false;
}


int Colectie::nrAparitii(TElem elem) const {
    Nod* p = prim;
    while (p != nullptr)
    {
        if (p->element().valoare == elem)
            return p->element().frecventa;
        p = p->urmator();
    }
    return 0;
}



int Colectie::dim() const {
    return total;
}


bool Colectie::vida() const {
    if (size == 0)
        return true;
    else
        return false;
}


IteratorColectie Colectie::iterator() const {
    return  IteratorColectie(*this);
}


Colectie::~Colectie() {

    while (this->prim != nullptr)
    {
        PNod p = this->prim;
        this->prim = this->prim->urm;
        delete p;
    }
}
