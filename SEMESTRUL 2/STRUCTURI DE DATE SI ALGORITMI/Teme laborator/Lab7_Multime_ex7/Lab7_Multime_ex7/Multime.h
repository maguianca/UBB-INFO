#pragma once
#pragma once
#include<climits>
#define NULL_TELEM -1
typedef int TElem;
typedef int TComparabil;
class IteratorMultime;

class Multime {
	friend class IteratorMultime;

private:
	int cp;
	int size;
	TComparabil* elems;
	int* stang;
	int* drept;
	int primLiber;
	int radacina;
	int aloca();
	void dealoca(int i);
	void resize();
	//void adauga_recursiv(int r,TComparabil e,int parinte);
	bool sterge_recursiv(int curent,int anterior,TComparabil e);
	//int cauta_recursiv(int r,TElem e);
	int minim(int p);
	int creeazaNod(TComparabil e);

public:
	//constructorul implicit
	Multime();

	//adauga un element in multime
	//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
	bool adauga(TComparabil elem);

	//sterge un element din multime
	//returneaza adevarat daca elementul a existat si a fost sters
	bool sterge(TComparabil e);

	//verifica daca un element se afla in multime
	bool cauta(TComparabil elem) const;


	//intoarce numarul de elemente din multime;
	int dim() const;

	//verifica daca multimea e vida;
	bool vida() const;

	//returneaza un iterator pe multime
	IteratorMultime iterator() const;

	// destructorul multimii
	~Multime();
	int diferentaMaxMin()const;
};




