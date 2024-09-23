#include "CosOferte.h"
#include <algorithm>
#include <random>
#include<fstream>
using std::shuffle;

void CosOferte::adaugaOfertaCos(const Turism& o) {
    auto it = find_if(cosOferte.begin(), cosOferte.end(), [&](const Turism& b) {
        return o.get_denumire() == b.get_denumire() && o.get_destinatie() == b.get_destinatie() && o.get_pret() == b.get_pret() && o.get_tip() == b.get_tip();
        });
    if (it == cosOferte.end()) {
        this->cosOferte.push_back(o);
        notify();
    }
    else
        throw RepoException("Oferta existenta");
}

void CosOferte::adaugaOfertaRandomCos(vector<Turism> oferte, int numar) {
    shuffle(oferte.begin(), oferte.end(), std::default_random_engine(std::random_device{}())); //amesteca vectorul v
    while (cosOferte.size() < numar && !oferte.empty()) {
        cosOferte.push_back(oferte.back());
        oferte.pop_back();
    }
    notify();
}

const vector<Turism>& CosOferte::getAllCos() const {
    return this->cosOferte;
}

void CosOferte::stergeCos() {
    this->cosOferte.clear();
    notify();
}

void CosOferte::exportaCos(string numeFisier)
{
    std::ofstream fout(numeFisier);
    for (auto& oferta : cosOferte)
        fout << oferta.get_denumire() << ":" << oferta.get_destinatie() << ":" << oferta.get_tip() << ":" << oferta.get_pret() << std::endl;
    fout.close();
}
