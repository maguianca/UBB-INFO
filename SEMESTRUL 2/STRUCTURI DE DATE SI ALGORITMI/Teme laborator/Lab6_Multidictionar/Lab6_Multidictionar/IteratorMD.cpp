#include "IteratorMD.h"
#include "MD.h"

using namespace std;

IteratorMD::IteratorMD(const MD& _md) : md(_md) {
	for (int i = 0; i < md.m; i++)
		if (md.e[i].first != INIT)
			elemente.push_back(md.e[i]);
	curent = 0;
}

TElem IteratorMD::element() const {
	if (valid())
		return elemente[curent];
	else
		throw std::exception();
	
}

bool IteratorMD::valid() const {
	if (curent < elemente.size())
		return true;
	return false;
}

void IteratorMD::urmator() {
	if (valid())
		curent = curent + 1;
	else
		throw std::exception();
}

void IteratorMD::prim() {
	curent = 0;
}

