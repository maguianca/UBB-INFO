#include "validator.h"

void Validator::validator(const Produs& p)
{
	string eroare = "";
	vector<Produs>rez{ repo.get_all() };
	auto f = find_if(rez.begin(), rez.end(), [&](const Produs& p1) {return p1.get_id() == p.get_id(); });
		if (f != rez.end())
		{
			eroare += "id existent\n";
		}
		if (p.get_nume() == " ")eroare += "nume invalid\n";
		if (p.get_tip() == " ")eroare += "tip invalid\n";
		if (p.get_pret() < 1.0 || p.get_pret() > 100.0)
			eroare += "pret invalid\n";
		if (eroare != "")
			throw ValException(eroare);
}
