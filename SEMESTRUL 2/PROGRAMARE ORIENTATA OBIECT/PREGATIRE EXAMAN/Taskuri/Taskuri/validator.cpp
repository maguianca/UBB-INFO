#include "validator.h"

void Validator::valideaza(Task& t)
{
	string eroare = "";
	vector<Task>r = repo.get_all();
	auto f = find_if(r.begin(), r.end(), [&](const Task& o1) { return t.get_id() == o1.get_id(); });
	if (f != r.end())
		eroare += "id existent\n";
	if (t.get_descriere() == "")
		eroare += "descriere invalida\n";
	if (t.get_programatori().size() > 4 || t.get_programatori().size() < 1)
		eroare += "nr programatori invalid\n";
	if (t.get_stare() != "close" && t.get_stare() != "inprogress" && t.get_stare() != "open")
		eroare += "stare invalida";
	if (eroare != "")
		throw ValException(eroare);
}
void Validator::valideaza_stare(string text)
{
	string eroare = "";
	if (text != "close" && text!= "inprogress" && text != "open")
		eroare += "stare invalida";
	if (eroare != "")
		throw ValException(eroare);
}
