import Business
import Domeniu
def adauga_cheltuiala_la_buget(lista,cheltuiala):
    """
    functie care adauga cheltuiala in lista
    :param lista:lista
    :param cheltuiala:lista
    :return:adaugare in lista
    """
    lista.append(cheltuiala)
    return lista
def adaugare_cheltuiala(evidenta):
    """
    adauga cheltuiala intr-o lista de dictionare
     param evidenta:
            evidenta lista
    Apartament: int
    Suma: int
    Tip: str ("Apa"/"Gaz"/"Incalzire"/"Canal"/"Altele")
    :return:
        lista de dictionare actualizata cu o noua cheltuiala, cu un nou dictionar
    """
    nr_ap=Business.citire_nr_ap()
    suma=Business.citire_suma()
    tip=Business.tipul_chelt()
    data=Business.citire_data()
    cheltuiala=Domeniu.creeaza_cheltuiala(nr_ap,suma,tip,data)
    adauga_cheltuiala_la_buget(evidenta,cheltuiala)
    return evidenta

def cautare1(evidenta,sc):
    """
    :param evidenta: lista
    :param sc:
    :return: functia returneaza o lista cu apartementente care au suma mai mare deact sc
    """
    #aici trb sa fac si except value error# cautari1
    #print("Introduceti o valoare pentru afisa apartamentele care au cheltuieli restanta mai mari decat valoarea respectiva:")
    apartamente=[]
    for i in range(len(evidenta)):
        if Domeniu.get_suma(evidenta[i])>sc:
            adauga_cheltuiala_la_buget(apartamente,evidenta[i])
            #apartamente.append(Domeniu.get_numar(evidenta[i]))
    return apartamente



#functii set si get nu evidenta[i]['Suma'] se ascund detaliile de implementare -arhitectura stratificate
#doar in set si get ne referim la chestii de implementare get_suma(evidenta[i])
#domeniu apartament set-eri get-eri fiacre atribut de ex suma si tip_cheltuieli get_suma si get_tip_cheltuieli functii implementate mai sus
def rap1(evidenta,sir):#rapoarte 1
    """
    aceasta functie returneaza o valoare care reprezinta suma unor elemente din lista care au tipul precizat
    :param evidenta: lista
    :param sir: str
    :return: int o valoare
    """
    stotal = 0
    for i in range(len(evidenta)):
        if Domeniu.get_tip(evidenta[i])==sir:
            stotal = stotal + Domeniu.get_suma(evidenta[i])
    return stotal


def rap3(evidenta,nr):
    """
    returneaza o valoare ce reprezinta totalul de cheltuieli a unui apartament
    :param evidenta: lista
    :param nr: int
    :return: int
    """
    sum=0
    for i in range(0,len(evidenta)):
        if Domeniu.get_numar(evidenta[i])==nr:
            sum=sum+Domeniu.get_suma(evidenta[i])
    return sum


def rap2(evidenta,sir):
    """
    functie ce sorteaza elementele din lista curenta care au un anumit tip de cheltuiala
    :param evidenta: lista
    :param sir: string
    :return: lista
    """
    lista=[]
    for i in range(0,len(evidenta)):
        if Domeniu.get_tip(evidenta[i])==sir:
            cheltuiala=Domeniu.creeaza_cheltuiala(Domeniu.get_numar(evidenta[i]),Domeniu.get_suma(evidenta[i]),Domeniu.get_tip(evidenta[i]),Domeniu.get_data(evidenta[i]))
            adauga_cheltuiala_la_buget(lista,cheltuiala)
           # Domeniu.creaza(lista,Domeniu.get_numar(evidenta[i]),Domeniu.get_suma(evidenta[i]),Domeniu.get_tip(evidenta[i]))
    lista.sort(key=Domeniu.get_numar)
    return lista

def cautare2(evidenta,sir):
    """
    aceasta functie returneaza o lista comprimata a listei din parametru(primul parametru) daca elementul din lista esre egal cu sirul precizat (al doilea parametru din functie)
    :param evidenta: lista
    :param sir: str
    :return: o lista
    """
    lista=[]
    for i in range(len(evidenta)):
        if Domeniu.get_tip(evidenta[i])==sir:
            cheltuiala=Domeniu.creeaza_cheltuiala_sub(Domeniu.get_numar(evidenta[i]),Domeniu.get_suma(evidenta[i]),Domeniu.get_data(evidenta[i]))
            adauga_cheltuiala_la_buget(lista,cheltuiala)
            #Domeniu.creazasub(lista,Domeniu.get_numar(evidenta[i]),Domeniu.get_suma(evidenta[i]))
    return lista


