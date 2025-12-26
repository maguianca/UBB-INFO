/*#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

class Sejur {
protected:
    char destinatie[20];
    int pret_calatorie;
    int pret_cazare;

public:
    Sejur(const char* s, int a, int b) {
        strncpy(destinatie, s, 19);
        destinatie[19] = '\0';
        pret_calatorie = a;
        pret_cazare = b;
    }

    Sejur() {
        strcpy(destinatie, "necunoscut");
        pret_calatorie = 0;
        pret_cazare = 0;
    }

    char* getDestinatie() {
        return destinatie;
    }

    int getPretCalatorie() {
        return pret_calatorie;
    }

    int getPretCazare() {
        return pret_cazare;
    }

    virtual int pretTotal() {
        return pret_calatorie + pret_cazare;
    }
};

class Concediu : public Sejur {
    int pret_muzee;

public:
    Concediu(const char* n, int a, int b, int p) : Sejur(n, a, b), pret_muzee(p) {}

    Concediu() {
        pret_muzee = 0;
    }

    int pretMuzee() const {
        return pret_muzee;
    }

    void set_pretMuzee(int p) {
        pret_muzee = p;
    }

    int pretTotal() override {
        return Sejur::pretTotal() + pret_muzee;
    }

    friend istream& operator>>(istream& stream, Concediu& ob);
    friend ostream& operator<<(ostream& stream, const Concediu& ob);
};

istream& operator>>(istream& stream, Concediu& ob) {
    stream >> ob.destinatie >> ob.pret_calatorie >> ob.pret_cazare;
    return stream;
}

ostream& operator<<(ostream& stream, const Concediu& ob) {
    stream << "Destinatie: " << ob.destinatie
        << ", Pret Calatorie: " << ob.pret_calatorie
        << ", Pret Cazare: " << ob.pret_cazare
        << ", Pret Muzee: " << ob.pret_muzee << endl;
    return stream;
}

int main() {
    const int n = 4;
    Concediu tab[n];

    for (int i = 0; i < n; i++) {
        cin >> tab[i];
        tab[i].set_pretMuzee(2);  // Setting pret_muzee to 2
    }

    Concediu* p;
    for (int i = 0; i < n; i++) {
        p = &tab[i]; // Address of each element
        cout << "Destinatie: " << p->getDestinatie()
            << ", Pret Calatorie: " << p->getPretCalatorie()
            << ", Pret Cazare: " << p->getPretCazare()
            << ", Pret Muzee: " << tab[i].pretMuzee() << endl;
    }

    int total_pret = 0;
    for (int i = 0; i < n; i++) {
        total_pret += tab[i].pretTotal();
    }
    cout << "\nPret Total: " << total_pret << endl;

    return 0;
}
*/