#include"UI.h"
#include<iostream>
using namespace std;
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
    catch (ValException& ex) {
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
    catch (ValException& ex) {
        cout << ex.get_mesaj();
    }
}

void UI::afisareUI()const {
    const vector<Turism>& listaTurism = service.get_all();

    cout << "OFERTE:\n";
    for (const Turism& l : listaTurism)
        cout << "DENUMIRE:" << l.get_denumire() << "\tDESTINATIE: " << l.get_destinatie() << "\tTIP: " << l.get_tip() << "\tPRET: " << l.get_pret() << " euro\n";
    /*
    for (const auto& oferta : oferte) {
        cout << "DENUMIRE:" << oferta.get_denumire() << "\tDESTINATIE: " << oferta.get_destinatie() << "\tTIP: " << oferta.get_tip() << "\tPRET: " << oferta.get_pret() << " euro\n";
    }*/
}
void UI::afisareUI_cos()const {
    const vector<Turism>& listaTurism = service.getAllCos();

    cout << "OFERTE:\n";
    for (const Turism& l : listaTurism)
        cout << "DENUMIRE:" << l.get_denumire() << "\tDESTINATIE: " << l.get_destinatie() << "\tTIP: " << l.get_tip() << "\tPRET: " << l.get_pret() << " euro\n";
    /*
    for (const auto& oferta : oferte) {
        cout << "DENUMIRE:" << oferta.get_denumire() << "\tDESTINATIE: " << oferta.get_destinatie() << "\tTIP: " << oferta.get_tip() << "\tPRET: " << oferta.get_pret() << " euro\n";
    }*/
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
    catch (ValException& ex) {
        cout << ex.get_mesaj();
    }
}
void UI::filtrare_destinatieUI()
{
    cout << "FILTRARE DESTINATIE\n";
    string destinatie;
    cout << "Destinatia: ";
    cin >> destinatie;
    cout << "OFERTE:\n";
    for (const Turism& l : service.filtrare_destinatie(destinatie))
        cout << "DENUMIRE:" << l.get_denumire() << "\tDESTINATIE: " << l.get_destinatie() << "\tTIP: " << l.get_tip() << "\tPRET: " << l.get_pret() << " euro\n";
    //afisareUI(service.filtrare_destinatie(destinatie));
}
void UI::filtrare_pretUI()
{
    cout << "FILTRARE PRET\n";
    double pret;
    cout << "Pret: ";
    cin >> pret;
    for (const Turism& l : service.filtrare_pret(pret))
        cout << "DENUMIRE:" << l.get_denumire() << "\tDESTINATIE: " << l.get_destinatie() << "\tTIP: " << l.get_tip() << "\tPRET: " << l.get_pret() << " euro\n";
    //afisareUI(service.filtrare_pret(pret));
}
void UI::sortare_destinatieUI()
{
    cout << "SORTARE DESTINATIE\n";
    for (const Turism& l : service.sortare_destinatie())
        cout << "DENUMIRE:" << l.get_denumire() << "\tDESTINATIE: " << l.get_destinatie() << "\tTIP: " << l.get_tip() << "\tPRET: " << l.get_pret() << " euro\n";
    //afisareUI(service.sortare(sort_destinatie));
}
void UI::sortare_denumireUI()
{
    cout << "SORTARE DESTINATIE\n";
    for (const Turism& l : service.sortare_denumire())
        cout << "DENUMIRE:" << l.get_denumire() << "\tDESTINATIE: " << l.get_destinatie() << "\tTIP: " << l.get_tip() << "\tPRET: " << l.get_pret() << " euro\n";
    //afisareUI(service.sortare(sort_denumire));
}
void UI::sortare_tip_pretUI()
{

    cout << "SORTARE TIP SI PRET \n";
    for (const Turism& l : service.sortare_tip_pret())
        cout << "DENUMIRE:" << l.get_denumire() << "\tDESTINATIE: " << l.get_destinatie() << "\tTIP: " << l.get_tip() << "\tPRET: " << l.get_pret() << " euro\n";
    //afisareUI(service.sortare(sort_tip_pret));
}
void UI::modificareUI() {
    cout << "MODIFICARE OFERTA\n";
    string denumire, destinatie, tip_nou, tip;
    float pret_nou, pret;
    cout << "Denumirea: ";
    cin >> denumire;
    cout << "Destinatia: ";
    cin >> destinatie;
    cout << "Tipul:";
    cin >> tip;
    cout << "Pret:";
    cin >> pret;
    cout << "Introduceti datele noi: \n";
    cout << "Tipul nou:";
    cin >> tip_nou;
    cout << "Pret nou:";
    cin >> pret_nou;
    try {
        service.modifica(denumire, destinatie, tip, pret, tip_nou, pret_nou);
        cout << "Modificare efectuata cu succes\n";
    }
    catch (RepoException& ex) {
        cout << ex.get_mesaj();
    }
    catch (ValException& ex) {
        cout << ex.get_mesaj();
    }
}
void UI::cosAdaugaUI() {
    string denumire, destinatie, tip;
    double pret;
    cout << "Denumirea: ";
    cin >> denumire;
    cout << "Destinatia: ";
    cin >> destinatie;
    cout << "Tipul: ";
    cin >> tip;
    cout << "Pretul: ";
    cin >> pret;
    try {
        service.cosAdauga(denumire, destinatie, tip, pret);
        cout << "Oferta s-a adaugat in Wishlist\n";
    }
    catch (RepoException& ex) {
        cout << ex.get_mesaj();
    }
    catch (ValException& ex) {
        cout << ex.get_mesaj();
    }
}

