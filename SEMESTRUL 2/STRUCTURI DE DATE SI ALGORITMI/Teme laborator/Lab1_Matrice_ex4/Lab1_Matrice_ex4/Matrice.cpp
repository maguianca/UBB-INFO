#include "Matrice.h"

#include <exception>

using namespace std;
//CF:Theta(1)//CD:Theta(1)//CT:Theta(1)
Matrice::Matrice(int m, int n) {
	this->nr_linii = m;
	this->nr_coloane = n;
	this->capacitate = 5;
	this->lungime = 0;
	this->Valoare = new TElem[this->capacitate]{ NULL_TELEMENT };
	this->Coloana = new int[this->capacitate] {NULL_TELEMENT};
	this->Linie = new int[this->nr_linii + 1] {NULL_TELEMENT};
}

//CF:Theta(1)//CD:Theta(1)//CT:Theta(1)
Matrice::~Matrice()
{
	delete[] this->Linie;
	delete[] this->Coloana;
	delete[] this->Valoare;
}

//CF:Theta(1)//CD:Theta(1)//CT:Theta(1)
int Matrice::nrLinii() const {
	return this->nr_linii;
}//CF:Theta(1)//CD:Theta(1)//CT:Theta(1)
int Matrice::nrColoane() const {
	return this->nr_coloane;
}

//CF:Theta(1)
//CD:Theta(n) n=this->Linie[i+1]-this->Linie[i]
//CM:Theta(n)
//CT:O(n)
TElem Matrice::element(int i, int j) const {
	if (i<0 || i>this->nr_linii || j < 0 || j > this->nr_coloane) {
		throw std::exception();
	}
	int st = this->Linie[i];
	int dr = this->Linie[i + 1];
	while (st < dr)
	{
		if (this->Coloana[st] == j)
		{
			return this->Valoare[st];
		}
		st++;
	}
	return NULL_TELEMENT;
}//CD:Theta(n)
//CF:Theta(n)
//CT:Theta(n) 
void Matrice::stergere(int poz, int j)
{
	for (int index = poz; index < this->lungime - 1; index++)
	{
		this->Coloana[index] = this->Coloana[index + 1];
		this->Valoare[index] = this->Valoare[index + 1];
	}
	for (int index = j + 1; index < this->nr_linii + 1; index++)
		this->Linie[index]--;
	this->lungime--;
}

//CF:Theta(n)
//CM:Theta(n)
//CT:Theta(n)// n-nr de elemente din matrice
void Matrice::resize()
{
	auto new_Valoare = new TElem[2 * this->capacitate];
	auto new_Coloana = new TElem[2 * this->capacitate];
	for (int i = 0; i < this->lungime; i++)
	{
		new_Coloana[i] = this->Coloana[i];
		new_Valoare[i] = this->Valoare[i];
	}
	delete[] this->Valoare;
	delete[] this->Coloana;
	this->Valoare = new_Valoare;
	this->Coloana = new_Coloana;
	this->capacitate = this->capacitate * 2;
}

//CD:Theta(n)
//CF:Theta(n)
//CT:Theta(n)
void Matrice::adaugare(int poz, int i, int j, TElem e)
{
	if (this->lungime == this->capacitate) {
		this->resize();
	}
	this->lungime++;
	for (int index = this->lungime - 1; index > poz; index--)
	{
		this->Coloana[index] = this->Coloana[index - 1];
		this->Valoare[index] = this->Valoare[index - 1];
	}
	for (int index = i + 1; index < this->nr_linii + 1; index++)
		this->Linie[index]++;
	this->Coloana[poz] = j;
	this->Valoare[poz] = e;
}

//CF:Theta(1)
//CD:Theta(n)-     n=this->Linie[i+1]-this->Linie[i]
//CM:Theta(n)
//CT:O(n)
TElem Matrice::modifica(int i, int j, TElem e) {

	if (i<0 || i>this->nr_linii || j < 0 || j > this->nr_coloane) {
		throw std::exception();
	}
	int st = this->Linie[i];
	int dr = this->Linie[i + 1];
	TElem obiect = NULL_TELEMENT;
	while (st < dr)
	{
		if (this->Coloana[st] == j)
		{
			obiect = this->Valoare[st];
			if (e != NULL_TELEMENT)
				this->Valoare[st] = e;
			else
				this->stergere(st, i);
			return obiect;
		}
		if (this->Coloana[st] > j)
		{
			obiect = this->Valoare[st];
			this->adaugare(st, i, j, e);
			return obiect;
		}
		st++;
	}
	this->adaugare(st, i, j, e);
	return NULL_TELEMENT;

}std::pair<int, int> Matrice::position(TElem e)const {
	pair<int, int> pozitie;
	pozitie.first = -1;
	pozitie.second = -1;
	for (int i = 0; i < this->lungime; i++) {
		if (Valoare[i] == e) {
			pozitie.second = Coloana[i];
			for (int j = 0; j <=this->nr_linii; j++)
				if (Linie[j] <= i)
				{
					pozitie.first = j;
				}

		}
	}
	return pozitie;
}
//CF:Theta(n)
//CD:Theta(n^2) (lungime-1)*nr_linii
//CT:O(n^2)



