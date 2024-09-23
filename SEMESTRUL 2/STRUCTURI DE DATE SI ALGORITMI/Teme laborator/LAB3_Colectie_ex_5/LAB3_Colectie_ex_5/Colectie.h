#pragma once
//Colectie.h
#include <utility>
typedef int TElem;

typedef bool (*Relatie)(TElem, TElem);
typedef bool (*Conditie)(TElem);
//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
class IteratorColectie;
class Nod;
struct Pereche {
	TElem valoare;
	int frecventa;
};
bool rel(TElem, TElem);
bool cond(TElem);
typedef Nod* PNod;

class Nod
{
public:
	friend class Colectie;
	Nod(Pereche e, PNod urm);
	Pereche element();
	PNod urmator();
private:
	Pereche e;
	PNod urm;
};



//interfata colectiei nu se modifica
class Colectie {
	friend class IteratorColectie;
private:
	int size;  // numarul de elemente distincte
	PNod prim;
	int total; //numar total de elemente
	
public:
	//constructorul implicit
	Colectie();

	//adauga un element in colectie
	void adauga(TElem e);

	//sterge o aparitie a unui element din colectie
	//returneaza adevarat daca s-a putut sterge
	bool sterge(TElem e);

	//verifica daca un element se afla in colectie
	bool cauta(TElem elem) const;

	//returneaza numar de aparitii ale unui element in colectie
	int nrAparitii(TElem elem) const;


	//intoarce numarul de elemente din colectie;
	int dim() const;

	//verifica daca colectia e vida;
	bool vida() const;

	//returneaza un iterator pe colectie
	IteratorColectie iterator() const;

	// destructorul colectiei
	~Colectie();
	//filtreaza elementele dupa o conditie
	void filtreaza();
};

