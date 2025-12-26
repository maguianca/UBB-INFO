//
// Created by Iris on 6/21/2024.
//

#include "Service.h"
#include <algorithm>
#include "Validator.h"
vector<Joc> Service::getAllJocuri() {
    return rep.getAll();
}

vector<Joc> Service::sortStare() {
    vector<Joc> listaRez = getAllJocuri();
    std::sort(listaRez.begin(), listaRez.end(), [&](Joc& j1, Joc& j2) {
        return j1.getStare() < j2.getStare();
        });
    return listaRez;
}

void Service::addJoc(int dim, string tabla, string jucator) {
    lastUsedId++;
    Joc j(lastUsedId, dim, tabla, jucator, "Neinceput");
    rep.addJoc(j);
}

void Service::modifica(int dim, string tabla, string jucator, string stare, int dimN, string tablaN, string jucatorN, string stareN) {
    if (Validator::valideazaDate(dimN, tablaN, jucatorN, stareN))
    {
        int id = findId(dim, tabla, jucator, stare);
        Joc j(id, dim, tabla, jucator, stare);
        rep.deleteJoc(j);
        Joc jNou(id, dimN, tablaN, jucatorN, stareN);
        rep.addJoc(jNou);
    }
}

int Service::findId(int dim, string tabla, string jucator, string stare) {
    for (auto& j : getAllJocuri())
        if (j.getDim() == dim && j.getTabla() == tabla && j.getJucator() == jucator && j.getStare() == stare)
            return j.getId();
}

void Service::deleteService(int id) {
    for (auto& j : getAllJocuri())
        if (j.getId() == id)
        {
            Joc joc(id, j.getDim(), j.getTabla(), j.getJucator(), j.getStare());
            rep.deleteJoc(joc);
        }
}


void Service::notify(int id, string tabla, string jucator, string stare) {
    rep.modificaStare(id, tabla, jucator, stare);
}
