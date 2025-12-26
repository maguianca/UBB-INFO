//
// Created by Ilinca on 30-Mar-22.
//

#ifndef LAB4_6OOP_SERVICE_H
#define LAB4_6OOP_SERVICE_H

#pragma once
#include "Repository.h"
#include "Validators.h"
#include <functional>
using std::function;

class Medicamente_Service{
private:
    Medicament_Repository& repo;
    Medicament_Validator& val;

    vector<Medicament> general_sort(bool(*mai_mic_f)(const Medicament&, const Medicament&));

public:
    Medicamente_Service(Medicament_Repository& med_repo, Medicament_Validator& val) :repo{ med_repo }, val{ val } {};

    //constructor de copiere
    //punem delete fiindca nu vrem sa se faca nicio copie la Service
    //(in aplicatie avem 1 singur Service)
    Medicamente_Service(const Medicamente_Service& ot) = delete;

    /*
	Adauga un medicament cu denumirea denumire, producatorul producator, substanta activa substanta activa si pretul pret
	*@param denumire: denumirea medicamentului care se adauga (string)
	*@param producator: producatorul medicamentului care se adauga (string)
	*@param substanta_activa: substanta activa medicamentului care se adauga (string)
	*@param pret: pretul medicamentului care se adauga (double)
	*
	* @throws:
	*	RepoException daca mai exista medicament cu denumirea si producatorul dat
	*	ValidationException daca medicamentul nu este valid
	*/

    void add_medicament(string denumire, string producator, string substanta_activa, double pret);

    /*
	Returneaza un vector cu toate medicamentele disponibile

	@return: lista cu toate medicamentele disponibile (vector cu obiecte de tip Medicament)
	*/

    VectorDinamic<Medicament>& get_all_medicamente() {
        return this->repo.get_all_medicamente();
    }


    /*
	Modifica pretul unui medicament cu denumirea denumire, producatorul producator, substanta activa substanta activa si noul pret pret_nou
	*@param denumire: denumirea medicamentului ce se modifica (string)
	*@param producator: producatorul medicamentului ce se modifica (string)
	*@param substanta_activa: substanta activa medicamentului ce se modifica (string)
	*@param pret_nou: pretul nou al medicamentului (double)
	*
	* @throws:
	*	RepoException daca nu exista medicament cu denumirea si producatorul dat
	*	ValidationException daca medicamentul nu este valid
	*/
    void modifica_pret_service(string denumire, string producator, string substanta_activa, double pret_nou);
    /*
	Sterge un medicament cu denumirea denumire, producatorul producator, substanta activa substanta activa si pretul pret
	*@param denumire: denumirea medicamentului ce se sterge (string)
	*@param producator: producatorul medicamentului ce se sterge (string)
	*@param substanta_activa: substanta activa medicamentului ce se sterge (string)
	*@param pret: pretul medicamentului ce se sterge (double)
	*
	* @throws:
	*	RepoException daca nu exista medicament cu denumirea si producatorul dat
	*	ValidationException daca medicamentul nu este valid
	*/
    void stergere_service(string denumire, string producator, string substanta_activa, double pret);

    /*
     * Filtreaza medicamentele din lista care au substanta activa substanta_activa
     *@param substanta_activa: substanta activa dupa care se face filtrarea (string)
	 *@return: lista noua cu medicamentele filtrate
     */
    VectorDinamic<Medicament> filtrare_substanta_activa(string substanta_activa);
    /*
     * Filtreaza medicamentele din lista care au pretul pret
     *@param substanta_activa: pretul dupa care se face filtrarea (double)
	 *@return: lista noua cu medicamentele filtrate
     */
    VectorDinamic<Medicament> filtrare_pret(double pret);

    /*
    functie de sortare a produselor dupa denumire
    param reverse: 0-ordine crescatoare,1-descrescatoare
     */
    vector<Medicament> sort_by_denumire();
    /*
    functie de sortare a produselor dupa producator
    param reverse: 0-ordine crescatoare,1-descrescatoare*/
    vector<Medicament> sort_by_producator();

    /*
     Functie de sortare generala
     functie - functie de comparare, verifica daca are loc relatia intre cele 2 produse
     returneaza o lista sortata dupa criteriu dat ca paramatru
    */
    VectorDinamic<Medicament> sortservice(int reverse, bool (*functie)( Medicament&, Medicament&));

    VectorDinamic<Medicament> sortdenumire(int reverse);
    VectorDinamic<Medicament> sortproducator(int reverse);
    VectorDinamic<Medicament> sortdsubstpret(int reverse);


};

void teste_service();

#endif //LAB4_6OOP_SERVICE_H
