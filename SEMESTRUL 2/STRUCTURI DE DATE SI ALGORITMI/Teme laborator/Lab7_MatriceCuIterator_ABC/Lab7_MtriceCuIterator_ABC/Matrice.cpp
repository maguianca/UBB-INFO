#include "Matrice.h"
#include<iostream>
#include <exception>
#include<stack>

using namespace std;

//Theta(1)
Nod::Nod(TElem e, PNod st, PNod dr,int i,int j) {
    this->e = e;
    this->st = st;
    this->dr = dr;
   // this->ij=i-j;
    this->i=i;
    this->j=j;
}

//Theta(1)
TElem Nod::element() {
    return e;
}

//Theta(1)
PNod Nod::stanga() {
    return st;
}

//Theta(1)
PNod Nod::dreapta() {
    return dr;
}

//Theta(1)
Matrice::Matrice(int m, int n) {
    /* Matrice m(10,10);
    assert(m.nrLinii() == 10);
    assert(m.nrColoane() == 10);
    for(int i=0; i<m.nrLinii(); i++)
        for(int j=0; j<m.nrColoane(); j++)
            assert(m.element(i,j) == NULL_TELEMENT); */
    nLinii=m;
    nColoane=n;
    rad= nullptr;
}

//OC: O(h), h=inaltimea ABC
PNod Matrice::adauga_rec(PNod p, TElem e,int i,int j) {
    if (p == nullptr) {
        p = new Nod(e, nullptr, nullptr,i,j);
    }
    else {
        if (i < p->i) //se adauga in stanga
            p->st = adauga_rec(p->st, e,i,j);
        else if(i==p->i&&j<p->j){
            p->st = adauga_rec(p->st, e,i,j);
        }else//se adauga in dreapta
            p->dr = adauga_rec(p->dr, e,i,j);
    }
    return p;
}

PNod Matrice::adauga_it(PNod p, TElem e,int i,int j) {
    PNod newNode = new Nod(e, nullptr, nullptr, i, j);

    if (p == nullptr) {
        return newNode;
    }

    PNod current = p;
    PNod parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (i < current->i || (i == current->i && j < current->j)) {
            // go to the left
            current = current->st;
        } else {
            // go to the right
            current = current->dr;
        }
    }

    if (i < parent->i || (i == parent->i && j < parent->j)) {
        parent->st = newNode;
    } else {
        parent->dr = newNode;
    }

    return p;
}

//OC: O(h), h=inaltimea ABC
void Matrice::distrug_rec(PNod p) {
    if (p != nullptr) {
        distrug_rec(p->stanga());
        distrug_rec(p->dreapta());
        delete p;
    }
}

//OC: O(h), h=inaltimea ABC
void Matrice::distrug_it(PNod p) {
    if (p == nullptr) {
        return;
    }

    std::stack<PNod> nodeStack;
    nodeStack.push(p);

    while (!nodeStack.empty()) {
        PNod current = nodeStack.top();
        nodeStack.pop();

        if (current->dreapta() != nullptr) {
            nodeStack.push(current->dreapta());
        }

        if (current->stanga() != nullptr) {
            nodeStack.push(current->stanga());
        }

        delete current;
    }
}

//Theta(1)
int Matrice::nrLinii() const{
    return nLinii;
}

//Theta(1)
int Matrice::nrColoane() const{
    return nColoane;
}

//OC: O(h), h=inaltimea ABC
PNod Matrice::search(PNod p,int i,int j) const{
    while (p != nullptr &&!(p->i==i&&p->j==j)) {
        if (i < p->i) {
            p = p->st;
        } else if(i==p->i&&j<p->j){
            p = p->st;
        }else p=p->dr;
    }
    return p;
}

//OC: O(h), h=inaltimea ABC, same as search complexity
TElem Matrice::element(int i, int j) const{
    if(this->search(rad,i,j)== nullptr)
        return NULL_TELEMENT;
    return this->search(rad,i,j)->e;
}


//OC: O(h), h=inaltimea ABC, apeleaza adaugarea recusriva si functia de search individual, deci aceeasi complexitate ca si cea predom. =in a.c. => O(h)
TElem Matrice::modifica(int i, int j, TElem e) {
    TElem e_vechi;
    if(rad== nullptr){
        rad=new Nod(e, nullptr, nullptr,i,j);
        return NULL_TELEMENT;
    }else{
        if(search(rad,i,j)== nullptr)
            e_vechi=NULL_TELEMENT;
        else
            e_vechi= element(i,j);

        if(e!=NULL_TELEMENT)
            adauga_rec(rad,e,i,j);
        if(e==NULL_TELEMENT&&e_vechi!=NULL_TELEMENT)
            distrug_rec(search(rad,i,j));
        return e_vechi;
    }
}

IteratorMatrice Matrice::iterator(int l) const {
    //Theta(1)
    return IteratorMatrice(*this,l);
}


