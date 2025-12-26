#include<iostream>
#include "IteratorColectie.h"
#include "Colectie.h"

//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	this->curent = this->col.prim;
	this->frecv = 0;
	//this->frecv = this->col.prim->element().frecventa;
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
TElem IteratorColectie::frecventa() const {
	if (this->valid())
		return curent->element().frecventa;
	throw std::exception();
}
//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
void IteratorColectie::urmator() {
	if (this->curent == this->col.prim &&  this->valid()) {
		frecv = this->curent->element().frecventa;
	}
	if (this->valid()) {
		if (frecv > 1) { 
			frecv--;
		}
		else {
			this->curent = this->curent->urmator(); 
			if (this->curent != nullptr) { 
				frecv = this->curent->element().frecventa; 
			}
		}
	}
	else {
		throw std::exception();
	}
}
//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
void IteratorColectie::prim() {
	this->curent =this-> col.prim;
	this->frecv = this->curent->element().frecventa;
	
}
