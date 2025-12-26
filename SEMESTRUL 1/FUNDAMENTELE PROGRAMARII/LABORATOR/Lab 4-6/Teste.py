import Repository
import Domeniu
import Validare
def teste_adaugare_cheltuiala():
    cheltuiala1=Domeniu.creeaza_cheltuiala(1,120,"Apa",1)
    cheltuiala2=Domeniu.creeaza_cheltuiala(2,120,"Gaz",2)
    Validare.valideaza_cheltuiala(cheltuiala1)
    Validare.valideaza_cheltuiala(cheltuiala2)
    assert Domeniu.get_suma(cheltuiala1)==Domeniu.get_suma(cheltuiala2)
    assert Domeniu.get_numar(cheltuiala1)==1
    assert Domeniu.get_tip(cheltuiala1)=="Apa"
    assert Domeniu.get_data(cheltuiala2)==2
    cheltuiala3=Domeniu.creeaza_cheltuiala(-1,-125,"",-1)
    #Domeniu.valideaza_cheltuiala(cheltuiala3)


def teste_cautare1():
    lista = []
    ap1=Domeniu.creeaza_cheltuiala( 1, 120, "Apa",2)
    ap2=Domeniu.creeaza_cheltuiala(2, 50, "Gaz",3)
    ap3=Domeniu.creeaza_cheltuiala( 3, 70, "Apa",4)
    ap4=Domeniu.creeaza_cheltuiala( 4, 60, "Apa",5)
    ap5=Domeniu.creeaza_cheltuiala( 5, 60, "Apa",6)
    Repository.adauga_cheltuiala_la_buget(lista, ap1)
    Repository.adauga_cheltuiala_la_buget(lista, ap2)
    Repository.adauga_cheltuiala_la_buget(lista, ap3)
    Repository.adauga_cheltuiala_la_buget(lista, ap4)
    Repository.adauga_cheltuiala_la_buget(lista, ap5)
    test1=Repository.cautare1(lista,50)
    assert test1[0]==ap1
    assert test1[1]==ap3
    assert test1[2]==ap4
    assert test1[3]==ap5
    #assert test1==[1,3,4,5]
    #test2=cautare1(lista,69)
    #assert test2==[1,3]
    #test3=cautare1(lista,130)
    #assert test3==[]
    #test4=cautare1(lista,10)
    #assert test4==[1,2,3,4,5]

def teste_rap1():
    lista = []
    ap1 = Domeniu.creeaza_cheltuiala(1, 120, "Apa",1)
    ap2 = Domeniu.creeaza_cheltuiala(2, 50, "Gaz",2)
    ap3 = Domeniu.creeaza_cheltuiala(3, 70, "Apa",3)
    ap4 = Domeniu.creeaza_cheltuiala(4, 60, "Apa",4)
    ap5 = Domeniu.creeaza_cheltuiala(5, 60, "Apa",5)
    Repository.adauga_cheltuiala_la_buget(lista, ap1)
    Repository.adauga_cheltuiala_la_buget(lista, ap2)
    Repository.adauga_cheltuiala_la_buget(lista, ap3)
    Repository.adauga_cheltuiala_la_buget(lista, ap4)
    Repository.adauga_cheltuiala_la_buget(lista, ap5)
    assert Repository.rap1(lista, "Apa") == 310
    assert Repository.rap1(lista, "Altele") == 0
    assert Repository.rap1(lista, "Gaz") == 50

def teste_rap3():
    lista = []
    ap1 = Domeniu.creeaza_cheltuiala(1, 120, "Apa",1)
    ap2 = Domeniu.creeaza_cheltuiala(1, 50, "Gaz",2)
    ap3 = Domeniu.creeaza_cheltuiala(3, 70, "Apa",3)
    ap4 = Domeniu.creeaza_cheltuiala(4, 60, "Apa",4)
    ap5 = Domeniu.creeaza_cheltuiala(5, 60, "Apa",5)
    Repository.adauga_cheltuiala_la_buget(lista, ap1)
    Repository.adauga_cheltuiala_la_buget(lista, ap2)
    Repository.adauga_cheltuiala_la_buget(lista, ap3)
    Repository.adauga_cheltuiala_la_buget(lista, ap4)
    Repository.adauga_cheltuiala_la_buget(lista, ap5)
    assert Repository.rap3(lista,1)==170
    assert Repository.rap3(lista,6)==0
    assert Repository.rap3(lista,3)==70

