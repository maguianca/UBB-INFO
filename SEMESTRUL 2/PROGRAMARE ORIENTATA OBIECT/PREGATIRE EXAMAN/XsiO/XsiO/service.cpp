#include "service.h"
#include<Qdebug>
#include<algorithm>
void Service::adauga(const int id, const int dim, string& joc, string& jucator,const string& stare)
{
	Joc j{ id,dim,joc,jucator,stare };
	val.valideaza(j);
	repo.adauga(j);
}

void Service::modifica(const int id, const int dim, string& joc, string& jucator,const  string& stare)
{
	Joc j{ id,dim,joc,jucator,stare };
	val.valideaza(j);
	repo.modifica(j);
}

vector<Joc> Service::sorteaza()
{
	vector<Joc>rez=get_all();
	/*sort(rez.begin(), rez.end(), [&](Joc& o1, Joc& o2) {return o1.get_stare() < o2.get_stare(); });
	for (const auto& joc : rez) {
		qDebug() << "Sorted Joc:" << joc.get_id() <<joc.get_joc() <<joc.get_jucator() << joc.get_stare();
	}*/
	for(int i=0;i<rez.size()-1;i++)
		for(int j=i+1;j<rez.size();j++)
			if (rez[i].get_stare() > rez[j].get_stare()) {
				swap(rez[i], rez[j]);
			}
	qDebug() << "sortat";
	for (auto& l : rez)
		qDebug() << l.get_id() << " " << l.get_dim() << l.get_joc() << " " << l.get_jucator() << l.get_stare();
	return rez;
}

void Service::mod(int& id,  string& joc, string& jucator)
{
	notify();
	repo.mod(id, joc, jucator);
}
