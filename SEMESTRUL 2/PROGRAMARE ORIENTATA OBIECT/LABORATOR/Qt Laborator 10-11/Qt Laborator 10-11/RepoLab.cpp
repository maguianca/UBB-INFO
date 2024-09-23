#include <algorithm>
#include "repo.h"

void RepoLab::random()const {
	double random = ((double)rand() / (RAND_MAX));
	//random = random * 100;
	//std::cout << "probabilitatea: " << random << "\n";
	if (random > probabilitatea)
	{
		random = random * 100;
		std::cout << "probabilitatea: " << random << "\n";
		throw(RepoException("Nu se poate executa functia de random!"));
	}
}
void RepoLab::set_probabilitatea(double pr)
{
	probabilitatea = pr;
}
bool RepoLab::exist(const Turism& oferta)
{
	random();
	for (auto& of : oferte)
	{
		if (of.second.get_denumire() == oferta.get_denumire() && of.second.get_destinatie() == oferta.get_destinatie())
		{
			return true;
		}
	}
	return false;
}
void RepoLab::store(const Turism& oferta)
{
	random();
	if (exist(oferta))
		throw RepoException("Ofera deja exista!");
	int i = int(oferte.size());
	oferte.insert(std::make_pair(i, oferta));
}
void RepoLab::stergere(const Turism& oferta)
{
	random();
	int i = 0;
	while (i < oferte.size() && oferte.at(i).get_denumire() != oferta.get_denumire()
		&& oferte.at(i).get_destinatie() != oferta.get_destinatie())
	{
		i++;
	}
	if (i > oferte.size())throw RepoException("Oferta nu exista");
	for (int j = i; j < oferte.size() - 1; j++)
		oferte.at(j) = oferte.at(j + 1);
	oferte.erase((int)oferte.size() - 1);
}
const Turism& RepoLab::cauta(const Turism& oferta)
{
	random();
	auto it = find_if(oferte.begin(), oferte.end(), [=](const std::pair<int, Turism>o) {
		return o.second.get_denumire() == oferta.get_denumire() && o.second.get_destinatie() == oferta.get_destinatie() &&
			o.second.get_tip() == oferta.get_tip() && o.second.get_pret() == oferta.get_pret();
		});
	if (it == oferte.end())
		throw RepoException("Oferta nu exista!");
	return (*it).second;
}
//vector<Turism>toate_ofertele;
const vector<Turism>& RepoLab::get_all()
{
	//toate_ofertele = std::make_unique<std::vector<Turism>>();
	random();
	toate_ofertele.clear();
	for (auto& o : oferte)
	{
		toate_ofertele.push_back(o.second);
	}
	return toate_ofertele;
}