def teste_rap2():
    lista = []
    ap1 = Domeniu.creeaza_cheltuiala(1, 120, "Apa",1)
    ap2 = Domeniu.creeaza_cheltuiala(1, 50, "Gaz",1)
    ap3 = Domeniu.creeaza_cheltuiala(3, 70, "Incalzire",1)
    ap4 = Domeniu.creeaza_cheltuiala(4, 60, "Apa",1)
    ap5 = Domeniu.creeaza_cheltuiala(5, 60, "Apa",1)
    ap6 = Domeniu.creeaza_cheltuiala(11, 1256, "Altele",2)
    ap7 = Domeniu.creeaza_cheltuiala(9, 125, "Incalzire",2)
    ap8 = Domeniu.creeaza_cheltuiala(10, 156, "Altele",2)
    Repository.adauga_cheltuiala_la_buget(lista, ap1)
    Repository.adauga_cheltuiala_la_buget(lista, ap2)
    Repository.adauga_cheltuiala_la_buget(lista, ap3)
    Repository.adauga_cheltuiala_la_buget(lista, ap4)
    Repository.adauga_cheltuiala_la_buget(lista, ap5)
    Repository.adauga_cheltuiala_la_buget(lista, ap6)
    Repository.adauga_cheltuiala_la_buget(lista, ap7)
    Repository.adauga_cheltuiala_la_buget(lista, ap8)
    test1=Repository.rap2(lista,"Apa")
    assert test1[0]==ap1
    assert test1[1]==ap4
    assert test1[2]==ap5
    test2=Repository.rap2(lista,"Altele")
    assert test2[0]==ap8
    assert test2[1]==ap6
    test3=Repository.rap2(lista,"Canal")
    assert test3==[]
    test4=Repository.rap2(lista,"Incalzire")
    assert test4[0]==ap3
    assert test4[1]==ap7

def teste_cautare2():
    lista=[]
    verif=[]
    ap1 = Domeniu.creeaza_cheltuiala(1, 120, "Apa",1)
    ap2 = Domeniu.creeaza_cheltuiala(1, 50, "Gaz",2)
    ap3 = Domeniu.creeaza_cheltuiala(3, 70, "Apa",3)
    ap4 = Domeniu.creeaza_cheltuiala(4, 60, "Apa",4)
    ap5 = Domeniu.creeaza_cheltuiala(5, 60, "Apa",1)
    Repository.adauga_cheltuiala_la_buget(lista, ap1)
    Repository.adauga_cheltuiala_la_buget(lista, ap2)
    Repository.adauga_cheltuiala_la_buget(lista, ap3)
    Repository.adauga_cheltuiala_la_buget(lista, ap4)
    Repository.adauga_cheltuiala_la_buget(lista, ap5)
    ve1 = Domeniu.creeaza_cheltuiala_sub(1, 120,1)
    ve2 = Domeniu.creeaza_cheltuiala_sub(3, 70,3)
    ve3 = Domeniu.creeaza_cheltuiala_sub(4, 60,4)
    ve4 = Domeniu.creeaza_cheltuiala_sub(5, 60,1)
    Repository.adauga_cheltuiala_la_buget(verif, ve1)
    Repository.adauga_cheltuiala_la_buget(verif, ve2)
    Repository.adauga_cheltuiala_la_buget(verif, ve3)
    Repository.adauga_cheltuiala_la_buget(verif, ve4)
    assert Repository.cautare2(lista,"Apa")==verif
    verif1 = []
    chelt1=Domeniu.creeaza_cheltuiala_sub(2,50,1)
    Repository.adauga_cheltuiala_la_buget(verif1,chelt1)
    assert Repository.cautare2(lista, "Altele") == []
    #test3=cautare2(lista,"Gaz")
    #assert Domeniu.get_numar(test3[0]) ==1


