#include<iostream>
#include "IteratorColectie.h"
#include "Colectie.h"

//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	this->curent = this->col.prim;
}
//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
TElem IteratorColectie::element() const {
	if (this->valid())
		return curent->element().valoare;
	throw std::exception();
}
//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
bool IteratorColectie::valid() const {
	return curent != nullptr;
}
//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
void IteratorColectie::urmator() {
	if (this->valid())
		this->curent = this->curent->urmator();
	else {
		throw std::exception();
	}
}
//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
void IteratorColectie::prim() {
	this->curent = this->col.prim;

}
