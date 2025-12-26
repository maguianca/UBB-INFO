//
// Created by Ilinca on 30-Mar-22.
//

#pragma once
#include "Service.h"
#include "Validators.h"
#include <assert.h>
#include <functional>
#include <algorithm>

void Medicamente_Service::add_medicament(string denumire, string producator, string substanta_activa, double pret) {
    Medicament med1{denumire, producator, substanta_activa, pret};
    val.valideaza(med1);
    repo.store(med1);
}

void Medicamente_Service::modifica_pret_service(string denumire, string producator, string substanta_activa,
                                                double pret_nou) {
    Medicament med1{denumire, producator, substanta_activa, pret_nou};
    val.valideaza(med1);
    repo.modificare_pret_repo(med1);
}

void Medicamente_Service::stergere_service(string denumire, string producator, string substanta_activa, double pret) {
    Medicament med1{denumire, producator, substanta_activa, pret};
    val.valideaza(med1);
    repo.stergere_repo(med1);
}

VectorDinamic<Medicament> Medicamente_Service::filtrare_substanta_activa(string substanta_activa) {
    VectorDinamic<Medicament> rezultat;
    for(const auto& med : repo.get_all_medicamente()) {
        if(med.get_substanta_activa() == substanta_activa){
            rezultat.add(med);
        }
    }
    return rezultat;
}

VectorDinamic<Medicament> Medicamente_Service::filtrare_pret(double pret) {
    VectorDinamic<Medicament> rezultat;
    for(const auto& med : repo.get_all_medicamente()) {
        if(med.get_pret() == pret){
            rezultat.add(med);
        }
    }
    return rezultat;
}

/*
vector<Medicament> Medicamente_Service::general_sort(bool (*mai_mic_f)(const Medicament &, const Medicament &)) {
    vector<Medicament> v{repo.get_all_medicamente()};
    for (size_t i=0;i<v.size();i++) {
        for (size_t j = i + 1; j < v.size(); j++) {
            if (!mai_mic_f(v[i], v[j])) {
                Medicament aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        }
    }
    return v;
}

vector<Medicament> Medicamente_Service::sort_by_denumire() {
    auto sorted_copy = repo.get_all_medicamente();
    sort(sorted_copy.begin(), sorted_copy.end(), cmp_denumire);
    return sorted_copy;
}

vector<Medicament> Medicamente_Service::sort_by_producator() {
    auto sorted_copy = repo.get_all_medicamente();
    sort(sorted_copy.begin(), sorted_copy.end(), cmp_producator);
    return sorted_copy;
}

 */
VectorDinamic<Medicament> Medicamente_Service::sortservice(int reverse, bool (*functie)(Medicament &, Medicament &)) {
    VectorDinamic<Medicament> v{repo.get_all_medicamente() };  //copie

    for (int i=0;i<v.size();i++)
    {
        for (int j=i+1;j<v.size();j++)
        {
            if (reverse == 0)
            {
                //crescator
                if (!functie(v.get(i),v.get(j)))
                {
                    Medicament aux = v.get(i);
                    v.get(i) = v.get(j);
                    v.get(j) = aux;
                }
            }
            else
            {
                //descrescator
                if (functie(v.get(i), v.get(j)))
                {
                    Medicament aux = v.get(i);
                    v.get(i) = v.get(j);
                    v.get(j) = aux;
                }
            }
        }
    }
    return v;
}

VectorDinamic<Medicament> Medicamente_Service::sortdenumire(int reverse) {
    return sortservice(reverse, cmp_denumire);
}

VectorDinamic<Medicament> Medicamente_Service::sortproducator(int reverse) {
    return sortservice(reverse, cmp_producator);
}

VectorDinamic<Medicament> Medicamente_Service::sortdsubstpret(int reverse) {
    return sortservice(reverse, cmp_substspret);
}


