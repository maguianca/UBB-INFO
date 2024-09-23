#pragma once
#pragma once

class ValException {
	string msg;
public:
	ValException(string m) :msg{ m } {

	}
	string get_mesaj();
};
class Validator {
public:
	bool contine_numere(const string& s);
	//testeaza daca constanta string contine cifre
	void valideaza_obiect(const Turism& oferta);
	//valideaza un obiect, verifica daca componentele unei oferte sunt valide
};
