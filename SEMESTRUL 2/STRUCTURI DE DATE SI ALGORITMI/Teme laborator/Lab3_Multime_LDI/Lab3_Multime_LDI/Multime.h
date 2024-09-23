#pragma once
#pragma once

typedef int TElem;

class IteratorMultime;

typedef struct Nod {
	TElem element;
	Nod* urmator;
	Nod* anterior;
};


class Multime {
	friend class IteratorMultime;

private:
	Nod* prim;
	Nod* ultim;
	int size;

public:
	//constructorul implicit
	Multime();

	//adauga un element in multime
	//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
	bool adauga(TElem e);

	//sterge un element din multime
	//returneaza adevarat daca elementul a existat si a fost sters
	bool sterge(TElem e);

	//verifica daca un element se afla in multime
	bool cauta(TElem elem) const;

	//intoarce numarul de elemente din multime;
	int dim() const;

	//verifica daca multimea e vida;
	bool vida() const;

	//returneaza un iterator pe multime
	IteratorMultime iterator() const;

	// destructorul multimii
	~Multime();
};