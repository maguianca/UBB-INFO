//
// Created by Iris on 6/21/2024.
//

#include "Repo.h"
#include <fstream>
#include <sstream>
using std::ifstream;
using std::ofstream;

void Repo::loadFromFile() {
    ifstream fin(fileName);
    string line;
    vector<Joc> listaDeAdaugat;
    while (getline(fin, line))
    {
        listaDeAdaugat.push_back(parseCsvToJoc(line));
    }
    for (auto& j : listaDeAdaugat)
        addJoc(j);
}

Joc Repo::parseCsvToJoc(string& line) {
    line = line.substr(0, line.length());
    std::istringstream iss(line);
    vector<string> componente;
    string value;
    while (getline(iss, value, ','))
        componente.push_back(value);
    Joc j(stoi(componente[0]), stoi(componente[1]), componente[2], componente[3], componente[4]);
    return j;
}

void Repo::addJoc(Joc& j) {
    listaJocuri.push_back(j);
    loadToFile();
}

void Repo::loadToFile() {
    ofstream fout(fileName);
    for (auto& j : listaJocuri)
    {
        string line = parseJocToCsv(j);
        fout << line;
    }
}

string Repo::parseJocToCsv(Joc& j) {
    string line = std::to_string(j.getId()) + ',' + std::to_string(j.getDim()) + ',' + j.getTabla() + ',' + j.getJucator() + ',' + j.getStare() + '\n';
    return line;
}

vector<Joc> Repo::getAll() {
    return listaJocuri;
}

void Repo::deleteJoc(Joc& j) {
    for (int i = 0; i < listaJocuri.size(); i++) {
        auto joc = listaJocuri[i];
        if (joc.getDim() == j.getDim() && joc.getTabla() == j.getTabla() && joc.getJucator() == j.getJucator() &&
            joc.getStare() == j.getStare())
            listaJocuri.erase(listaJocuri.begin() + i);
    }
    loadToFile();
}

void Repo::modificaStare(int id, string tabla, string jucator, string stare) {
    for (auto& j : listaJocuri) {
        if (j.getId() == id) {
            j.setJucator(jucator);
            j.setStare(stare);
            j.setTabla(tabla);
            loadToFile();
        }
    }
}