def teste_cautare3():
    lista=[]
    ap1 = Domeniu.creeaza_cheltuiala(1, 120, "Apa",1)
    ap2 = Domeniu.creeaza_cheltuiala(1, 50, "Gaz",1)
    ap3 = Domeniu.creeaza_cheltuiala(3, 70, "Apa",2)
    ap4 = Domeniu.creeaza_cheltuiala(4, 60, "Apa",3)
    ap5 = Domeniu.creeaza_cheltuiala(5, 60, "Apa",4)
    Repository.adauga_cheltuiala_la_buget(lista, ap1)
    Repository.adauga_cheltuiala_la_buget(lista, ap2)
    Repository.adauga_cheltuiala_la_buget(lista, ap3)
    Repository.adauga_cheltuiala_la_buget(lista, ap4)
    Repository.adauga_cheltuiala_la_buget(lista, ap5)
    teste1=Repository.cautare3(lista,2,40)
    assert len(teste1)==2
    assert teste1[0]==ap1
    assert Domeniu.get_data(teste1[1])==1
    assert Domeniu.get_suma(teste1[1])==50
    teste2=Repository.cautare3(lista,6,20)
    assert teste2==[]
    teste3=Repository.cautare3(lista,2,120)
    assert teste3==[]

def teste_eliminare1():
    lista = []
    ap1 = Domeniu.creeaza_cheltuiala(1, 10, "Apa",1)
    ap2 = Domeniu.creeaza_cheltuiala(2, 11, "Gaz",1)
    ap3 = Domeniu.creeaza_cheltuiala(3, 12, "Canal",1)
    ap4 = Domeniu.creeaza_cheltuiala(4, 13, "Incalzire",1)
    ap5 = Domeniu.creeaza_cheltuiala(5, 14, "Apa",1)
    Repository.adauga_cheltuiala_la_buget(lista, ap1)
    Repository.adauga_cheltuiala_la_buget(lista, ap2)
    Repository.adauga_cheltuiala_la_buget(lista, ap3)
    Repository.adauga_cheltuiala_la_buget(lista, ap4)
    Repository.adauga_cheltuiala_la_buget(lista, ap5)
    test1 = Repository.eliminare1(lista, "Apa")
    assert test1[0]==ap2
    assert test1[1]==ap3
    assert test1[2]==ap4
    assert len(test1)==3
    test2=Repository.eliminare1(lista,"Altele")
    assert len(test2)==len(lista)
    test3=Repository.eliminare1(lista,"Incalzire")
    assert test3[3]==ap5
    assert len(test3)==4


def teste_eliminare2():
    lista = []
    ap1 = Domeniu.creeaza_cheltuiala(1, 10, "Apa",1)
    ap2 = Domeniu.creeaza_cheltuiala(2, 11, "Gaz",1)
    ap3 = Domeniu.creeaza_cheltuiala(3, 12, "Canal",1)
    ap4 = Domeniu.creeaza_cheltuiala(4, 13, "Incalzire",1)
    ap5 = Domeniu.creeaza_cheltuiala(5, 14, "Apa",1)
    Repository.adauga_cheltuiala_la_buget(lista, ap1)
    Repository.adauga_cheltuiala_la_buget(lista, ap2)
    Repository.adauga_cheltuiala_la_buget(lista, ap3)
    Repository.adauga_cheltuiala_la_buget(lista, ap4)
    Repository.adauga_cheltuiala_la_buget(lista, ap5)
    test1 = Repository.eliminare2(lista, 12)
    assert test1[0] == ap3
    assert test1[1] == ap4
    assert test1[2] == ap5
    assert len(test1) == 3
    test2 = Repository.eliminare2(lista,10)
    assert len(test2) == len(lista)
    test3 = Repository.eliminare2(lista, 20)
    assert len(test3)==0


