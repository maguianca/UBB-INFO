#pragma once
//
// Created by Iris on 6/21/2024.
//

#ifndef TICTAC_JOC_H
#define TICTAC_JOC_H
#include <string>
using std::string;

class Joc {
private:
    int id;
    int dim;
    string tabla;
    string jucator;
    string stare;
public:
    Joc(int i, int d, string tab, string juc, string st) : id{ i }, dim{ d }, tabla{ tab }, jucator{ juc }, stare{ st } {}
    int getId()const { return id; }
    int getDim()const { return dim; }
    string getTabla()const { return tabla; }
    string getJucator()const { return jucator; }
    string getStare()const { return stare; }
    void setStare(string newStare) { stare = newStare; }
    void setTabla(string tabla) { this->tabla = tabla; }
    void setJucator(string jucator) { this->jucator = jucator; }

};


#endif //TICTAC_JOC_H
