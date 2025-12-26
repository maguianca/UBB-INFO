#include"service.h"
#include<QWidget>
vector<Joc> Service::sorteaza()
{
	vector<Joc>rez{ repo.get_all() };
	for (int i = 0; i < rez.size() - 1; i++)
		for (int j = i + 1; j < rez.size(); j++)
			if (rez[i].get_joc() > rez[j].get_joc()) {
				swap(rez[i], rez[j]);
			}
	//qDebug() << "sortat";
	//for (auto& l : rez)
	//	qDebug() << l.get_id() << " " << l.get_dim() << l.get_joc() << " " << l.get_jucator() << l.get_stare();
	return rez;
}
void Service::mod(int& id, string& joc, string& jucator)
{
	//notify();
	repo.mod(id, joc, jucator);
}
void Service::adauga(const int id, const int dim, string& joc, string& jucator, const string& stare)
{
	Joc j{ id,dim,joc,jucator,stare };
	val.valideaza(j);
	repo.adauga(j);
}

void Service::modifica(const int id, const int dim, string& joc, string& jucator, const  string& stare)
{
	Joc j{ id,dim,joc,jucator,stare };
	val.valideaza(j);
	repo.modifica(j);
}
void Service::notify(int id, string tabla, string jucator, string stare) {
	repo.modificaStare(id, tabla, jucator, stare);
}