def teste_stergere1():
    lista = []
    ap1 = Domeniu.creeaza_cheltuiala(1, 10, "Apa",1)
    ap2 = Domeniu.creeaza_cheltuiala(2, 11, "Gaz",1)
    ap3 = Domeniu.creeaza_cheltuiala(3, 12, "Canal",2)
    ap4 = Domeniu.creeaza_cheltuiala(4, 13, "Incalzire",2)
    ap5 = Domeniu.creeaza_cheltuiala(5, 14, "Apa",2)
    Repository.adauga_cheltuiala_la_buget(lista, ap1)
    Repository.adauga_cheltuiala_la_buget(lista, ap2)
    Repository.adauga_cheltuiala_la_buget(lista, ap3)
    Repository.adauga_cheltuiala_la_buget(lista, ap4)
    Repository.adauga_cheltuiala_la_buget(lista, ap5)
    assert len(Repository.stergere1(lista,1))==4
    assert len(Repository.stergere1(lista,0))==4
    test1=Repository.stergere1(lista,5)
    assert test1[0]==ap2
    assert test1[1]==ap3
    assert test1[2]==ap4

def teste_stergere2():
    lista = []
    ap1 = Domeniu.creeaza_cheltuiala(1, 10, "Apa",1)
    ap2 = Domeniu.creeaza_cheltuiala(2, 11, "Gaz",1)
    ap3 = Domeniu.creeaza_cheltuiala(3, 12, "Canal",1)
    ap4 = Domeniu.creeaza_cheltuiala(4, 13, "Incalzire",1)
    ap5 = Domeniu.creeaza_cheltuiala(5, 14, "Apa",1)
    Repository.adauga_cheltuiala_la_buget(lista, ap1)
    Repository.adauga_cheltuiala_la_buget(lista, ap2)
    Repository.adauga_cheltuiala_la_buget(lista, ap3)
    Repository.adauga_cheltuiala_la_buget(lista, ap4)
    Repository.adauga_cheltuiala_la_buget(lista, ap5)
    test1=Repository.stergere2(lista,1,2)
    assert test1[0]==ap3
    assert test1[1]==ap4
    assert test1[2]==ap5
    assert len(Repository.stergere2(lista,1,6))==0
    assert len(Repository.stergere2(lista,7,10))==len(lista)
    lista1=[]
    ap1 = Domeniu.creeaza_cheltuiala(1, 10, "Apa",1)
    ap2 = Domeniu.creeaza_cheltuiala(2, 11, "Gaz",1)
    ap3 = Domeniu.creeaza_cheltuiala(3, 12, "Canal",1)
    ap4 = Domeniu.creeaza_cheltuiala(4, 13, "Incalzire",1)
    ap5 = Domeniu.creeaza_cheltuiala(5, 14, "Apa",1)
    Repository.adauga_cheltuiala_la_buget(lista1, ap1)
    Repository.adauga_cheltuiala_la_buget(lista1, ap2)
    Repository.adauga_cheltuiala_la_buget(lista1, ap3)
    Repository.adauga_cheltuiala_la_buget(lista1, ap4)
    Repository.adauga_cheltuiala_la_buget(lista1, ap5)
    test2=Repository.stergere2(lista1,2,4)
    assert test2[0]==ap1
    assert test2[1]==ap5


def teste_stergere3():
    lista = []
    ap1 = Domeniu.creeaza_cheltuiala(1, 10, "Apa",1)
    ap2 = Domeniu.creeaza_cheltuiala(2, 11, "Gaz",1)
    ap3 = Domeniu.creeaza_cheltuiala(3, 12, "Canal",2)
    ap4 = Domeniu.creeaza_cheltuiala(4, 13, "Incalzire",2)
    ap5 = Domeniu.creeaza_cheltuiala(5, 14, "Apa",2)
    Repository.adauga_cheltuiala_la_buget(lista, ap1)
    Repository.adauga_cheltuiala_la_buget(lista, ap2)
    Repository.adauga_cheltuiala_la_buget(lista, ap3)
    Repository.adauga_cheltuiala_la_buget(lista, ap4)
    Repository.adauga_cheltuiala_la_buget(lista, ap5)
    test1=Repository.stergere3(lista,"Apa")
    assert test1[0]==ap2
    assert test1[1]==ap3
    assert test1[2]==ap4
    assert len(test1)==3
    assert Repository.stergere3(lista, "Altele") == lista
    assert Repository.stergere3(lista, "Apa") == lista
    lista1=[]
    ap1 = Domeniu.creeaza_cheltuiala(1, 10, "Apa",1)
    ap2 = Domeniu.creeaza_cheltuiala(2, 11, "Apa",1)
    ap3 = Domeniu.creeaza_cheltuiala(3, 12, "Apa",2)
    Repository.adauga_cheltuiala_la_buget(lista1, ap1)
    Repository.adauga_cheltuiala_la_buget(lista1, ap2)
    Repository.adauga_cheltuiala_la_buget(lista1, ap3)
    assert len(Repository.stergere3(lista1,"Apa"))==0

