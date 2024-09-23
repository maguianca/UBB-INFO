#include"domeniu.h"
#include"validator.h"
#include<string.h>
#include<assert.h>
#include <cctype> 
void Validator::valideaza_obiect(const Turism& o) {
	if (o.get_denumire() == "")
		throw ValException("Denumirea este incorecta!\n");
	if (o.get_tip() == "")
		throw ValException("Tipul este incorect!\n");
	if (o.get_pret() <= 0)
		throw ValException("Pretul este incorect!\n");
	if (o.get_destinatie() == "")
		throw ValException("Destinatia este incorecta!\n");
	if (contine_numere(o.get_destinatie()))
		throw ValException("Destinatia nu poate contine numere!\n");

}
bool Validator::contine_numere(const string& s) {
	for (char c : s) {
		if (std::isdigit(c)) {
			return true;
		}
	}
	return false;
}
string ValException::get_mesaj() {
	return msg;
}
