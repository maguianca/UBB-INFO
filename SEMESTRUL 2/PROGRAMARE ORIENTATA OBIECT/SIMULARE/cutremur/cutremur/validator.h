#pragma once
#include "domeniu.h"
#include<exception>
using namespace std;
class ValException :public exception {
private:
	string mesaj = "";
public:
	ValException(string& mesaj) :mesaj{ mesaj } {}
	string get_mesaj() { return mesaj; }
};
class Validator {
public:
	void valideaza(Cutremur& cutremur) {
		string errors = "";
		if (cutremur.get_data() == "")
			errors += "data invalida\n";
		if (cutremur.get_locatie() == "")
			errors += "locatie invalida\n";
		if (cutremur.get_adancime() < 0)
			errors += "adancime invalida\n";
		if (cutremur.get_intensitate() < 0 || cutremur.get_intensitate() > 10)
			errors += "intensitate invalida\n";
		if (!errors.empty())
			throw::ValException(errors);
	}
};