def test_modificare_intre_cheltuieli():
    c1 = Domeniu.creeaza_cheltuiala(1, 120, "Apa",1)
    c2 = Domeniu.creeaza_cheltuiala(2, 50, "Gaz",1)
    Repository.modificare_intre_cheltuieli(c1,c2)
    assert Domeniu.get_suma(c1)==Domeniu.get_suma(c2)
    assert Domeniu.get_tip(c1)==Domeniu.get_tip(c2)
    assert Domeniu.get_data(c1)==Domeniu.get_data(c2)


def teste_modificare_cheltuiala():
    lista = []
    ap1 = Domeniu.creeaza_cheltuiala(1, 120, "Apa",1)
    ap2 = Domeniu.creeaza_cheltuiala(2, 50, "Gaz",2)
    verif = Domeniu.creeaza_cheltuiala(1, 70, "Apa",3)
    Repository.adauga_cheltuiala_la_buget(lista, ap1)
    Repository.adauga_cheltuiala_la_buget(lista, ap2)
    Repository.modificare_cheltuiala(lista,1,verif)
    assert Domeniu.get_suma(lista[0])==Domeniu.get_suma(verif)
    assert Domeniu.get_tip(lista[0])==Domeniu.get_tip(verif)
    assert Domeniu.get_data(lista[0])==Domeniu.get_data(verif)


def test_creeaza_cheltuiala():
    nr_ap=1
    suma=125
    tip="Apa"
    epsilon=0.0001
    data=12
    cheltuiala=Domeniu.creeaza_cheltuiala(nr_ap,suma,tip,data)
    assert(Domeniu.get_tip(cheltuiala)==tip)
    assert(Domeniu.get_numar(cheltuiala)==nr_ap)
    assert(Domeniu.get_suma(cheltuiala)==suma)
    assert(Domeniu.get_data(cheltuiala)==data)
    assert (abs(Domeniu.get_suma(cheltuiala)-suma)<epsilon)

def test_valideaza_cheltuiala():
    nr_ap=1
    suma=125
    tip="Apa"
    data=12
    cheltuiala_valida=Domeniu.creeaza_cheltuiala(nr_ap,suma,tip,data)
    nr_ap_1 = -1
    suma_1 = -125
    tip_1 = ""
    data1=0
    cheltuiala_invalida=Domeniu.creeaza_cheltuiala(nr_ap_1,suma_1,tip_1,data1)
    try:
        Validare.valideaza_cheltuiala(cheltuiala_invalida)
        assert(False)
    except Exception as ex:
        assert(str(ex)=="numar apartament invalid\ntip invalid\nsuma invalida\ndata invalida\n")

def test_tipuri():
    """
    aceasta este o functie care valideaza functie de tipuri
    """
    assert(Domeniu.tipuri(1)=="Apa")
    assert(Domeniu.tipuri(2)=="Canal")
    assert(Domeniu.tipuri(3)=="Incalzire")
    assert(Domeniu.tipuri(4)=="Gaz")
    assert(Domeniu.tipuri(5)=="Altele")
    assert(Domeniu.tipuri(152556)==0)
def test_creeaza_cheltuiala_sub():
    nr_ap=1
    suma=125
    epsilon=0.0001
    data=12
    cheltuiala=Domeniu.creeaza_cheltuiala_sub(nr_ap,suma,data)
    assert(Domeniu.get_numar(cheltuiala)==nr_ap)
    assert(Domeniu.get_suma(cheltuiala)==suma)
    assert Domeniu.get_data(cheltuiala)==data
    assert (abs(Domeniu.get_suma(cheltuiala)-suma)<epsilon)
