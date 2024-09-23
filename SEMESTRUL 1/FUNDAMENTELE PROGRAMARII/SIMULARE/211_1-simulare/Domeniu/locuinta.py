class Locuinta:
    def __init__(self, id, adresa, oras, pret, garantie):
        self.__id = id
        self.__adresa = adresa
        self.__oras = oras
        self.__pret = pret
        self.__garantie = garantie

    def get_id(self):
        return self.__id

    def get_adresa(self):
        return self.__adresa

    def get_oras(self):
        return self.__oras

    def get_pret(self):
        return self.__pret

    def get_garantie(self):
        return self.__garantie

    def set_id(self, val):
        self.__id = val

    def set_adresa(self, val):
        self.__adresa = val

    def set_oras(self, val):
        self.__oras = val

    def set_pret(self, val):
        self.__pret = val

    def set_garantie(self, val):
        self.__garantie = val

    def __eq__(self,val):
        return val.get_id()==self.get_id()

    def __str__(self):
        return f"{self.__id},{self.__adresa},{self.__oras},{self.__pret},{self.__garantie}"

class DTO:
    def __init__(self,id,adresa,oras,pret,garantie):
        self.__id = id
        self.__adresa = adresa
        self.__oras = oras
        self.__pret = pret
        self.__garantie=garantie
        self.__calcul=0

    def get_id(self):
        return self.__id
    def get_calcul(self):
        return self.__calcul

    def get_adresa(self):
        return self.__adresa

    def get_oras(self):
        return self.__oras

    def get_pret(self):
        return self.__pret
    def calculeaza(self):
        self.__calcul=self.__pret*3/2+self.__garantie

def test():
    x = Locuinta(1, "dorobanti", "Cluj", 1750.5, 1000)
    assert x.get_id() == 1
    assert x.get_garantie() == 1000
    assert x.get_oras() == "Cluj"
    y=DTO(1,"dorobanti","cluj",1000,500)
    assert y.get_id() == 1
    assert y.get_adresa() =="dorobanti"
    assert y.get_oras() == "cluj"
    y.calculeaza()
    assert y.get_calcul()==2000


test()
