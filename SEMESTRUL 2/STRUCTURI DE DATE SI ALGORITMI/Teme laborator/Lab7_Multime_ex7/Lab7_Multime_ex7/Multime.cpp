#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
bool rel(TComparabil e1, TComparabil e2)
{
	return e1 <= e2;
}
//CF:Theta(1)
//CD:Theta(n)n-h
//CT:O(n)n-h
int Multime::minim(int p)
{
	while (p != -1)
		p = stang[p];
	return p;
}
//CF:Theta(1)
//CD:Theta(n)
//CT:O(n)
int Multime::creeazaNod(TComparabil e)
{
	if (size>= cp) {
		resize();
	}
	int p = aloca();
	elems[p] = e;
	stang[p] = -1;
	drept[p] = -1;
	return p;
}
//CF:Theta(n)
//CD:Theta(n)
//CT:Theta(n)
Multime::Multime() {
	cp = 100;
	size = 0;
	elems = new TComparabil[cp];
	stang = new int[cp];
	drept = new int[cp];
	radacina = -1;
	for (int i = 0; i < cp - 1; i++)
	{
		drept[i] = i + 1;
		stang[i] = i - 1;
	}
	stang[0] = -1;
	drept[cp - 1] = -1;
	primLiber = 0;

}

//CF:Theta(1)
//CD:Theta(n)
//CT:O(n)
bool Multime::adauga(TComparabil elem) {
	if (radacina == -1)
	{
		radacina = creeazaNod(elem);
		size++;
		return true;
	}
	int pos = radacina;
	int parinte = pos;
	while (pos != -1) {
		parinte = pos;
		if (elem == elems[pos])
			return false;
		if (rel(elem, elems[pos]))
		{
			pos = stang[pos];
		}
		else
			pos = drept[pos];
	}
	int p = creeazaNod(elem);
	if (rel(elem, elems[parinte]))
		stang[parinte] = p;
	else
		drept[parinte] = p;
	size++;
	return true;
}


/*
bool Multime::sterge(TComparabil elem) {
	
	return sterge_recursiv(radacina,-1,elem);
}*/
//CF:Theta(1)
//CD:Theta(n)
//CT:O(n)n-h
bool Multime::sterge(TComparabil elem) {
	if (radacina == -1) {
		// arborele e gol
		return false;
	}

	int curent = radacina;
	int anterior = -1;
	bool gasit = false;

	// Gasim nodul care trebuie sters
	while (curent != -1 && !gasit) {
		if (elems[curent] == elem) {
			gasit = true;
		}
		else {
			anterior = curent;
			if (rel(elem, elems[curent])) {
				curent = stang[curent];
			}
			else {
				curent = drept[curent];
			}
		}
	}

	if (!gasit) {
		// Elementul nu a fost gasit
		return false;
	}

	// Eliminam nodul
	if (stang[curent] == -1 && drept[curent] == -1) {
		if (curent == radacina) {
			radacina = -1;
		}
		else {
			if (stang[anterior] == curent) {
				stang[anterior] = -1;
			}
			else {
				drept[anterior] = -1;
			}
		}
	}
	else if (stang[curent] == -1 || drept[curent] == -1) {
		int copil;
		if (stang[curent] != -1) {
			copil = stang[curent];
		}
		else {
			copil = drept[curent];
		}
		if (curent == radacina) {
			radacina = copil;
		}
		else {
			if (stang[anterior] == curent) {
				stang[anterior] = copil;
			}
			else {
				drept[anterior] = copil;
			}
		}
	}
	else {
		/*
		// nodul are doi fii
		int succesorAnterior = curent;
		int succesor = drept[curent];

		//int min = minim(succesor);
		while (stang[succesor] != -1) {
			succesorAnterior = succesor;
			succesor = stang[succesor];
		}

		elems[curent] = elems[succesor];

		//eliminam 
		if (succesorAnterior != curent) {
			stang[succesorAnterior] = drept[succesor];
		}
		else {
			drept[curent] = drept[succesor];
		}

		curent = succesor;
		*/
		int min = minim(curent);
		elems[curent] = min;
		int succesor = drept[curent];
		int anterior = curent;
		while (stang[curent] != -1)
		{
			anterior = succesor;
			succesor = stang[succesor];
		}
		if (succesor == min)
		{
			stang[anterior] = drept[anterior];
		}
	}
	dealoca(curent);
	size--;
	return true;
}