void UI::cosAdaugaRandomUI() {
    int numar;
    char str[101];
    cout << "Cate oferte random vreti in WISHLIST: ";
    cin >> str;
    numar = stoi(str);
    if (!(numar < 0 || strlen(str) > 10)) {
        try {
            int numar_oferte = service.cosAdaugaRandom(numar);
            cout << "S-au adaugat " << numar_oferte << " oferte random in WISHLIST" << endl;
        }
        catch (RepoException& ex) {
            cout << ex.get_mesaj();
        }
        catch (ValException& ex) {
            cout << ex.get_mesaj();
        }
    }
    else cout << "Numarul este invalid!" << endl;
}

void UI::cosStergeUI() {
    service.cosSterge();
    cout << "S-au sters toate ofertele din WISHLIST!" << endl;
}
void UI::raport_UI() {
    cout << "Raport privind destinatiile" << endl;
    auto map = service.raport();
    for (const auto& pereche : map) {
        cout << pereche.first << ": " << pereche.second << " oferte" << endl;
    }
}
void UI::cosExportUI()
{
    string filename;
    cout << "Introduceti numele fisierului in care vreti sa salvati wishlist-ul (.csv sau .html): " << endl;
    cin >> filename;
    string referinta = "C:\\Programare orientata obiect\\Qt Laborator 10-11\\Qt Laborator 10-11\\wishlist\\";
    service.cosExport(referinta.append(filename));
}
void UI::Meniu() {
    while (true) {
        cout << "WISHLIST" << endl;
        cout << "Exista " << service.getAllCos().size() << " oferte in wishlist.\n";
        cout << "---\t---\tMENIU WISHLIST\t---\t---" << endl;
        cout
            << "1. Adaugare oferta in wishlist\n2. Adaugare oferte random in wishlist\n3. Goleste wishlist\n4. Afisare wishlist\n5. Exporta Wishlish\n6. Iesire\n---\t---\t---\n";
        int optiune;
        cout << "Optiunea: ";
        cin >> optiune;
        try {
            switch (optiune) {
            case 1:
                cosAdaugaUI();
                break;
            case 2:
                cosAdaugaRandomUI();
                break;
            case 3:
                cosStergeUI();
                break;
            case 4:
                //afisareUI_cos(service.getAllCos());
                afisareUI_cos();
                break;
            case 5:
                cosExportUI();
                break;
            case 6:
                cout << "Iesire din WISHLIST";
                return;
            default:
                cout << "Comanda invalida!";
            }
        }
        catch (RepoException& ex) {
            cout << ex.get_mesaj() << endl;
        }
    }
}

void UI::run() {
    while (true) {
        cout << "---\tMENIU\t---\n---\t---\t---\n";
        cout << "1. Adaugare\n2. Afisare oferte\n3. Modifica tipul si pretul unei oferte\n4. Stergere\n5. Cautare oferta\n6. Filtrare dupa destinatie\n7. Filtrare dupa pretul maxim\n8. Sortare dupa denumire\n9. Sortare dupa destinatie\n10. Sortare dupa tip+pret\n11. WISHLIST\n12. Raport destinatii\n13. Undo\n0. Exit\n---\t---\t---\n";
        int optiune;
        cout << "Optiunea: ";
        cin >> optiune;
        try {
            switch (optiune) {
            case 1:
                adaugaUI();
                break;
            case 2:
                //afisareUI(service.get_all());
                afisareUI();
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
            case 11:
                Meniu();
                break;
            case 12:
                raport_UI();
                break;
            case 13:
                try {
                    service.undo();
                    cout << "S-a facut undo-ul" << endl;
                }
                catch (RepoException ex)
                {
                    cout << ex.get_mesaj() << "\n";
                }
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
        catch (ValException& ex) {
            cout << ex.get_mesaj();
        }
    }

}