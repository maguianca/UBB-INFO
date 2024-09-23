#pragma once
#pragma once
//#include"domeniu.h"
#define INITIAL_CAPACITY 5
template <typename ElementT>
class IteratorVectorT;

template <typename ElementT>
class VectD
{
public:
	VectD();

	VectD(const VectD& ot);

	~VectD();

	VectD& operator=(const VectD& ot);

	VectD(VectD&& ot);

	VectD& operator=(VectD&& ot);


	void add(const ElementT& el);
	void set(int poz, const ElementT& el);
	void sters();
	ElementT& get(int poz) const;


	int size() const noexcept;

	friend class IteratorVectorT<ElementT>;

	IteratorVectorT<ElementT>begin();
	IteratorVectorT<ElementT>end();


private:
	int lg;
	int cap;
	ElementT* elems;

	void ensureCapacity();
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
	IteratorVectorT(const VectD<ElementT>& v) noexcept;
	IteratorVectorT(const VectD<ElementT>& v, int poz)noexcept;
	bool valid()const;
	ElementT& element() const;
	void next();
	ElementT& operator*();
	IteratorVectorT& operator++();
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




