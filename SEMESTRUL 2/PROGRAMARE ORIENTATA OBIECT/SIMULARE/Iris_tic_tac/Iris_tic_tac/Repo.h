#pragma once
//
// Created by Iris on 6/21/2024.
//

#ifndef TICTAC_REPO_H
#define TICTAC_REPO_H
#include "Joc.h"
#include <vector>
using std::vector;

class Repo {
private:
    string fileName;
    vector<Joc> listaJocuri;
    void loadFromFile();
    void loadToFile();
    Joc parseCsvToJoc(string& s);
    string parseJocToCsv(Joc& j);



public:
    Repo() :fileName("date.csv") { loadFromFile(); };
    vector<Joc> getAll();
    void addJoc(Joc& j);
    void deleteJoc(Joc& j);
    void modificaStare(int id, string tabla, string jucator, string stare);
};


#endif //TICTAC_REPO_H
