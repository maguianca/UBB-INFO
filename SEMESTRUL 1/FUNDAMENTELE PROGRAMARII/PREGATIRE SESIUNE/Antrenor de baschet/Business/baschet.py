from Domeniu.validare import Validator
from Domeniu.baschet import Jucator
import random
class BusinessBaschet:
    def __init__(self,repo,validator):
        self.__repo=repo
        self.__validator=validator
    def adaugare(self,nume,prenume,inaltime,post):
        juc=Jucator(nume,prenume,inaltime,post)
        self.__validator.valideaza_jucator(juc)
        self.__repo.adaugare(juc)
    def modificare(self,nume,prenume,inaltime):
        #juc=Jucator(nume,prenume,inaltime,"Pivot")
        #self.__validator.valideaza_jucator(juc)
        self.__repo.modificare(nume,prenume,inaltime)
    def filtrare(self):
        lista=self.__repo.get_all()
        lista=sorted(lista,key=lambda x:x.get_inaltime(),reverse=True)
        lista1=[x for x in lista if x.get_post()=="Fundas"]
        lista1=lista1[:2]
        lista2 = [x for x in lista if x.get_post() == "Pivot"]
        lista2 = lista2[:1]
        lista3 = [x for x in lista if x.get_post() == "Extrema"]
        lista3 = lista3[:2]
        return lista1+lista2+lista3
    def importa(self,fisier):
        """lista=["Fundas","Pivot","Extrema"]
        cnt=0
        #"C:\Proiecte\Pregatire Sesiune\Antrenor de baschet\Data\\baschet.txt"
        with open(fisier,'r')as f:
            lines=f.readlines()
            for line in lines:
                if line!="":
                    params=line.strip().split(" ")
                    if len(params)==2:
                        nume=params[0]
                        prenume=params[1]
                        inaltime=random.randint(160,210)
                        post=random.choice(lista)
                        jucator=Jucator(nume,prenume,inaltime,post)
                        if self.__repo.cautare(nume,prenume) is not True:
                            cnt+=1
                            self.__repo.adaugare(jucator)
        return cnt"""
        return self.__repo.importa(fisier)


