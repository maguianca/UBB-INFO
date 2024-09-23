#include "validator.h"
#include"domeniu.h"
void Validator::valideaza(const Produs& p)
{
	string error = "";
	vector<Produs>pr = repo.get_all();
	auto f = find_if(pr.begin(), pr.end(), [&](const Produs& o) {return o.get_id() == p.get_id(); });
	if (f != pr.end())
		error += "id existent ";
	if (p.get_nume() == "")
		error += "nume invalid ";
	if (p.get_tip() == "")
		error += "tip invalid ";
	if (p.get_pret() > 100.0 || p.get_pret() < 1.0)
		error += "pret invalid ";
	if (error != "")
		throw::ValException(error);
}
