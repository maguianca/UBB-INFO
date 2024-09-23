#include "CosOferte.h"
#include <algorithm>
#include <random>

using std::shuffle;

void CosOferte::adaugaOfertaCos(const Turism& o) {
    this->cosOferte.push_back(o);
}

void CosOferte::adaugaOfertaRandomCos(vector<Turism> oferte, int numar) {
    shuffle(oferte.begin(), oferte.end(), std::default_random_engine(std::random_device{}())); //amesteca vectorul v
    while (cosOferte.size() < numar && !oferte.empty()) {
        cosOferte.push_back(oferte.back());
        oferte.pop_back();
    }
}

const vector<Turism>& CosOferte::getAllCos() const{
    return this->cosOferte;
}

void CosOferte::stergeCos() {
    this->cosOferte.clear();
}