def teste_myundo_adaugare2():
    lst1 = []
    ist1=[]
    verif1 = Domeniu.creeaza_cheltuiala(1, 70, "Apa", 3)
    ap1 = Domeniu.creeaza_cheltuiala(1, 120, "Apa", 1)
    Repository.adauga_cheltuiala_la_buget(lst1, ap1)
    ist1.append(Domeniu.creeaza_copie(lst1))
    lista1=Repository.modificare_cheltuiala(lst1, 1, verif1)
    ist1.append(Domeniu.creeaza_copie(lista1))
    assert Domeniu.get_suma(lista1[0]) == Domeniu.get_suma(verif1)
    assert Domeniu.get_tip(lista1[0]) == Domeniu.get_tip(verif1)
    assert Domeniu.get_data(lista1[0]) == Domeniu.get_data(verif1)
    ev=Repository.myundo(ist1)
    assert Domeniu.get_suma(ev[0]) == 120
    assert Domeniu.get_tip(ev[0]) == "Apa"
    assert Domeniu.get_data(ev[0]) == 1
def teste_myundo_adaugare1():
    lst = []
    ist=[]
    ap1 = Domeniu.creeaza_cheltuiala(1, 10, "Apa", 1)
    Repository.adauga_cheltuiala_la_buget(lst, ap1)
    ist.append(Domeniu.creeaza_copie(lst))
    ap2 = Domeniu.creeaza_cheltuiala(2, 11, "Gaz", 1)
    Repository.adauga_cheltuiala_la_buget(lst, ap2)
    ist.append(Domeniu.creeaza_copie(lst))
    ap3 = Domeniu.creeaza_cheltuiala(3, 12, "Canal", 2)
    Repository.adauga_cheltuiala_la_buget(lst, ap3)
    ist.append(Domeniu.creeaza_copie(lst))
    assert len(lst)==3
    l = Repository.myundo(ist)
    assert len(l)==2
    assert l[0]==ap1
    assert l[1]==ap2
    l2=Repository.myundo(ist)
    assert len(l2)==1
    assert l2[0]==ap1
    l3=Repository.myundo(ist)
    assert l3==[]
def teste_undo_stergere():
    lst = []
    ist = []
    ap1 = Domeniu.creeaza_cheltuiala(1, 10, "Apa", 1)
    ap2 = Domeniu.creeaza_cheltuiala(2, 11, "Gaz", 1)
    ap3 = Domeniu.creeaza_cheltuiala(3, 12, "Apa", 2)
    Repository.adauga_cheltuiala_la_buget(lst, ap1)
    Repository.adauga_cheltuiala_la_buget(lst, ap2)
    Repository.adauga_cheltuiala_la_buget(lst, ap3)
    assert len(lst) == 3
    assert Domeniu.get_suma(lst[2]) == 12
    assert Domeniu.get_tip(lst[2]) == "Apa"
    assert Domeniu.get_data(lst[2]) == 2
    ist.append(Domeniu.creeaza_copie(lst))
    ist.append(Domeniu.creeaza_copie(Repository.stergere3(lst,"Apa")))
    assert len(lst)==1
    assert Domeniu.get_suma(lst[0]) == 11
    assert Domeniu.get_tip(lst[0]) == "Gaz"
    assert Domeniu.get_data(lst[0]) == 1
    e=Repository.myundo(ist)
    assert len(e) == 3
    assert Domeniu.get_suma(e[2]) == 12
    assert Domeniu.get_tip(e[2]) == "Apa"
    assert Domeniu.get_data(e[2]) == 2
def ruleaza_toate_testele():
      test_tipuri()
      test_valideaza_cheltuiala()
      test_creeaza_cheltuiala()
      teste_modificare_cheltuiala()
      test_modificare_intre_cheltuieli()
      teste_stergere2()
      teste_stergere1()
      teste_stergere3()
      teste_rap1()
      teste_rap2()
      teste_rap3()
      teste_eliminare2()
      teste_eliminare1()
      teste_cautare3()
      teste_cautare2()
      teste_cautare1()
      teste_adaugare_cheltuiala()
      test_creeaza_cheltuiala_sub()
      teste_myundo_adaugare2()
      teste_myundo_adaugare1()
      teste_undo_stergere()