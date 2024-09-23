class Mobilier:
    def __init__(self,cod,tip,nume,stock,pret):
        self.__cod=cod
        self.__tip=tip
        self.__nume=nume
        self.__stock=stock
        self.__pret=pret

    def get_cod(self):
        return self.__cod

    def get_tip(self):
        return self.__tip

    def get_nume(self):
        return self.__nume

    def get_stock(self):
        return self.__stock

    def get_pret(self):
        return self.__pret

    def set_cod(self,val):
        self.__cod=val

    def set_tip(self,val):
        self.__tip=val

    def set_nume(self,val):
        self.__nume=val

    def set_stock(self,val):
        self.__stock=val

    def set_pret(self,val):
        self.__pret=val

    def __eq__(self, other):
        return self.__cod==other.__cod
    def __str__(self):
        return f"{self.__cod},{self.__tip},{self.__nume},{self.__stock},{self.__pret}"
#DTO
class Mob:
    def __init__(self,nume,stock,pret):
        self.__nume = nume
        self.__stock = stock
        self.__pret = pret

    def get_nume(self):
        return self.__nume

    def get_stock(self):
        return self.__stock

    def get_pret(self):
        return self.__pret

    def set_nume(self, val):
        self.__nume = val

    def set_stock(self, val):
        self.__stock = val

    def set_pret(self, val):
        self.__pret = val

def test_domeniu():
    mobilier=Mob("dulap",5,75.85)
    assert mobilier.get_nume()=="dulap"
    assert mobilier.get_pret()==75.85
    assert mobilier.get_stock()==5
test_domeniu()