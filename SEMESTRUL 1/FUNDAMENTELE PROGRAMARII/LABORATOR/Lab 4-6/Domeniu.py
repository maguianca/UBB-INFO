
def set_suma(lista,suma):
    """
    functie care seteaza suma userului lista
    :param lista: lista
    :param suma: int
    """
    lista['Suma']=suma
def get_suma(lista):
    """
       functie care returneaza suma userului lista
       :param lista: lista
       """
    return lista['Suma']
def set_tip(lista,tip):
    """
       functie care seteaza tipul userului lista
       :param lista: lista
       :param tip:string
       """
    lista['Tip']=tip
def set_data(lista,data):
    """
    functie care seteaza data userului cu o alta valoare
    :param lista: lista
    :param data:
    """
    lista['Data']=data
def get_data(lista):
    """
    functie care returneaza data userului lista
    :param lista: lista
    """
    return lista['Data']
def get_tip(lista):
    """
       functie care returneaza tipul userului lista
       :param lista:lista
       """
    return lista['Tip']
def set_numar(lista,numar):
    """
       functie care seteaza suma userului lista
       :param lista:lista
       :param numar:int
       """
    lista['Apartament']=numar
def get_numar(lista):
    """
       functie care returneaza numarul userului lista
       :param lista:lista
    """
    return lista['Apartament']


def creeaza_cheltuiala(nr_ap,suma,tip,data):
    """
    functie care creeaza o entitate pe baza a nr_ap,suma tip,data
    :param nr_ap: int
    :param suma: int
    :param tip: string
    :param data:int
    return: user cu nr_ap,suma ,tip,data
    """
    return {'Apartament': nr_ap,
            'Suma': suma,
            'Tip': tip,
            'Data':data}


def creeaza_cheltuiala_sub(nr_ap,suma,data):
    """
    functie care creeaza un user pe baza a nr_ap si suma
    :param nr_ap: int
    :param suma: int
    :return:user cu nr_ap si suma
    """
    return {'Apartament': nr_ap,
            'Suma': suma,
            'Data':data}

def tipuri(tip):
    """
        aceasta functie returneaza valoarea care corespunde numarului din meniu
    """
    if tip==1:
        return "Apa"
    elif tip==2:
        return "Canal"
    elif tip==3:
        return "Incalzire"
    elif tip==4:
        return "Gaz"
    elif tip==5:
        return "Altele"
    else:
        return 0

def printeaza_cheltuiala():
    print("Introduceti numarul in functie de tipul cheltuielii:")
    print("\n1.Apa\n2.Canal\n3.Incalzire\n4.Gaz\n5.Altele")

def afisare_lista(evidenta):
    """
    aceasta functie afiseaza elementele separat fiecare pe un rand separat
    :param evidenta: lista
    :return: afisare lista
    """
    if (len(evidenta)):
        print("Nr.Ap Suma  Tip cheltuiala  Data")
        for i in range(0, len(evidenta)):
            if(get_numar(evidenta[i])):
                print(get_numar(evidenta[i]),"   ",get_suma(evidenta[i]), "   ",get_tip(evidenta[i]),"  ",get_data(evidenta[i]))
    else:
        print("nu sunt elemente")

def afisare_cheltuieli(evidenta):
    """
    este o functie de afisare a listei complete
    :param evidenta:lista
    :return:print
    """
    if(len(evidenta)):
        print("Nr.Ap Suma Data")
        for i in range(0,len(evidenta)):
            if get_numar(evidenta[i]):
                print(get_numar(evidenta[i]),"   ",get_suma(evidenta[i]),"   ",get_data(evidenta[i]))
    else:
        print("nu sunt elemente")
def exista_index(evidenta,index):
    """
    aceasta functie verifica daca exista apartamentul cu indexul respectiv in lista
    :param evidenta: lista
    :param index: int
    :return: pozitia daca exista sau -1 in caz contrar
    """
    for i in range(0,len(evidenta)):
        if get_numar(evidenta[i])==index:
            return i
    return -1

def creeaza_copie(lista_ac):
    """
       Face o copie "deep" a listei date
       :param lst: lista de dictionare
       :return: copia listei
       """
    lista_copiata = []
    for current_dictionary in lista_ac:
        dictionar= {}
        for key, value in current_dictionary.items():
            dictionar[key] = value

        lista_copiata.append(dictionar)

    return lista_copiata