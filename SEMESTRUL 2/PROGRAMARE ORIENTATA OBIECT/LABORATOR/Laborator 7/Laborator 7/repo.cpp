#include"repo.h"
#include<assert.h>
void Repo::store(const Turism& oferta)
{
		if (exist(oferta))
			throw RepoException("Oferta existenta\n");
	//vacante.push_back(oferta);
		vacante.add(oferta);
}
void Repo::stergere(const Turism& oferta) {
		int ok = 0;
		for (int i = 0; i < vacante.size(); i++) {
			if (vacante.get(i).get_destinatie() == oferta.get_destinatie() && vacante.get(i).get_denumire() == oferta.get_denumire() && vacante.get(i).get_tip() == oferta.get_tip() && vacante.get(i).get_pret() == oferta.get_pret()) {
				for (int j = i; j < vacante.size(); j++)
					vacante.set(j, vacante.get(j + 1));
				vacante.sters();
				ok = 1;
				return;}}
		if (ok == 0)
			throw RepoException("Oferta neexistenta, deci nu se poate sterge\n");

}
void Repo::modifica(const Turism& o)
{
	bool ok = false;
	for (auto& i : vacante)
		if (i.get_denumire() == o.get_denumire() && i.get_destinatie() == o.get_destinatie())
		{  
			i.set_pret(o.get_pret());
			i.set_tip(o.get_tip());
			ok = true;
			break;
		}
	if (!ok)
		throw RepoException("Nu s-a realizat nicio modificare!\n");


}
const Turism& Repo::cauta(const Turism&oferta){
	//VectD<Turism> lista = vacante;
	//vacante
	for  (auto& o : vacante ){
		if (o.get_denumire() == oferta.get_denumire() && o.get_destinatie() == oferta.get_destinatie() && o.get_tip() == oferta.get_tip() && o.get_pret() == oferta.get_pret()) {
			return o;
		}
	}
	throw RepoException("Nu exista oferta!\n");
}
bool Repo::exist(const Turism& o){
	try {
		cauta(o);
		return true;
	}
	catch (RepoException&) {
		return false;}
}
