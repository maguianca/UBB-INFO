#pragma once
#include"domeniu.h"
#define INITIAL_CAPACITY 5
template <typename ElementT>
class IteratorVectorT;

template <typename ElementT>
class VectD
{
public:

	//Constructor default
	VectD();
	//Constructor de copiere
	VectD(const VectD& ot);
	//Eliberam memoria
	~VectD();
	//Operator assignment
	VectD& operator=(const VectD& ot);
	///Move constructor
	VectD(VectD&& ot);
	//Move assignment
	VectD& operator=(VectD&& ot);

	//adauga un element in vector
	void add(const ElementT& el);
	//seteaza pe pozitia poz un element in vector
	void set(int poz, const ElementT& el);
	//sterge un element din lista
	void sters();
	//metoda geter returneaza elem de pe pozitia poz
	ElementT& get(int poz) const;

	//returneaza marimea vectorului
	int size() const noexcept;

	friend class IteratorVectorT<ElementT>;
	//functii care creaza iteratori
	IteratorVectorT<ElementT>begin();
	IteratorVectorT<ElementT>end();


private:
	int lg;//nr elemente
	int cap;//capacitatea
	ElementT* elems;//vectorul de elemente

	void ensureCapacity();
	//mareste capacitatea vectorului daca e necesar
};
template<typename ElementT>
void VectD<ElementT>::sters() {
	lg--;
}


template<typename ElementT>
VectD<ElementT>::VectD() :elems{ new ElementT[INITIAL_CAPACITY] }, cap{ INITIAL_CAPACITY }, lg{ 0 } {}


template<typename ElementT>
VectD<ElementT>::VectD(const VectD<ElementT>& ot) {
	elems = new ElementT[ot.cap];
	for (int i = 0; i < ot.lg; i++) {
		elems[i] = ot.elems[i];
	}
	lg = ot.lg;
	cap = ot.cap;
}

template<typename ElementT>
VectD<ElementT>& VectD<ElementT>::operator=(const VectD<ElementT>& ot) {
	if (this == &ot) {
		return *this;
	}
	delete[] elems;
	elems = new ElementT[ot.cap];

	for (int i = 0; i < ot.lg; i++) {
		elems[i] = ot.elems[i];
	}
	lg = ot.lg;
	cap = ot.cap;
	return *this;
}

template<typename ElementT>
VectD<ElementT>::~VectD() {
	delete[] elems;
}

template<typename ElementT>
VectD<ElementT>::VectD(VectD&& ot) {

	elems = ot.elems;
	lg = ot.lg;
	cap = ot.cap;

	ot.elems = nullptr;
	ot.lg = 0;
	ot.cap = 0;
}

template<typename ElementT>
VectD<ElementT>& VectD<ElementT>::operator=(VectD<ElementT>&& ot) {
	if (this == &ot) {
		return *this;
	}
	delete[] elems;

	elems = ot.elems;
	lg = ot.lg;
	cap = ot.cap;
	ot.elems = nullptr;
	ot.lg = 0;
	ot.cap = 0;
	return *this;
}

template<typename ElementT>
void VectD<ElementT>::add(const ElementT& el) {
	ensureCapacity();
	elems[lg++] = el;
}
template<typename ElementT>
ElementT& VectD<ElementT>::get(int poz) const {
	return elems[poz];
}

template<typename ElementT>
void VectD<ElementT>::set(int poz, const ElementT& el) {
	elems[poz] = el;
}

template<typename ElementT>
int VectD<ElementT>::size() const noexcept {
	return lg;
}

template<typename ElementT>
void VectD<ElementT>::ensureCapacity() {
	if (lg < cap) {
		return;
	}
	cap *= 2;
	ElementT* aux = new ElementT[cap];
	for (int i = 0; i < lg; i++) {
		aux[i] = elems[i];
	}
	delete[] elems;
	elems = aux;
}

template<typename ElementT>
IteratorVectorT<ElementT> VectD<ElementT>::begin()
{
	return IteratorVectorT<ElementT>(*this);
}

template<typename ElementT>
IteratorVectorT<ElementT> VectD<ElementT>::end()
{
	return IteratorVectorT<ElementT>(*this, lg);
}

template<typename ElementT>
class IteratorVectorT {
private:
	const VectD<ElementT>& v;
	int poz = 0;
public:
	//constructor default
	IteratorVectorT(const VectD<ElementT>& v) noexcept;
	//constructor de copiere
	IteratorVectorT(const VectD<ElementT>& v, int poz)noexcept;
	//returneaza true sau false daca iteratorul se fala pe o pozitie valida
	bool valid()const;
	//returneaza elementul
	ElementT& element() const;
	//muta iteratorul pe urmatoarea pozitie
	void next();
	ElementT& operator*();
	IteratorVectorT& operator++();
	//operator assignment
	bool operator==(const IteratorVectorT& ot)noexcept;
	bool operator!=(const IteratorVectorT& ot)noexcept;
};

template<typename ElementT>
IteratorVectorT<ElementT>::IteratorVectorT(const VectD<ElementT>& v) noexcept :v{ v } {}

template<typename ElementT>
IteratorVectorT<ElementT>::IteratorVectorT(const VectD<ElementT>& v, int poz)noexcept : v{ v }, poz{ poz } {}

template<typename ElementT>
bool IteratorVectorT<ElementT>::valid()const {
	return poz < v.lg;
}

template<typename ElementT>
ElementT& IteratorVectorT<ElementT>::element() const {
	return v.elems[poz];
}

template<typename ElementT>
void IteratorVectorT<ElementT>::next() {
	poz++;
}

template<typename ElementT>
ElementT& IteratorVectorT<ElementT>::operator*() {
	return element();
}

template<typename ElementT>
IteratorVectorT<ElementT>& IteratorVectorT<ElementT>::operator++() {
	next();
	return *this;
}

template<typename ElementT>
bool IteratorVectorT<ElementT>::operator==(const IteratorVectorT<ElementT>& ot) noexcept {
	return poz == ot.poz;
}

template<typename ElementT>
bool IteratorVectorT<ElementT>::operator!=(const IteratorVectorT<ElementT>& ot)noexcept {
	return !(*this == ot);
}




