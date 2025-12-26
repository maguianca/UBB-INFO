#pragma once
//
// Created by david on 17.05.2022.
//


#include "RepoCandidati.h"

class Service {
private:
    RepoCandidati& repoPlacaDeBaza;
public:
    Service(RepoCandidati& repoPlacaDeBaza) :repoPlacaDeBaza{ repoPlacaDeBaza } {};

    vector<Candidat>& getPlaciDeBaza() {
        return repoPlacaDeBaza.getAll();
    }
    void addPlaca(string nume,
        string soclu,
        int pret);

    vector<Candidat> filterBySoclu(string name);
    int pret(string numeProcesor, string numePlaca);
};

