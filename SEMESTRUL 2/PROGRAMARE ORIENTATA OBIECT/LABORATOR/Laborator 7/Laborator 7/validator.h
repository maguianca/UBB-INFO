
class ValException {
	string msg;
public:
	ValException(string m) :msg{ m } {

	}
	string get_mesaj();
};
class Validator {
public:
	bool contine_numere(const string& s);
	void valideaza_obiect(const Turism& oferta);
};
