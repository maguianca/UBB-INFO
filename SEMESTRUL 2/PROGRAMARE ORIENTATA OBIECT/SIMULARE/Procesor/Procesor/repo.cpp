#include "repo.h"
#include<iostream>
#include <fstream>
#include <sstream>

void Repo::load_from_file_2()
{
    ifstream file(this->fisier2);
    if (!file.is_open()) {
        throw std::exception("nu se poate citi din fisier");
    }
    string line;
    while (getline(file, line))
    {
        string nume, soclu;
        int pret;
        stringstream linestream(line);
        string curent_item;
        int item_no = 0;
        while (getline(linestream, curent_item, ','))
        {
            if (item_no == 0) nume = curent_item;
            if (item_no == 1) soclu = curent_item;
            if (item_no == 2) pret = stoi(curent_item); 
            item_no++;
        }
        PlacaDeBaza s{ nume,soclu,pret };
        Repo::adauga(s);
    }
    file.close();
}

void Repo::load_from_file_1()
{
    ifstream file(this->fisier1);
    if (!file.is_open()) {
        throw std::exception("nu se poate citi din fisier");
    }
    string line;
    while (getline(file, line))
    {
        string nume, soclu;
        int pret, tr;
        stringstream linestream(line);
        string curent_item;
        int item_no = 0;
        while (getline(linestream, curent_item, ','))
        {
            if (item_no == 0) nume = curent_item;
            if (item_no == 1) tr = stoi(curent_item);
            if (item_no == 2) soclu = curent_item;
            if (item_no == 3) pret = stoi(curent_item); 
            item_no++;
        }
        Procesor1 s{ nume,tr,soclu,pret };
        Repo::adauga_procesor(s);
    }
    file.close();
}

void Repo::write_to_file_2()
{
    ofstream file(this->fisier2); 
    if (!file.is_open())
        throw::exception("nu se poate scrie in fisier");
    for (auto& placa : get_all_placi()) { 
        file << placa.get_nume() << "," << placa.get_soclu() << "," << placa.get_pret() << endl; 
    }
    file.close();
}

void Repo::adauga(const PlacaDeBaza& placa)
{
    placi.push_back(placa);
    write_to_file_2();
}
void Repo::adauga_procesor(const Procesor1&p)
{
    procesoare.push_back(p);
}

string Repo::cauta(string text)
{
    for (auto& placi : get_all_procesoare())
    {
        string aux = placi.get_nume()+"      "+to_string(placi.get_numar());
        if (text == aux)
        {
            return placi.get_soclu();
        }
    }
    return "";
}
int Repo::numar(string text)
{
    for (auto& placi : get_all_procesoare())
    {
        string aux = placi.get_nume() + "      " + to_string(placi.get_numar());
        if (text == aux)
        {
            return placi.get_pret();
        }
    }
    return 0;
}
int Repo::numar_2(string text)
{
    for (auto& placi : get_all_placi())
    {
        string aux = placi.get_nume();
        if (text == aux)
        {
            return placi.get_pret();
        }
    }
    return 0;
}
