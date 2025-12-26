import Domeniu
import Business

import Repository

def undo_ui(evidenta,istoric):
    """
    functie care printeaza daca statusul listei dupa undo
    :param evidenta: lista
    :param istoric: lista
    :return: mesaj
    """
    try:
        evidenta = Repository.myundo(istoric)
        print("SUCCES:\n" +  "Undo efectuat cu succes.")
        Domeniu.afisare_lista(evidenta)
        return evidenta
    except ValueError as exc:
        print("EROARE:" + str(exc)+"va rog introduceti elemente in lista pentru alte operatii")
def meniuadaugare(evidenta,istoric):
    """
    acesta este submeniul de adaugare care se apleleaza in meniul mare
    interfata cu utlizator
    """
    i=0
    while True:
        print("Apasati tasta 1 pentru a adauga cheltuieli")
        print("Apasati tasta 2 pentru a modifica o cheltuiala")
        print("Apasati tasta 3 pentru a termina procesul de adaugare")
        user = int(input())
        if user==1:
            Repository.adaugare_cheltuiala(evidenta)
            istoric.append(Domeniu.creeaza_copie(evidenta))
        elif user==2:
            if evidenta==[]:
                print("nu sunt elemente, va rog introduceti elemente")
            else:
                index = Business.index_valid(evidenta)
                suma = Business.citire_suma()
                tip = Business.tipul_chelt()
                data = Business.citire_data()
                cheltuiala1 = Domeniu.creeaza_cheltuiala(index, suma, tip, data)
                lista = Repository.modificare_cheltuiala(evidenta, index, cheltuiala1)
                print("Lista dupa modificare este:")
                Domeniu.afisare_lista(lista)
                istoric.append(Domeniu.creeaza_copie(lista))
        elif user==3:
            break
        else :
            print("Tasta nu este valida")
    Domeniu.afisare_lista(evidenta)

def meniucautari(evidenta):
    """
    acesta functie este un submeniu de cautare care se apeleaza in meniul mare
    :param evidenta: lista
    :return:printeaza
    interfata cu utilizatorul
    """
    i=0
    while True:
        print("Apasati tasta 1 pentru a tipari toate apartamentele cu cheltuieli mai mari decat o suma data")
        print("Apasati tasta 2 pentru a tipari cheltuielile de un anumit tip")
        print("Apasati tasta 3 pentru a tipari toate cheltuielile efectuate cu o zi inainte si mai mari decta o suma")
        print("Apasati tasta 4 pentru terminarea procesului de cautare")
        user = int(input())
        if user==1:
            sc=Business.citire_suma()
            lista=Repository.cautare1(evidenta,sc)
            print("Apartamentele care au cheltuieli mai mari sunt:")
            Domeniu.afisare_lista(lista)
        elif user==2:
            sir=Business.tipul_chelt()
            print("Apartamentele care au restate la respectivul tip sunt: ")
            Domeniu.afisare_cheltuieli(Repository.cautare2(evidenta,sir))
            #Repository.cautare2(evidenta,sir)
        elif user==3:
            data=Business.citire_data()
            suma=Business.citire_suma()
            lista=Repository.cautare3(evidenta,data,suma)
            print("Apartamentele care au efectuat cheltuielile in data de",data,"si au valoarea",suma,"sunt:")
            Domeniu.afisare_lista(lista)
        elif user==4:
            break
        else :
            print("Tasta nu este valida")
def meniurapoarte(evidenta):
    """
        acesta functie este un submeniu de rapoarte care se apeleaza in meniul mare
        :param evidenta: lista
        :return:printeaza
        interfata cu utilizatorul
        """
    i=0
    sir=0
    while True:
        print("Apasati tasta 1 pentru a tipari suma totala pentru un tip de cheltuiala")
        print("Apasati tasta 2 pentru a tipari toate apartamentele sortate dupa un tip de cheltuiala")
        print("Apasati tasta 3 pentru a tipari totalul de cheltuieli pentru un apartament")
        print("Apasati tasta 4 pentru terminarea procesului de cautare")
        user = int(input())
        if user==1:
            sir=Business.tipul_chelt()
            print("Suma totala pentru tipul respectiv de cheltuiala este: ",Repository.rap1(evidenta,sir))
        elif user==2:
            sir=Business.tipul_chelt()
            print("Apartamentele sortate dupa",sir,"sunt:")
            Domeniu.afisare_lista(Repository.rap2(evidenta,sir))
        elif user==3:
            nr = Business.citire_nr_ap()
            print("Apartamentul", nr, "are de platit:", Repository.rap3(evidenta, nr))
        elif user==4:
            break
        else :
            print("Tasta nu este valida")
