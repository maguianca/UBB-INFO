#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::cout;
using std::vector;

class Smoothy {
private:
    int pret;
public:
    Smoothy(int pret) :pret{ pret } {};
    virtual int getPret()
    {
        return pret;
    }
    virtual string descriere() = 0;

    virtual ~Smoothy() = default;
};

class BasicSmoothy :public Smoothy {
private:
    string nume;
public:
    BasicSmoothy(int pret, string name) :Smoothy(pret), nume{ name } {};
    string descriere() override {
        return nume;
    }
};

class DecoratorSmoothy :public Smoothy {
private:
    Smoothy* s;
public:
    DecoratorSmoothy(Smoothy* sm) :Smoothy(sm->getPret()), s{ sm } {};
    // vreau sa fac un smoothy s cu specificatiile smoothie-ului sm
    // pt asta, trebuie sa apelez constructorul de smoothy cu sm->pret(), iar abia dupa sa il dau ca referinta
    // mereu clasa care mosteneste va apela constructorul clasei de baza
    virtual string descriere() override {
        return s->descriere(); // metoda din clasa cealalta
        // practic nici pe asta n o s o pot construi direct
    }
    virtual ~DecoratorSmoothy() {
        delete s;
    }
};

class SmoothyCuFrisca :public DecoratorSmoothy {
public:
    SmoothyCuFrisca(Smoothy* s) : DecoratorSmoothy(s) {};
    string descriere() override {
        return DecoratorSmoothy::descriere() + " cu frisca";
    }
    int getPret() override {
        return DecoratorSmoothy::getPret() + 2;
    }

};

class SmoothyCuUmbreluta : public DecoratorSmoothy {
public:
    SmoothyCuUmbreluta(Smoothy* s) : DecoratorSmoothy(s) {};
    string descriere() override {
        return DecoratorSmoothy::descriere() + " cu umbreluta";
    }
    int getPret() override {
        return DecoratorSmoothy::getPret() + 3;
    }
};
/*
 *  Scrieți o funcție C++ care returnează o lista de smothy-uri: un smoothy de kivi cu frișcă si
umbreluță, un smoothy de căpșuni cu frișcă si un smoothy simplu de kivi. (0.5p)
3 Programul principal apelează funcția descrisa mai sus, apoi tipărește descrierea si prețul
pentru fiecare smoothy in ordine alfabetica după descriere. (0.25p)
 */

vector <Smoothy*> creeaza_lista2() {
    vector <Smoothy*> lista;
    lista.push_back(new SmoothyCuUmbreluta(new DecoratorSmoothy(new SmoothyCuFrisca(new BasicSmoothy(10, "kivi")))));
    lista.push_back(new SmoothyCuFrisca(new BasicSmoothy(10, "capsuni")));
    lista.push_back(new BasicSmoothy(10, "kivi"));
    return lista;
}

vector<Smoothy*> creeaza_lista1() {
    // atentie ca nu pot declara smoothy, ca e pur abstracta, trebuie sa fac smoothy cu frisca din basic smoothy
    vector<Smoothy*> lista;
    SmoothyCuFrisca* f = new SmoothyCuFrisca(new BasicSmoothy(10, "kivi"));
    SmoothyCuUmbreluta* u = new SmoothyCuUmbreluta(new DecoratorSmoothy(f));
    //cout<<"pret: "<<u->getPret();
    lista.push_back(u);

    SmoothyCuFrisca* c = new SmoothyCuFrisca(new BasicSmoothy(10, "capsuni"));
    lista.push_back(c);

    BasicSmoothy* b = new BasicSmoothy(10, "kivi");
    lista.push_back(b);

    return lista;
}

void distruge_lista1(vector<Smoothy*> v) {
    //ca sa dealoc memoria ocupata de elementele unui vector de employees
    for (auto& s : v) {
        delete s;
    }
}
template<typename TElem>

class Geanta {
private:
    string name;
    vector<TElem> obiecte;
public:
    Geanta(string name) : name{ name } {}

    Geanta& operator=(const TElem& other) {
        if (other != this)
        {
            name = other.name;
            obiecte = obiecte.other;
        }
        return *this;
    }
    // Correct operator+ to create and return a new object
    Geanta &operator+(const TElem& obj){
        obiecte.push_back(obj);
        return *this;
    }

    typename vector<TElem>::iterator begin() {
        return obiecte.begin();
    }

    typename vector<TElem>::iterator end() {
        return obiecte.end();
    }
};

void calatorie() {
    Geanta<string> ganta{ "Ion" };//creaza geanta pentru Ion
    ganta = ganta + string{ "haine" }; //adauga obiect in ganta
    ganta + string{ "pahar" };
    for (auto o : ganta) {//itereaza obiectele din geanta
        cout << o << "\n";
    }
}

/*
int main() {
    vector<Smoothy*> list=creeaza_lista1();
    vector<Smoothy*> list = creeaza_lista2();
    //ordonez vector dupa descriere
    std::sort(list.begin(), list.end(), [&](Smoothy* s1, Smoothy* s2) {
        return s1->descriere() < s2->descriere();
        });
    for (auto& e : list) {
        cout << e->descriere() << " " << e->getPret();
        cout << "\n";
    }
    distruge_lista1(list);
    
    calatorie();
    return 0;
}*/