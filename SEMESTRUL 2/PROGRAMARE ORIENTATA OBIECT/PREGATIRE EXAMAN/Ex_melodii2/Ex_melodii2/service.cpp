#include "service.h"

void Service::adauga(string titlu, string artist, string gen)
{
	int id = ret_id();
	Melodie m{ id,titlu,artist,gen };
	repo.adauga(m);
}

vector<Melodie> Service::sorteaza()
{
	vector<Melodie>rez{ repo.get_all() };
	sort(rez.begin(), rez.end(), [](const Melodie& m1, const Melodie& m2) {
		return m1.get_artist() < m2.get_artist(); });
	return rez;
}

int Service::artist(string artist)
{
	int count = 0;
	for (const auto& l : repo.get_all())
	{
		if (l.get_artist() == artist)
			count++;
	}
	return count;
}

int Service::gen(string gen)
{
	int count = 0;
	for (const auto& l : repo.get_all())
	{
		if (l.get_gen() == gen)
			count++;
	}
	return count;
}

int Service::ret_id()
{
	vector<Melodie>rez{ repo.get_all() };
	sort(rez.begin(), rez.end(), [](const Melodie& m1, const Melodie& m2) {
		return m1.get_id() < m2.get_id(); });
	int id = rez[rez.size() - 1].get_id()+1;
	return id;
}

void Service::sterge(int id)
{
	repo.sterge(id);
}
