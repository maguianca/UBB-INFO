//
// Created by Ilinca on 30-Mar-22.
//

#include "Repository.h"
#include "VectorDinamicTemplate.h"
#include <assert.h>

const Medicament& Medicament_Repository::find(string denumire, string producator) {
    for(const Medicament& m: this->all_medicamente){
        if(m.get_denumire() == denumire && m.get_producator() == producator){
            return m;
        }
    }
    throw Repo_Exception("Medicamentul cu denumirea "+denumire+" si producatorul "+producator+" nu este in lista");
}

bool Medicament_Repository::exists(const Medicament &m) {
    try{
        find(m.get_denumire(),m.get_producator());
        return true;
    }
    catch (Repo_Exception) {
        return false;
    }
}

VectorDinamic<Medicament>& Medicament_Repository::get_all_medicamente() {
    return this->all_medicamente;
}

void Medicament_Repository::store(const Medicament& m) {
    if(exists(m)){
        throw Repo_Exception("Medicamentul cu denumirea "+m.get_denumire()+" si producatorul "+m.get_producator()+" nu este in lista");
    }
    this->all_medicamente.add(m);
}


void Medicament_Repository::modificare_pret_repo(const Medicament &med) {
    if(!exists(med)){
        throw Repo_Exception("Medicamentul dorit nu este in lista!\n");
    }
    int i = 0;
    for(auto& medic : this->all_medicamente){
        if(medic.get_denumire() == med.get_denumire() && medic.get_producator() == med.get_producator() && medic.get_substanta_activa() == med.get_substanta_activa()){
            medic.set_pret(med.get_pret());
            //medic=med;
        }
        i++;
    }
}

int Medicament_Repository::findindex(string denumire, string producator) {
    for (int i=0; i<this->all_medicamente.size();i++) {
        if(this->all_medicamente.get(i).get_denumire() == denumire && this->all_medicamente.get(i).get_producator() == producator) {
            return i;
        }
    }
    return -1;
}

void Medicament_Repository::stergere_repo(const Medicament &med) {
    if(!exists(med)){
        throw Repo_Exception("Medicamentul nu este in lista.\n");
}
    /*
    int i=0;
    for( auto& medic : this->all_medicamente){
        if(medic.get_denumire() == med.get_denumire() && medic.get_producator() == med.get_producator() && medic.get_substanta_activa() == med.get_substanta_activa() && medic.get_pret() == med.get_pret()){
            this->all_medicamente.remove(this->all_medicamente.begin()+i);
        }
        i++;
    }
}
     */
    const int index = findindex(med.get_denumire(), med.get_producator());
    if(index != -1)
    {
    this->all_medicamente.remove(index);
    }
}
