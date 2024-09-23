#pragma once
#pragma once
#pragma once
#include"domeniu.h"
#include"repo.h"
#include"validators.h"
#include<stdio.h>
#include<assert.h>
#include<string.h>
int service_adaugare(int suma, int zi, char* tip, Lista* l);
int service_modificare(int suma, int zi, char* tip, int m_suma, int m_zi, char* m_tip, Lista* l);
int service_stergere(int suma, int zi, char* tip, Lista* l);
Lista service_filtrare_suma(int suma, Lista* l);
Lista service_filtrare_tip(char* tip, Lista* l);
Lista service_filtrare_zi(int zi, Lista* l);
Lista* service_ordonare(int tipul, int ascensiune, Lista* l);
void test_service_adauga();
void test_service_modifica();
void test_service_sterge();
void test_service_filtrare_suma();
void test_service_filtrare_tip();
void test_service_filtrare_zi();
void test_comparare_tip();
void test_comparare_suma();
void test_service_sortare();
void test_service();
int comparesuma_d(buget a, buget b);
int comparesuma_c(buget a, buget b);
int comparetip_c(buget a, buget b);
int comparetip_d(buget a, buget b);
Lista* service_sortare_2(Lista* l, int (*comparator)(buget a, buget b));