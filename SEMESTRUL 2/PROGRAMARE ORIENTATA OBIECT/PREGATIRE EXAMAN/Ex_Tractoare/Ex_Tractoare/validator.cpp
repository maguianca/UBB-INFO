#include "validator.h"

void Validator::valideaza(const Tractor& t)
{
	string eroare = "";
	vector<Tractor>rez=repo.get_all();
	auto f = find_if(rez.begin(), rez.end(), [&](const Tractor& o) {return o.get_id() == t.get_id(); });
	if (f !=rez.end())
	{
		eroare += "id existent\n";
	}
	if (t.get_denumire() == " ")
		eroare += "denumire invalida\n";
	if (t.get_tip() == " ")
		eroare += "tip invalid\n";
	if (t.get_numar() % 2 == 1 || t.get_numar() < 2 || t.get_numar() > 16) {
		eroare += "numar invalid\n";
	}
	if (eroare != "")
		throw ValException(eroare);
}
void Validator::m_valideaza(const Tractor& t)
{
	string eroare = "";
	if (t.get_denumire() == " ")
		eroare += "denumire invalida\n";
	if (t.get_tip() == " ")
		eroare += "tip invalid\n";
	if (t.get_numar() % 2 == 1 || t.get_numar() < 2 || t.get_numar() > 16) {
		eroare += "numar invalid\n";
	}
	if (eroare != "")
		throw ValException(eroare);
}