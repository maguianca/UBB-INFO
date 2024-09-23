#include "IteratorMD.h"
#include "MD.h"

using namespace std;
//CF:Theta(n)
//CD:Theta(n)
//CT:Theta(n)
IteratorMD::IteratorMD(const MD& _md) : md(_md) {
	for (int i = 0; i < md.capacitate; i++)
		if (md.elem[i].first != -1000000)
			elemente.push_back(md.elem[i]);
}
//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
TElem IteratorMD::element() const {
	if (valid())
		return elemente[curent];
	else
		throw std::exception();
}
//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
bool IteratorMD::valid() const {
	return curent<elemente.size();
}
//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
void IteratorMD::urmator() {
	if (valid())
		curent++;
	else
		throw std::exception();
}
//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
void IteratorMD::prim() {
	curent = 0;
}

