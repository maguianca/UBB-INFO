#pragma once
#include"IteratorMatrice.h"
typedef int TElem;


#define NULL_TELEMENT 0

//referire a clasei Nod

class Nod;

class IteratorMatrice;

//se defineste tipul PNod ca fiind adresa unui Nod

typedef Nod *PNod;

class Nod

{
    friend class IteratorMatrice;

public:

    friend class Matrice;

    //constructor

    Nod(TElem e, PNod st, PNod dr,int i,int j);

    TElem element();

    PNod stanga();

    PNod dreapta();


private:

    TElem e;
    PNod st, dr;
    //in functie de i-j se face adaugarea in arbore
    //int ij;
    int i,j;
};

class Matrice {
    friend class IteratorMatrice;
private:
    //rad este adresa radacinii
    PNod rad;
    int nLinii,nColoane;


    //adaugarea recursiva a elementului de pe pozitia i j cu valoarea e in matrice, incepanf de la nodul p, pt a indica rad arborelui
    //in care se face adaugarea
    PNod adauga_rec(PNod p, TElem e,int i,int j);
    //adaugarea iterativa a elementului de pe pozitia i j cu valoarea e in matrice, incepanf de la nodul p, pt a indica rad arborelui
    //in care se face adaugarea
    PNod adauga_it(PNod p, TElem e,int i,int j);
    //cautare
    //cauta in arbore nodul de pe pozitia i j in matrice, returneaza pointer catre nodul respectiv, daca nu exista, se returneaza pointer null
    //p este nodul de inceput, de aici se incepe cautarea, pt a putea indica rad arborelui in care se face cautarea
    PNod search(PNod p,int i,int j) const;
    //distrugerea recursiva a nodurilor din arborele/subarborlee care incepe la rad pnod
    void distrug_rec(PNod);
    //distrugerea recursiva a nodurilor din arborele/subarborlee care incepe la rad pnod
    void distrug_it(PNod);

public:

    //constructor
    //se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
    Matrice(int nrLinii, int nrColoane);


    //destructor
    ~Matrice(){//se elibereaza memoria alocata nodurilor listei
        distrug_rec(rad);};

    //returnare element de pe o linie si o coloana
    //se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
    //indicii se considera incepand de la 0
    TElem element(int i, int j) const;


    // returnare numar linii
    int nrLinii() const;

    // returnare numar coloane
    int nrColoane() const;


    // modificare element de pe o linie si o coloana si returnarea vechii valori
    // se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
    TElem modifica(int i, int j, TElem);

    // se returneaza iterator pe MD
    IteratorMatrice iterator(int l) const;

};







