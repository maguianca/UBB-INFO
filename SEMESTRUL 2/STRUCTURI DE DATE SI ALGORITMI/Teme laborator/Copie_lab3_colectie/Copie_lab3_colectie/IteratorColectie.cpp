#include<iostream>
#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	this->curent = this->col.prim;
}

TElem IteratorColectie::element() const {
	if (this->valid())
		return curent->element().valoare;
	throw std::exception();
}

bool IteratorColectie::valid() const {
	return curent != nullptr;
}

void IteratorColectie::urmator() {
	if (this->valid())
		this->curent = this->curent->urmator();
	else {
		throw std::exception();
	}
}

void IteratorColectie::prim() {
	this->curent = this->col.prim;

}
