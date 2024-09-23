#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>
#include<algorithm>
using namespace std;

//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
int MD::dispersie(TCheie c) {
	c = abs(c);
	return c % capacitate;
}
//CF:Theta(n)
//CD:Theta(n)
//CT:Theta(n)
MD::MD() {
	capacitate = 200;
	primLiber = 0;
	dimensiune = 0;
	elem = new TElem[capacitate];
	urmator = new int[capacitate];
	for (int i = 0; i < capacitate; i++) {
		urmator[i] = -1;
		elem[i].first = -1000000;
		elem[i].second = -1000000;
	}
}

//CD:Theta(n)
//CF:Theta(1)
//CM:Theta(1)
//CT:O(n)
void MD::adauga(TCheie c, TValoare v) {
	int pozitie = dispersie(c);
	if (dimensiune == capacitate)
	{
		redimensionare();
		rehashing();
	}
	if (elem[pozitie].first == -1000000) {
		elem[pozitie].first = c;
		elem[pozitie].second = v;
		urmator[pozitie] = -1;
		dimensiune++;
	}
	else {
		elem[primLiber].first = c;
		elem[primLiber].second = v;
		urmator[primLiber] = -1;
		while (urmator[pozitie] != -1)
		{
			pozitie = urmator[pozitie];
		}
		urmator[pozitie] = primLiber;
		dimensiune++;
	}
	if (elem[primLiber].first != -1000000)
		primLiber = actualizarePrimLiber();
}

//CD:Theta(n)
//CF:Theta(1)
//CM:Theta(1)
//CT:O(n) n-capacitatea
bool MD::sterge(TCheie c, TValoare v) {
	int i= dispersie(c);
	int p, pp, j=-1;
	bool gata;
	for (int k = 0; k < capacitate && j == -1; k++)
		if (urmator[k] == i)
			j = k;
	while (i != -1 && !(elem[i].first == c && elem[i].second == v)) {
		j = i;
		i = urmator[i];
	}
	if (i == -1)
		return false;
	else {
		gata = false;
		do {
			p = urmator[i];
			pp = i;
			while (p != -1 && dispersie(elem[p].first) != i)
			{
				pp = p;
				p = urmator[p];
			}
			if (p == -1)
				gata = true;
			else {
				elem[i] = elem[p];
				i = p;
				j = pp;
			}
		} while (!gata);
		if (j != -1) {
			urmator[j] = urmator[i];
		}
		elem[i].first = -1000000;
		elem[i].second = -1000000;
		urmator[i] = -1;
		if (primLiber > i)
			primLiber = i;
		dimensiune--;
		return true;
	}
}

//CD:theta(n)
//CF:Theta(1)
//CM:Theta(1)
//CT:O(n)
vector<TValoare> MD::cauta(TCheie c){
	std::vector<TValoare>v;
	int pozitie = dispersie(c);
	while (pozitie != -1)
	{
		if (elem[pozitie].first == c)
			v.push_back(elem[pozitie].second);
		pozitie = urmator[pozitie];
	}
	return v;
}

//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
int MD::dim() const{
	return dimensiune;
}

//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
bool MD::vid() const {
	return dimensiune==0;
}
//CF:Theta(n)
//CD:Theta(n)
//CT:Theta(n)
void MD::redimensionare()
{
	TElem* elem_nou = new TElem[capacitate * 2];
	int* urmator_nou = new int[capacitate * 2];
	for (int i = 0; i < capacitate; i++) {
		elem_nou[i] = elem[i];
		urmator_nou[i] = urmator[i];
	}
	for (int i = capacitate; i < capacitate * 2; i++)
	{
		elem_nou[i].first = -1000000;
		elem_nou[i].second = -1000000;
		urmator_nou[i] = -1;
	}
	primLiber = capacitate;
	capacitate = capacitate * 2;
	delete[]elem;
	delete[]urmator;
	elem = elem_nou;
	urmator = urmator_nou;
}
//CF:Theta(n)
//CD:Theta(n)
//CT:Theta(n)
void MD::rehashing() {
	TElem* elem_vechi = new TElem[capacitate];
	for (int i = 0; i < capacitate; i++)
		elem_vechi[i] = elem[i];
	int dimensiune_veche = dimensiune;
	for (int i = 0; i < capacitate; i++)
	{
		elem[i].first = -1000000;
		elem[i].second = -1000000;
		urmator[i] = -1;
	}
	primLiber = actualizarePrimLiber();
	dimensiune = 0;
	for (int i = 0; i < dimensiune_veche; i++)
		adauga(elem_vechi[i].first, elem_vechi[i].second);
}
//CF:Theta(n)
//CD:Theta(n)
//CT:Theta(n)
int MD::actualizarePrimLiber() {
	for (int i = 0; i < capacitate; i++)
		if (elem[i].first == -1000000)
			return i;
}
//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
IteratorMD MD::iterator() const {
	return IteratorMD(*this);
}

//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
MD::~MD() {
	delete[] this->elem;
	delete[] this->urmator;
}
//CF:Theta(n)
//CD:Theta(n)
//CT:Theta(n)
vector<TValoare> MD::colectiaValorilor() const
{
	vector<TValoare> valori;
	for (int i = 0; i < capacitate; ++i) {
		if (elem[i].first != -1000000) {
			valori.push_back(elem[i].second);
			//int urm = urmator[i];
			//while (urm != -1) {
			//	valori.push_back(elem[urm].second);
			//	urm = urmator[urm];
			//}
		}
	}
	return valori;
}

