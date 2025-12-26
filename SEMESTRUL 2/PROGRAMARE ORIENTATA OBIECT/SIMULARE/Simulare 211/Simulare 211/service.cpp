#include "service.h"

vector<Rochie> Service::sorteaza_marime()
{
	vector<Rochie>v{ repo.get_all() };
	sort(v.begin(), v.end(), [](const Rochie& a, const Rochie& b) {
		return a.get_marime() < b.get_marime();
		});
	return v;
}

vector<Rochie> Service::sorteaza_pret()
{
	vector<Rochie>v{ repo.get_all() };
	sort(v.begin(), v.end(), [](const Rochie& a, const Rochie& b) {
		return a.get_pret() < b.get_pret();
		});
	return v;
}

void Service::seteaza(Rochie& r,const string& text)
{
	repo.seteaza(r,text);
}

vector<Rochie> Service::filtreaza()
{
	vector<Rochie>rep{ repo.get_all() };
	vector<Rochie>fil;
	copy_if(rep.begin(), rep.end(), back_inserter(fil), [&](const Rochie& x) {
		return x.get_pret() < 1000;
		});
	return fil;
}
