#pragma once
#pragma once
#pragma once
#include "domeniu.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include"observer.h"
#include"repo.h"
using std::vector;

class CosOferte:public Observable {
private:
    Repo& repo;
    vector<Turism> cosOferte;
public:
    /*
     * Constructorul cosului.
     */
    CosOferte(Repo& repo) :repo{ repo } {};

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
    * Adauga un numar de oferte in cos.
    * param oferte: ofertele random ce trebuie adaugate in cos.
    * param numar: numarul de oferte ce trebuie adaugate.
    */
    void umple(int cate) {
        int seed = std::chrono::system_clock::now().time_since_epoch().count();
        vector<Turism> all = repo.get_all();
        std::shuffle(all.begin(), all.end(), std::default_random_engine(seed)); //amesteca vectorul v
        while (cosOferte.size() < cate && all.size() > 0) {
            cosOferte.push_back(all.back());
            all.pop_back();
        }
        //notificam can dse schimba ceva in cos
        notify();
    }

    /*
     * Sterge toate ofertele din cos.
     */
    void stergeCos();

    void exportaCos(string numeFisier);
};