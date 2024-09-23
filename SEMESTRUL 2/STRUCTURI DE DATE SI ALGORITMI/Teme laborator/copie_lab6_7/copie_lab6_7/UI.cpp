#include"UI.h"
#include<iostream>
using std::cin;
using std::cout;
void UI::adaugaUI() {
    cout << "ADAUGARE OFERTA\n";
    string denumire, destinatie, tip;
    float pret;
    cout << "Denumirea: ";
    cin >> denumire;
    cout << "Destinatia: ";
    cin >> destinatie;
    cout << "Tipul: ";
    cin >> tip;
    cout << "Pretul: ";
    cin >> pret;
    try {
        service.adauga(denumire, destinatie, tip, pret);
        cout << "Oferta adaugata\n";
    }
    catch (RepoException& ex) {
        cout << ex.get_mesaj();
    }
}

void UI::cautareUI() {
    cout << "CAUTARE OFERTA\n";
    string denumire, destinatie, tip;
    float pret;
    cout << "Denumirea: ";
    cin >> denumire;
    cout << "Destinatia: ";
    cin >> destinatie;
    cout << "Tipul: ";
    cin >> tip;
    cout << "Pretul: ";
    cin >> pret;
    try {
        service.cautare(denumire, destinatie, tip, pret);
        cout << "Oferta este inca valabila\n";
    }
    catch (RepoException& ex) {
        cout << ex.get_mesaj();
    }
}

void UI::afisareUI(const vector<Turism>& oferte) {
    cout << "OFERTE:\n";
    for (const auto& oferta : oferte) {
        cout << "DENUMIRE:" << oferta.get_denumire() << "\tDESTINATIE: " << oferta.get_destinatie() << "\tTIP: " << oferta.get_tip() << "\tPRET: " << oferta.get_pret() << " euro\n";
    }
}
void UI::stergereUI() {
    cout << "STERGERE OFERTA\n";
    string denumire, destinatie, tip;
    float pret;
    cout << "Denumirea: ";
    cin >> denumire;
    cout << "Destinatia: ";
    cin >> destinatie;
    cout << "Tipul: ";
    cin >> tip;
    cout << "Pretul: ";
    cin >> pret;
    try {
        service.stergere(denumire, destinatie, tip, pret);
        cout << "Oferta stearsa\n";
    }
    catch (RepoException& ex) {
        cout << ex.get_mesaj();
    }
}
void UI::filtrare_destinatieUI()
{
    cout << "FILTRARE DESTINATIE\n";
    string destinatie;
    cout << "Destinatia: ";
    cin >> destinatie;
    afisareUI(service.filtrare_destinatie(destinatie));
}
void UI::filtrare_pretUI()
{
    cout << "FILTRARE PRET\n";
    double pret;
    cout << "Pret: ";
    cin >> pret;
    afisareUI(service.filtrare_pret(pret));
}
int sort_denumire(const Turism& o1, const Turism& o2) {
    return o1.get_denumire() > o2.get_denumire();
}

int sort_destinatie(const Turism& o1, const Turism& o2) {
    return o1.get_destinatie() > o2.get_destinatie();
}
int sort_tip_pret(const Turism& o1, const Turism& o2) {
    if (o1.get_tip() == o2.get_tip()) {
        return o1.get_pret() > o2.get_pret();
    }
    return o1.get_tip() > o2.get_tip();
}
void UI::sortare_destinatieUI()
{
    cout << "SORTARE DESTINATIE\n";
    afisareUI(service.sortare(sort_destinatie));
}
void UI::sortare_denumireUI()
{
    cout << "SORTARE DESTINATIE\n";
    afisareUI(service.sortare(sort_denumire));
}
void UI::sortare_tip_pretUI()
{

    cout << "SORTARE TIP SI PRET \n";
    afisareUI(service.sortare(sort_tip_pret));
}
void UI::modificareUI() {
    cout << "MODIFICARE OFERTA\n";
    string denumire, destinatie, tip_nou;
    float pret_nou;
    cout << "Denumirea: ";
    cin >> denumire;
    cout << "Destinatia: ";
    cin >> destinatie;
    cout << "Introduceti datele noi: \n";
    cout << "Tipul nou:";
    cin >> tip_nou;
    cout << "Pret nou:";
    cin >> pret_nou;
    try {
        service.modifica(denumire, destinatie,tip_nou, pret_nou);
        cout << "Modificare efectuata cu succes\n";
    }
    catch (RepoException& ex) {
        cout << ex.get_mesaj();
    }
}
void UI::run() {
    while (true) {
        cout << "---\tMENIU\t---\n---\t---\t---\n";
        cout << "1. Adaugare\n2. Afisare oferte\n3. Modifica tipul si pretul unei oferte\n4. Stergere\n5. Cautare oferta\n6. Filtrare dupa destinatie\n7. Filtrare dupa pretul maxim\n8. Sortare dupa denumire\n9. Sortare dupa destinatie\n10. Sortare dupa tip+pret\n0. Exit\n---\t---\t---\n";
        int optiune;
        cout << "Optiunea: ";
        cin >> optiune;
        try {
            switch (optiune) {
            case 1:
                adaugaUI();
                break;
            case 2:
                afisareUI(service.get_all());
                break;
            case 3:
                modificareUI();
                break;
            case 4:
                stergereUI();
                break;
            case 5:
                cautareUI();
                break;
            case 6:
                filtrare_destinatieUI();
                break;
            case 7:
                filtrare_pretUI();
                break;
            case 8:
                sortare_denumireUI();
                break;
            case 9:
                sortare_destinatieUI();
                break;
            case 10:
                sortare_tip_pretUI();
                break;
            case 0:
                cout << "Aplicatie terminata";
                return;
            default:
                cout << "Optiune invalida!Introduceti din nou.\n";
            }
        }
        catch (RepoException& ex) {
            cout << ex.get_mesaj();
        }
    }
}