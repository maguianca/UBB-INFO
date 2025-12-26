//
// Created by Ilinca on 30-Mar-22.
//

#include "Medicament.h"
#include "assert.h"

string Medicament::get_denumire() const {
    return this->denumire;
}

string Medicament::get_producator() const {
    return this->producator;
}

string Medicament::get_substanta_activa() const {
    return this->substanta_activa;
}

double Medicament::get_pret() const {
    return this->pret;
}

void Medicament::set_denumire(string denumire_noua) {
    this->denumire = denumire_noua;
}

void Medicament::set_producator(string producator_nou) {
    this->producator = producator_nou;
}

void Medicament::set_substanta_activa(string substanta_activa_noua) {
    this->substanta_activa = substanta_activa_noua;
}

void Medicament::set_pret(double pret_nou) {
    this->pret = pret_nou;
}

bool cmp_denumire( Medicament& m1,  Medicament& m2) {
    return m1.get_denumire() < m2.get_denumire();
}

bool cmp_producator(Medicament& m1, Medicament& m2) {
    return m1.get_producator() < m2.get_producator();
}

bool cmp_substspret(Medicament& m1, Medicament& m2) {
    if (m1.get_substanta_activa() == m2.get_substanta_activa())
        return m1.get_pret() < m2.get_pret();
    else
        return m1.get_substanta_activa() < m2.get_substanta_activa();
}


