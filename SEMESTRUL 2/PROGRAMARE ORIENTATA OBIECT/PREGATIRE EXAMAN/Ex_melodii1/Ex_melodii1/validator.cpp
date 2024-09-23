#include "validator.h"

void Validator::valideaza(const Melodie& m)
{
	string eroare = "";
	if (m.get_artist() == "")
		eroare += "artist invalid";
	if (m.get_titlu() == "")
		eroare += "titlu invalid";
	if (m.get_rank()<0 || m.get_rank()>10)
		eroare += "rank invalid";
	if(eroare!="")
		throw ValException(eroare);
}