def meniufiltru(evidenta):
    """
    aceasta functie este submeniu de filtrare care se apeleaza in functie de meniu principal
    :param evidenta: lista
    :return: printeaza
    """
    i=0
    while True:
        print("Apasati tasta 1 pentru a elimina toate cheltuielile de un anumit tip")
        print("Apasati tasta 2 pentru a elimina toate cheltuielile mai mici de o suma data")
        print("Apasati tasta 3 pentru a termina procesul de filtrare")
        user = int(input())
        if user==1:
            sir = Business.tipul_chelt()
            lista=Repository.eliminare1(evidenta,sir)
            print("Lista dupa eliminare:")
            Domeniu.afisare_lista(lista)
        elif user==2:
            sc =Business.citire_suma()
            lista = Repository.eliminare2(evidenta,sc)
            print("Lista dupa eliminare:")
            Domeniu.afisare_lista(lista)
        elif user==3:
            break
        else :
            print("Tasta nu este valida")
def meniustergere(evidenta,istoric):
    """
    acesta functie este un submeniu de cautare care se apeleaza in meniul mare
    :param evidenta: lista
    :return:printeaza
    interfata cu utilizatorul
    """
    i=0
    while True:
        print("Apasati tasta 1 pentru a sterge toate cheltuielile de la un apartament")
        print("Apasati tasta 2 pentru a sterge cheltuielile de la doua apartamente consecutive")
        print("Apasati tasta 3 pentru a sterge cheltuielile de un anumit tip de la toate apartamentele")
        print("Apasati tasta 4 pentru terminarea procesului de cautare")
        user = int(input())
        if user==1:
            nr=Business.citire_nr_ap()
            Repository.stergere1(evidenta,nr)
            print("Apartamentele care mai au cheltuieli dupa stergere sunt: ")
            Domeniu.afisare_lista(evidenta)
            istoric.append(Domeniu.creeaza_copie(evidenta))
        elif user==2:
            nr1 = Business.citire_nr_ap()
            nr2 = Business.citire_douanumere_valide(nr1)
            Repository.stergere2(evidenta, nr1, nr2)
            print("Apartamentele care mai au cheltuieli dupa stergere sunt: ")
            Domeniu.afisare_lista(evidenta)
            istoric.append(Domeniu.creeaza_copie(evidenta))
        elif user==3:
            sir = Business.tipul_chelt()
            Repository.stergere3(evidenta,sir)
            print("Apartamentele care mai au cheltuieli dupa stergere sunt: ")
            Domeniu.afisare_lista(evidenta)
            istoric.append(Domeniu.creeaza_copie(evidenta))
        elif user==4:
            break
        else :
            print("Tasta nu este valida")
def meniu():
    """
    aceasta functie reprezinta meniul principal al programului care apeleaza restul functiilor de submeniu
    :return: apeleaza alte functii(functiile de submeniu) si printeaza randuri libere
    """
    istoric=[]
    evidenta=[]
    while True:
        print("Apasati 1 pentru ADAUGARE:")
        print("Apasati 2 pentru STERGERE:")
        print("Apasati 3 pentru CAUTARI:")
        print("Apasati 4 pentru RAPOARTE:")
        print("Apasati 5 pentru FILTRU:")
        print("Apasati 6 pentru UNDO:")
        print("Apasati 7 pentru TERMINAREA PROGRAMULUI")
        user=int(input())
        if user==1:
            meniuadaugare(evidenta,istoric)
            print()
        elif user==2:
            meniustergere(evidenta,istoric)
        elif user==3:
            meniucautari(evidenta)
            print()
        elif user==4:
            meniurapoarte(evidenta)
        elif user==5:
            meniufiltru(evidenta)
        elif user==6:
            evidenta = undo_ui(evidenta, istoric)
            print()
        elif user==7:
            break
        else:
            print("Tasta nu este valida")