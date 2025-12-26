//
// Created by Ilinca on 30-Mar-22.
//

#ifndef LAB4_6OOP_VALIDATORS_H
#define LAB4_6OOP_VALIDATORS_H

#pragma once
#include "Medicament.h"
#include <vector>
#include <string>
using std::vector;
using std::string;

class Validation_Exception{
    vector<string> error_msg;

public:
    Validation_Exception(vector<string> error_mesagges) : error_msg{error_mesagges } {};

    string get_error_messages() {
        string full_msg = "";
        for(const string e : error_msg) {
            full_msg += e + "\n";
        }
        return full_msg;
    }
};

/*
 * Un medicament este valid daca, are
 * denumirea din mai mult de 2 caractere
 * producatorul din mai mult de 2 caractere
 * substanta activa  din mai mult de 2 caractere
 * pretul este pozitiv
 */

class Medicament_Validator{

public:
    void valideaza(const Medicament& m){
        vector<string> errors;
        if(m.get_denumire().length() < 2)
            errors.push_back("Denumirea trebuie sa aiba cel putin 2 caractere.");
        if(m.get_producator().length() < 2)
            errors.push_back("Producatorul trebuie sa aiba cel putin 2 caractere.");
        if(m.get_substanta_activa().length() < 1)
            errors.push_back("Substanta activa trebuie sa aiba cel putin 1 caracter.");
        if(m.get_denumire().length() < 2)
            errors.push_back("Denumirea trebuie sa aiba cel putin 2 caractere.");
        if(m.get_pret() < 0)
            errors.push_back("Pretul  trebuie sa fie pozitiv.");

        if(errors.size() > 0)
            throw Validation_Exception(errors);

    }
};

#endif //LAB4_6OOP_VALIDATORS_H
