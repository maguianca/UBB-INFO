#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>
#include <algorithm>
using namespace std;

//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
int MD::dispersie(TCheie c)const {
	c = abs(c);
	return c % m;
}


void MD::actualizarePrimLiber() {
	primLiber++;
	while (primLiber < m && e[primLiber].first != INIT)
		primLiber++;
}

//CF:Theta(m)
//CD:Theta(m)
//CT:Theta(m)
MD::MD() {
	m = 300;
	n = 0;
	for (int i = 0; i < m; i++)
	{
		e[i].first = INIT;
		e[i].second = INIT;
		urm[i] = INIT;
	}
	primLiber = 0;
}

void MD::adauga(TCheie c, TValoare v) {
	int j, i = dispersie(c);
	if (e[i].first == INIT) {
		e[i].first = c;
		e[i].second = v;
		if (i == primLiber) {
			actualizarePrimLiber();
		}
		n++;
	}
	else {
		j = -1;
		while (i != INIT)
		{
			j = i;
			i = urm[i];
		}
		if (primLiber >= m)
			throw std::exception();
			
		    e[primLiber].first = c;
			e[primLiber].second = v;
			urm[j] = primLiber;
			actualizarePrimLiber();
			n++;
	}
}



bool MD::sterge(TCheie c, TValoare v) {
	TElem elem(c, v);
	int i = dispersie(c), j = INIT, k = 0, p, pp;
	bool gata;
	while (k < m && j == INIT) {
		if (urm[k] == i) j = k;
		else k++;
	}
	while (i != INIT && e[i] != elem) {
		j = i;
		i = urm[i];
	}
	if (i == INIT)
		return false;
	else {
		gata = false;
		do {
			p = urm[i];
			pp = i;
			while (p != INIT && dispersie(e[p].first) != i)
			{
				pp = p;
				p = urm[p];
			}
			if (p == INIT)
				gata = true;
			else {
				e[i] = e[p];
				j = pp;
				i = p;
			}
		} while (!gata);
		if (j != INIT)
			urm[j] = urm[i];
		e[i].first = INIT;
		urm[i] = INIT;
		if (primLiber > i)
			primLiber = i;
		n--;
		return true;
	}
}


vector<TValoare> MD::cauta(TCheie c) const {
	vector<TValoare>v;
	int pozitie = dispersie(c);
	while (pozitie != -1 && e[pozitie].first != c)
		pozitie = urm[pozitie];
	while (pozitie != -1 && e[pozitie].first == c) {
			v.push_back(e[pozitie].second);
			std::cout << "al " << v.size() << "-lea pe pozitia " << pozitie << " \n";
			std::cout <<pozitie<< "element" << e[pozitie].second << " \n";
			//printf("%d element: %d\n", poz,e[poz].second);
			pozitie = urm[pozitie];
			std::cout <<pozitie<< "element" << e[pozitie].second << " \n";
		}
	return v;
}


int MD::dim() const {
	return n;
}


bool MD::vid() const {
	return n==0;
}

IteratorMD MD::iterator() const {
	return IteratorMD(*this);
}


MD::~MD() {
}

