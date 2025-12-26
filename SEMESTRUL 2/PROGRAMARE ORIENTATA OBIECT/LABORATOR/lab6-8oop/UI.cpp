//
// Created by Ilinca on 30-Mar-22.
//

#pragma once
#include "UI.h"
#include <iostream>
using namespace std;

void Console::print_meniu() {
    cout<<"Comenzile disponibile sunt:"<<endl;
    cout<<"1. Adauga un medicament."<<endl;
    cout<<"2. Modifica pretul unui medicament."<<endl;
    cout<<"3. Sterge un medicament."<<endl;
    cout<<"4. Afiseaza toate medicamentele."<<endl;
    cout<<"5. Filtrare medicamente dupa substanta activa/pret."<<endl;
    cout<<"6. Sorteaza medicamente dupa denumire/producator/substanta activa+pret."<<endl;
    cout<<"0. Exit."<<endl;
}

void Console::ui_add() {
    string denumire, producator, substanta_activa;
    double pret;
    cout<<"Denumirea medicamentului este:";
    getline(cin>> ws , denumire);

    cout<<"Producatorul medicamentului este:";
    getline(cin>> ws , producator);

    cout<<"Substanta activa a medicamentului este:";
    getline(cin>> ws , substanta_activa);

    cout<<"Pretul medicamentului este:";
    cin >> pret;

    try{
        srv.add_medicament(denumire, producator, substanta_activa, pret);
    }
    catch (Repo_Exception& re) {
        cout << re.get_error_message();
    }
    catch (Validation_Exception& ve) {
        cout << "Medicamentul introdus nu este valid!" << endl;
        cout << ve.get_error_messages();
    }
}


void Console::print_all_medicamente() {
        VectorDinamic<Medicament>& all_medicamente = srv.get_all_medicamente();
        if(all_medicamente.size() == 0)
            cout << "Nu exista medicamente in lista!"<<endl;
        else
            for(const auto& med : all_medicamente){
                cout<<"Denumire: " << med.get_denumire() <<" || Producator: " << med.get_producator() << " || Substanta activa: " << med.get_substanta_activa() << " || Pret: " << med.get_pret() << endl;

            }

}

void Console::ui_modificare() {
    string denumire, producator, substanta_activa;
    double pret_nou;
    cout << "Denumirea medicamentului pe care doriti sa o modificati: \n";
    getline(cin >> ws, denumire);

    cout << "Producatorul medicamentului pe care doriti sa o modificati: \n";
    getline(cin >> ws, producator);

    cout << "Substanta activa a medicamentului pe care doriti sa o modificati: \n";
    getline(cin >> ws, substanta_activa);

    cout << "Noul pret al medicamentului: \n";
    cin >> pret_nou;
    try{
        srv.modifica_pret_service(denumire, producator, substanta_activa, pret_nou);
        cout << "Pretul medicamentului a fost modificat cu succes!!\n";
    }
    catch (Repo_Exception& re){
        cout << re.get_error_message();
    }
    catch (Validation_Exception& ve) {
        cout << "Medicamentul nu este valid!!" << endl;
        cout << ve.get_error_messages();
    }
}

void Console::ui_stergere(){
    string denumire, producator, substanta_activa;
    double pret;
    cout << "Denumirea medicamentului pe care doriti sa il stergeti:\n";
    getline(cin >> ws, denumire);

    cout << "Producatorul medicamentului pe care doriti sa il stergeti:\n";
    getline(cin >> ws, producator);

    cout << "Substanta activa a medicamentului pe care doriti sa il stergeti:\n";
    getline(cin >> ws, substanta_activa);

    cout << "Pretul medicamentului:\n";
    cin >> pret;

    try{
        srv.stergere_service(denumire, producator, substanta_activa, pret);
        cout << "Medicamentul a fost sters cu succes!\n";
    }
    catch (Repo_Exception& re){
        cout << re.get_error_message();
    }
    catch (Validation_Exception& ve){
        cout << ve.get_error_messages();
    }
}

void Console::ui_filtrare() {
    cout << "Optiunile pentru filtrare sunt:\n";
    cout << "1 - dupa substanta activa.\n";
    cout << "2 - dupa pret.\n";
    int filtru;
    string denumire, producator, substanta_activa;
    double pret;
    cout << "Introduceti filtrul dorit:\n";
    cin >> filtru;
    if (filtru == 1) {
        cout << "Introduceti substanta activa dupa care doriti sa se faca filtrarea:\n";
        getline(cin >> ws, substanta_activa);
        if (srv.filtrare_substanta_activa(substanta_activa).size() == 0)
            cout << "Nu exista medicamente cu aceasta substanta activa!\n";
        for (const auto &med: srv.filtrare_substanta_activa(substanta_activa)) {
            cout << "Denumire: " << med.get_denumire() << " || Producator: " << med.get_producator()
                 << " || Substanta activa: " << med.get_substanta_activa() << " || Pret: " << med.get_pret() << endl;

        }
    }

    if (filtru == 2) {
        cout << "Introduceti pretul dupa care doriti sa se faca filtrarea:\n";
        cin >> pret;
        if (srv.filtrare_pret(pret).size() == 0)
            cout << "Nu exista medicamente cu acest pret!\n";
        for (const auto &med: srv.filtrare_pret(pret)) {
            cout << "Denumire: " << med.get_denumire() << " || Producator: " << med.get_producator()
                 << " || Substanta activa: " << med.get_substanta_activa() << " || Pret: " << med.get_pret() << endl;

        }
    }
}

//void Console::print_meds

void Console::ui_sort() {
    int ordine, optiune;
    cout << "Sortati dupa:" << endl;
    cout << "1-Denumire    2-Producator    3-Substanta activa+Pret" << endl;
    cin >> optiune;
    cout << "Ordinea poate fi: 0-crescator      1-descrescator:" << endl;
    cin >> ordine;
    if (optiune == 1)
    {
        for (const auto& med: srv.sortdenumire(ordine))
        {
            cout << "Denumire: " << med.get_denumire() << " || Producator: " << med.get_producator()
                 << " || Substanta activa: " << med.get_substanta_activa() << " || Pret: " << med.get_pret() << endl;

        }
    }
    if (optiune == 2)
    {
        for (const auto& med: srv.sortproducator(ordine))
        {
            cout << "Denumire: " << med.get_denumire() << " || Producator: " << med.get_producator()
                 << " || Substanta activa: " << med.get_substanta_activa() << " || Pret: " << med.get_pret() << endl;

        }
    }
    if (optiune == 3)
    {
        for (const auto& med: srv.sortdsubstpret(ordine))
        {
            cout << "Denumire: " << med.get_denumire() << " || Producator: " << med.get_producator()
                 << " || Substanta activa: " << med.get_substanta_activa() << " || Pret: " << med.get_pret() << endl;

        }
    }
}


void Console:: run(){
    int running = 1;
    int cmd;
    while(running){
        print_meniu();
        cout << "Comanda dumneavoatra este:";
        cin >> cmd;
        switch (cmd) {
            case 1:
                ui_add();
                break;
            case 2:
                ui_modificare();
                break;
            case 3:
                ui_stergere();
                break;
            case 4:
                print_all_medicamente();
                break;
            case 5:
                ui_filtrare();
                break;
            case 6:
                ui_sort();
                break;
            case 0:
                running = 0;
                break;
            default:
                break;

        }
    }
}

