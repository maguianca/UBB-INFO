#include "service.h"
vector<Melodie> Service::sorteaza()
{
	vector<Melodie>rez{ repo.get_all() };
	sort(rez.begin(), rez.end(), [](const Melodie& m1, const Melodie& m2) {return m1.get_rank() < m2.get_rank(); });
	return rez;


}

void Service::modifica(int id, string titlu, string artist, int rank)
{
	Melodie m{ id,titlu,artist,rank };
	Melodie mv = repo.cauta(id);
	l_undo.push_back(std::make_unique<UndoModifica>(repo, mv,m));
	val.valideaza(m);
	repo.modifica(m);
}

void Service::sterge(int id)
{
	Melodie m = repo.cauta(id);
	l_undo.push_back(std::make_unique<UndoSterge>(repo,m));
	repo.sterge(id);
}

int Service::rank(int r)
{
	int c = 0;
	for (const auto& l : repo.get_all())
	{
		if (l.get_rank() == r)
			c++;
	}
	return c;
}

int Service::artist(string artist)
{
	int c = 0;
	for (const auto& l : repo.get_all())
	{
		if (l.get_artist() == artist)
			c++;
	}
	return c;
}

void Service::undo()
{
	if (!l_undo.empty()) {
		l_undo.back()->doUndo();
		l_undo.pop_back();
	}
	else
		throw exception("aaa");
}
