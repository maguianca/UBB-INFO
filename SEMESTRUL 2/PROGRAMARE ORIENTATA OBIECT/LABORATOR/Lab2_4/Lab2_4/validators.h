#pragma once
#include<string.h>
#include<assert.h>
#include"domeniu.h"
int valideaza(buget b);
int validare_tipul(char tip[21]);
int validare_negativ(int x);
int valideaza_zi(int zi);
void test_tipul();
void test_negativ();
void test_valideaza();
void test_valideaza_zi();
void test_validators();