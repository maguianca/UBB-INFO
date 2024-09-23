#pragma once
#pragma once
#include "domeniu.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using std::vector;

class CosOferte {
private:
    vector<Turism> cosOferte;
public:
    /*
     * Constructorul cosului.
     */
    CosOferte() = default;

    /*
     * Adauga o oferta in cos.
     * param o: oferta ce trebuie adaugata in cos.
     */
    void adaugaOfertaCos(const Turism& o);

    /*
     * Adauga un numar de oferte in cos.
     * param oferte: ofertele random ce trebuie adaugate in cos.
     * param numar: numarul de oferte ce trebuie adaugate.
     */
    void adaugaOfertaRandomCos(vector<Turism> oferte, int numar);

    /*
     * Returneaza un vector cu toate ofertele din cos.
     */
    const vector<Turism>& getAllCos()const;

    /*
     * Sterge toate ofertele din cos.
     */
    void stergeCos();
};