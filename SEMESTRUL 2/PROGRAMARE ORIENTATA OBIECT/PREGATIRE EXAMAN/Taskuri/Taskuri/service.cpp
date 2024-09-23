#include "service.h"

vector<Task> Service::sorteaza()
{
	vector<Task>rez{ repo.get_all() };
	sort(rez.begin(), rez.end(), [](const Task& o1, const Task& o2) {return o1.get_stare() < o2.get_stare(); });
	return rez;
}

void Service::adauga(int id, string denumire, vector<string> programatori, string stare)
{
	Task t{ id,denumire,programatori,stare };
	val.valideaza(t);
	repo.adauga(t);
	notify();
}

vector<Task> Service::filtrare(const string text)
{
	vector<Task>rez;
	vector<Task>r = repo.get_all();
	copy_if(r.begin(), r.end(), back_inserter(rez), [text](const Task& t) {return t.get_programatori_string() == text; });
	return rez;
}

vector<Task> Service::stare(const string text)
{
	vector<Task>rez;
	vector<Task>r = repo.get_all();
	copy_if(r.begin(), r.end(), back_inserter(rez), [text](const Task& t) {return t.get_stare() == text; });
	return rez;
}

void Service::modifica(const int id,const string stare)
{
	val.valideaza_stare(stare);
	repo.modificare(id, stare);
	notify();
}