//CF:Theta(1)
//CD:Theta(n)
//CT:O(n)
bool Multime::cauta(TComparabil elem) const {
	int pos = radacina;
	while (pos != -1)
	{
		if (elem == elems[pos])
		{
			return true;
		}
		if (rel(elem, elems[pos]))
			pos = stang[pos];
		else
			pos = drept[pos];
	}
	return false;
}

//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
int Multime::dim() const {
	return size;
}
//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
bool Multime::vida() const {
	return size==0;
}

//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
Multime::~Multime() {
	delete[]elems;
	delete[]stang;
	delete[] drept;
}
//CF:Theta(1)
//CD:Theta(h)
//CT:O(n)n-h
int Multime::diferentaMaxMin() const
{
	if (radacina == -1)
		return -1;
	int min = this->radacina;
	int max = this->radacina;
	int dif = -1;
	while (stang[min] != -1) {
		min = stang[min];
	}
	while (drept[max] != -1) {
		max = drept[max];
	}
	return elems[max]-elems[min];
}


//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}
//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
int Multime::aloca()
{
	int p = primLiber;
	primLiber = drept[primLiber];
	return p;
}
//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
void Multime::dealoca(int p)
{
	drept[p] = primLiber;
	stang[p] = -1;
	primLiber = p;
}
//CF:Theta(n)
//CD:Theta(n)
//CT:Theta(n)
void Multime::resize()
{
	TComparabil* new_elems = new TComparabil[cp * 2];
	int* new_stang = new int[2 * cp];
	int* new_drept = new int[2 * cp];
	for (int i = 0; i < cp; i++) {
		new_elems[i] = elems[i];
		new_stang[i] = stang[i];
		new_drept[i] = drept[i];
	}
	delete elems;
	delete drept;
	delete stang;
	elems = new_elems;
	stang = new_stang;
	drept = new_drept;
	for (int i = cp; i < cp * 2 - 1; i++)
		drept[i] = i + 1;
	stang[cp * 2 - 1] = -1;
	primLiber = cp;
	cp = cp * 2;
}

//CF:Theta(1)-stergem rad
//CD:Theta(n)
//CT:O(n)
/*
bool Multime::sterge_recursiv(int curent,int anterior, TComparabil e)
{
	if (curent == -1)
		return false;
	if (elems[curent] == e)
	{
		size--;
		if (stang[curent] != -1 && drept[curent] != -1) {
			int min = minim(drept[curent]);
			elems[curent] = elems[min];
			return sterge_recursiv(drept[curent], curent, elems[min]);

		}
		else if (stang[curent] == -1 && drept[curent] == -1)
		{
			if (curent == radacina)
				radacina = -1;
			else {
				if (stang[anterior] == curent)
					stang[anterior] = -1;
				else
					drept[anterior] = -1;
			}
		}
		else if (stang[curent] == -1)
		{
			if (anterior == -1)
				radacina = drept[curent];
			else if (stang[anterior] == curent)
			{
				stang[anterior] = drept[anterior];

			}
			else
				drept[anterior] = drept[curent];
		}
		else {
			if (anterior == -1)
				radacina = stang[curent];
			else if (stang[anterior] == curent)
				stang[anterior] = stang[curent];
			else
				drept[anterior] = stang[curent];
		}
		dealoca(curent);
		return true;
	}
	if (rel(e, elems[curent]))
		return sterge_recursiv(stang[curent], curent, e);
	else
		return sterge_recursiv(drept[curent], curent, e);
}
*/