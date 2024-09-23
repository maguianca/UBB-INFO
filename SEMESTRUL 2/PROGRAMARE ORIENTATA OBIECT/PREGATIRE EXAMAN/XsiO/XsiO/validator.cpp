#include "validator.h"

void Validator::valideaza(Joc& joc)
{
	string eroare = "";
	if (joc.get_id()< 0)
		eroare += "id invalid\n";
	if (joc.get_dim() !=3 && joc.get_dim() != 4 && joc.get_dim() != 5)
		eroare += "dim invalida\n";
	if (joc.get_joc().size()!=joc.get_dim()*joc.get_dim())
		eroare += "joc invalid\n";
	for (int i = 0; i < joc.get_joc().size(); i++)
		if (joc.get_joc()[i] != 'X' && joc.get_joc()[i] != 'O' && joc.get_joc()[i] != '-')
			eroare += "string din joc invalid\n";
	if (joc.get_jucator()!="X"&& joc.get_jucator() != "O")
		eroare += "jucator invalid\n";
	if (joc.get_stare() != "Terminat" && joc.get_stare() != "Neinceput" && joc.get_stare() != "Inderulare")
		eroare += "stare invalida\n";
	if (eroare != "")
		throw ValException(eroare);
}
