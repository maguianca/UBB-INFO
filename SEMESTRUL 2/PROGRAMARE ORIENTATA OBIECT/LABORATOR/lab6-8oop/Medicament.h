//
// Created by Ilinca on 30-Mar-22.
//

#ifndef LAB4_6OOP_MEDICAMENT_H
#define LAB4_6OOP_MEDICAMENT_H

#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class Medicament{
private:
    string denumire;
    string producator;
    string substanta_activa;
    double pret;

public:
    Medicament() = default;
    Medicament(string denumire, string producator, string substanta_activa, double pret): denumire { denumire }, producator { producator }, substanta_activa{ substanta_activa }, pret{ pret } {};
    Medicament(const Medicament& ot) :denumire{ ot.denumire }, producator{ ot.producator }, substanta_activa{ ot.substanta_activa }, pret{ ot.pret }{
        //cout << "[MEDICAMENT] Copy constructor called."<<endl;
    }
    /*
     * Get-er pentru denumirea unui medicament
     * @return: denumirea medicamentului
     */
    string get_denumire() const;
    /*
     * Get-er pentru producatorul unui medicament
     * @return: producatorul medicamentului
     */
    string get_producator() const;
    /*
     * Get-er pentru substanta activa a unui medicament
     * @return: substanta activa a medicamentului
     */
    string get_substanta_activa() const;
    /*
     * Get-er pentru pretul unui medicament
     * @return: pretul unui medicamentului
     */
    double get_pret() const;
    /*
     * Set-er pentru denumirea unui medicament
     */
    void set_denumire(string denumire_noua);
    /*
     * Set-er pentru producatorul unui medicament
     */
    void set_producator(string producator_nou);
    /*
     * Set-er pentru substanta activa a unui medicament
     */
    void set_substanta_activa(string substanta_activa_noua);
    /*
     * Set-er pentru pretul unui medicament
     */
    void set_pret(double pret_nou);

};

/*
 * Compara 2 melodii dupa denumire
 * @return: true daca denumirea medicamentului e mai mica lexicografic decat
 *          denumirea medicamentului m2, false altfel
 */
bool cmp_denumire(Medicament& m1, Medicament& m2);


/*
 * Compara 2 melodii dupa producator
 * @return: true daca producatorul medicamentului e mai mic lexicografic decat
 *          producatorul medicamentului m2, false altfel
 */
bool cmp_producator(Medicament& m1, Medicament& m2);

bool cmp_substspret(Medicament& m1, Medicament& m2);

void teste_domain();

#endif //LAB4_6OOP_MEDICAMENT_H
