#pragma once
//
// Created by Iris on 6/21/2024.
//

#ifndef TICTAC_SERVICE_H
#define TICTAC_SERVICE_H
#include "Repo.h"

class Service {
private:
    Repo& rep;
    int lastUsedId = 100;
public:
    Service(Repo& r) : rep{ r } {}
    vector<Joc> getAllJocuri();
    vector<Joc> sortStare();
    void addJoc(int dim, string tabla, string jucator);
    void modifica(int dim, string tabla, string jucator, string stare, int dimN, string tablaN, string jucatorN, string stareN);
    int findId(int dim, string tabla, string jucator, string stare);
    void deleteService(int id);
    void notify(int id, string tabla, string jucator, string stare);
};


#endif //TICTAC_SERVICE_H
