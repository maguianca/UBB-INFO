import Domeniu
import Validare

def citire_nr_ap():
    """
    citeste si valideaza datele introduce de utilizator pentru numar apartament
    return numar apartament sau mesaj
    """
    while True:
        try:
            print("Introduceti numarul apartamentului:")
            numar = int(input())
            if type(numar) != int or numar<1:
                print("Aparatmentul nu exista, introduceti un numar valid")
                continue
            return numar
        except ValueError:
            print("Aparatmentul nu exista, introduceti un numar valid")

def citire_suma():
    """
        aceasta functie citeste si determina daca ceea ce a introdus utlizatorul este un numar valid
        return suma sau mesaj
    """
    print("Introduceti suma:")
    while True:
        try:
            suma = int(input())
            if type(suma) != int or suma<0:
                print("Suma nu este valida, introduceti din nou suma:")
                continue
            return suma
        except ValueError:
            print("Suma nu este valida, introduceti din nou suma:")


def tipul_chelt():
    """
        aceasta functie citeste numarul tipului de cheltuiala din meniu introdus de utilizator
     """
    # print("Introduceti numarul in functie de tipul cheltuielii:")
    # print("\n1.Apa\n2.Canal\n3.Incalzire\n4.Gaz\n5.Altele")
    Domeniu.printeaza_cheltuiala()
    while True:
        try:
            tip = int(input())
            if tip < 1 or tip > 5:
                print("Numarul nu este valid")
                continue
            return Domeniu.tipuri(tip)
        except ValueError:
            print("Numarul nu este valid")
def citire_data():
    """
    citeste data curenta si o valideaza
    :return: int sau mesaj daca e valuerror
    """
    print("Introduceti data din luna cand s-a platit cheltuiala:")
    while True:
        try:
            data = int(input())
            if data < 1 or data > 31 or type(data)!=int:
                print("Data nu este valida")
                continue
            return data
        except ValueError:
            print("Data nu este valida")
def index_valid(evidenta):
    """
    valideaza indexul daca numarul apartamentul se afla in lista
    :param evidenta: lista
    :return: int sau mesaj daca e valueeror
    """
    while True:
        try:
            index=citire_nr_ap()
            if Domeniu.exista_index(evidenta, index) == -1:
                print("numar invalid")
                continue
            return index
        except IndexError:
            print("numar invalid")
def citire_douanumere_valide(n1):
    """
    functie care citeste al doilea numar al apartamentului si verifica daca este mai mare decat parametrul functiei
    :param n1: int
    :return:int sau mesaj daca e exceptie
    """
    while True:
        n2=citire_nr_ap()
        try:
            Validare.valideaza_numere_ap(n1,n2)
            return n2
        except Exception:
            print("numerele nu sunt in ordine crescatoare, introduceti din nou al doilea numar")