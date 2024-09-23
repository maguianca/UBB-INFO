#pragma once
#pragma once
#pragma once
#pragma once
#include"repo.h"
#include"service.h"
#include"UI.h"
//#include"vector.h"
#include"CosOferte.h"
void test_validator();
//valideaza clasa validator
void test_repo_adauga();
//testeaza_functia de adauga din repo
void test_repo_stergere();
//testeaza_functia de stergere din repo
void test_repo_cauta();
//testeaza_functia de cauta din repo
void test_service_adauga();
//testeaza_functia de adauga din service
void test_service_modifica();
//testeaza_functia de modifica din service
void test_service_stergere();
//testeaza functia de stergere din service
void test_service_cautare();
//testeaza functia de cauta din service
void test_service_filtrare_destinatie();
//testeaza functie de filtrare din service
void test_service_filtrare_pret();
//testeaza functie de filtrare din service
void test_sortare();
//testeaza functie de sortare
void teste_teste();
//contine toate testele
int sort_denumire1(const Turism& o1, const Turism& o2);
//returneaza 1 daca elementele Turism sunt ordonate crescator dupa denumire altfel 0
int sort_destinatie1(const Turism& o1, const Turism& o2);
//returneaza 1 daca elementele Turism sunt ordonate crescator dupa destinatie altfel 0
int sort_tip_pret1(const Turism& o1, const Turism& o2);
//returneaza 1 daca elementele Turism sunt ordonate crescator dupa pret si tip altfel 0
void test_cos();
//testeaza functionalitatea operatiilor din Clasa CosOferta
void teste_teste();
//apeleaza toate functiile de teste