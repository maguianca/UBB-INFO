#pragma once
#include <stdio.h>
#include <string.h>
#include"domeniu.h"
#include"repo.h"
#include"service.h"
#include "UI.h"

void meniu();
void afisare(Lista lista_buget);
void ui_adaugare(Lista* lista_buget);

void ui_modificare(Lista* lista_buget);

void ui_stergere(Lista* lista_buget);

void ui_filtrare(Lista* lista_buget);
void ui_sortare(Lista* lista_buget);

void consola(Lista* lista_buget);
void test();
void meniu_filtrare();