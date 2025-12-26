#include "service.h"

vector<elev> Service::sortare_clasa()
{
	vector<elev>v{ repo.get_all() };
	sort(v.begin(), v.end(), s_clasa);
	return v;
}

vector<elev> Service::sortare_medie()
{
	vector<elev>v{ repo.get_all() };
	sort(v.begin(), v.end(), s_medie);
	return v;
}

vector<elev> Service::sortare_nume()
{
	vector<elev>v{ repo.get_all() };
	sort(v.begin(), v.end(), s_nume);
	return v;
}
void Service::stergere(int matricol)
{
	return repo.stergere(matricol);
}
elev& Service::cauta(string text)
{
	return repo.cauta(text);
}
bool s_nume(elev& a, elev& b)
{
	return a.get_nume() < b.get_nume();
}
bool s_medie(elev& a, elev& b)
{
	return a.get_medie() < b.get_medie();
}
bool s_clasa(elev& a, elev& b)
{
	return a.get_clasa() < b.get_clasa();
}