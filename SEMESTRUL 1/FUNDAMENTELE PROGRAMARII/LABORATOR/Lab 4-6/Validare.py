import Domeniu

def valideaza_cheltuiala(cheltuiala):
    """
    functie care verifica daca nr_ap si suma userului cheltuiala este poziti si numele nevid
    :preconsitii:user
    :posconditii: Exception cu mesajul:string
                  "numar apartament invalid \n" daca nr_ap<=0
                  "tip invalid\n" daca tip=""
                  "suma invalida\n" daca suma<=0
    """
    eroare=""
    if Domeniu.get_numar(cheltuiala)<=0:
        eroare+="numar apartament invalid\n"
    if Domeniu.get_tip(cheltuiala)=="":
        eroare+="tip invalid\n"
    if Domeniu.get_suma(cheltuiala)<=0:
        eroare+="suma invalida\n"
    if Domeniu.get_data(cheltuiala)<=0:
        eroare+="data invalida\n"
    if len(eroare)>0:
        raise Exception(eroare)
def valideaza_numar(numar):
    try:
        if type(numar) != int or numar<1:
            print("numar invalid")
    except ValueError:
            print("numar invalid")

def valideaza_numere_ap(nr1,nr2):
    """
    functie care verifica ca cele 2 numere sa fie in ordine crescatoare
    :param nr1: int
    :param nr2: int
    :return: exception daca numerele nu sunt in ordine crescatoare altfel nu se intampla nimic
    """
    eroare=""
    if nr1>nr2:
        eroare="numere invalide, nu sunt in ordine crescatoare"
        raise Exception(eroare)