def cautare3(evidenta,data,suma):
    """
    functie ce returneaza o lista cu apartamentele care au efectuat inainte de o zi plata si au suma mai mica decat o val
    :param evidenta: lista
    :param data: int
    :param suma: int
    :return: lista
    """
    lista = []
    for i in range(len(evidenta)):
        if Domeniu.get_data(evidenta[i]) == data-1 and Domeniu.get_suma(evidenta[i])>suma:
            cheltuiala = Domeniu.creeaza_cheltuiala(Domeniu.get_numar(evidenta[i]), Domeniu.get_suma(evidenta[i]),Domeniu.get_tip(evidenta[i]),Domeniu.get_data(evidenta[i]))
            adauga_cheltuiala_la_buget(lista, cheltuiala)

    return lista

def eliminare1(evidenta,sir):
    """
    aceasta functie returneaza o noua lista care prezinta doar anumite elemente care corespund cerintei din lista parametru
    aceasta functie returneaza o noua lista cu elementele din lista a caror elemente sunt egale cu al doilea parametru al functiei
    :param evidenta: lista
    :param sir: str
    :return: lista
    """
    res = [i for i in evidenta if not (Domeniu.get_tip(i) == sir)]
    return res

def eliminare2(evidenta,sc):
    """
     aceasta functie returneaza o noua lista care prezinta doar anumite elemente care corespund cerintei din lista parametru
     aceasta functie returneaza elementele din lista parametru a caror valoare e mai mica ca al doilea parametru din functie sc
    :param evidenta: lista
    :param evidenta:lista
    :param sc: int
    :return: o lista
    """
    res = [i for i in evidenta if not (Domeniu.get_suma(i) < sc)]
    return res


def stergere1(evidenta,nr):
    """
    aceasta functie sterge toate cheltuielile de la un apartament
    :param evidenta: lista
    :param nr: int
    :return: lista modificata
    """
    for i in range(0,len(evidenta)):
        if Domeniu.get_numar(evidenta[i])==nr:
            evidenta.pop(i)
            break
    return evidenta


def stergere2(evidenta,nr1,nr2):
    """
    aceasta functie sterge cheltuielile de la apartamente consecutive
    :param evidenta: lista
    :param nr1: int
    :param nr2: int
    :return: lista modificata
    """
    ok=0
    for i in range(0,len(evidenta)):
        if Domeniu.get_numar(evidenta[i]) >= nr1 and Domeniu.get_numar(evidenta[i]) <= nr2:
            del evidenta[i]
            ok=1
            break
    while ok==1:
        ok=0
        for i in range(0, len(evidenta)):
            if Domeniu.get_numar(evidenta[i]) >= nr1 and Domeniu.get_numar(evidenta[i]) <= nr2:
                del evidenta[i]
                ok = 1
                break
    return evidenta


def stergere3(evidenta,tip):

    """
     functie care sterge cheltuielile de un anumit tip de la toate apartamentele
    :param evidenta:
    :param tip:
    :return:
    """
    ok = 0
    for i in range(0, len(evidenta)):
        if Domeniu.get_tip(evidenta[i])==tip:
            del evidenta[i]
            ok = 1
            break
    while ok == 1:
        ok = 0
        for i in range(0, len(evidenta)):
            if Domeniu.get_tip(evidenta[i]) == tip:
                del evidenta[i]
                ok = 1
                break
    return evidenta


def modificare_cheltuiala(evidenta,index,cheltuiala1):
    """
    aceasta functie modifica cheltuiala daca aceasta exista in lista
    :param evidenta: lista
    :param index: int
    """
    pozitie=Domeniu.exista_index(evidenta,index)
    if pozitie==-1:
        print("Apartementul nu se afla in lista, va rugam adaugati aparatmentul in lista")
    else:
        modificare_intre_cheltuieli(evidenta[pozitie],cheltuiala1)
    return evidenta
def modificare_intre_cheltuieli(cheltuiala1,cheltuiala2):
    """
    functie care modifica suma si tipul din cheltuiala1 cu suma si tipul din cheltuaiala 2
    :param cheltuiala1: lista
    :param cheltuiala2: lista
    """
    Domeniu.set_suma(cheltuiala1,Domeniu.get_suma(cheltuiala2))
    Domeniu.set_tip(cheltuiala1, Domeniu.get_tip(cheltuiala2))
    Domeniu.set_data(cheltuiala1,Domeniu.get_data(cheltuiala2))

def myundo(istoric):
    """
    Anuleaza ultima operatie
    :return: -
    :raises ValueError daca nu se mai poate face undo
    """
    if len(istoric) > 0:
        istoric.pop(len(istoric)-1)
        if istoric==[]:
            #print("lista e goala")
            return []
        else:
             return istoric[len(istoric)-1]
    else:
        raise ValueError("Nu se mai poate face undo.")

