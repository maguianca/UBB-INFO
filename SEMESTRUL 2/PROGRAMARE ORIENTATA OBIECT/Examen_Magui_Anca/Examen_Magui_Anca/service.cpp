#include "service.h"
#include<algorithm>
vector<Utilaj> Service::sortare()
{
	vector<Utilaj>rez{ repo.get_all() };
	sort(rez.begin(), rez.end(), [](const Utilaj& o1, const Utilaj& o2) { if(o1.get_tip()!=o2.get_tip()) return o1.get_tip() < o2.get_tip();
	else return o1.get_denumire() < o2.get_denumire(); });
	return rez;

}

void Service::sterge(int id)
{
	repo.sterge(id);
}

void Service::modifica(int id, string denumire, string tip, int cilindri)
{
	Utilaj u(id, denumire, tip, cilindri);
	repo.modifica(u);
}

int Service::tip(string text)
{
	int count = 0;
	for (const auto& l : repo.get_all())
	{
		if (l.get_tip() == text)
			count++;
	}
	return count;
}

int Service::nr_cilindri(int x)
{
	int count = 0;
	for (const auto& l : repo.get_all())
	{
		if (l.get_cilindri() == x)
			count++;
	}
	return count;

}
