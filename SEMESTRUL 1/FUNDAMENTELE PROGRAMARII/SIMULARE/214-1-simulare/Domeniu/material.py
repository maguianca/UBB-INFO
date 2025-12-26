class Material:
    def __init__(self,cod,denumire,cantitate,pret):
        self.__cod=cod
        self.__denumire=denumire
        self.__cantitate=cantitate
        self.__pret=pret
    def get_cod(self):
        """metoda getter"""
        return self.__cod
    def get_denumire(self):
        """metoda getter"""
        return self.__denumire
    def get_cantitate(self):
        """metoda getter"""
        return self.__cantitate
    def get_pret(self):
        """metoda getter"""
        return self.__pret
    def __eq__(self,val):
        """verifica daca doua el au acelasi id"""
        return val.get_cod()==self.get_cod()
    def __str__(self):
        """afiseaza corespunzator obiectul clasei"""
        return f"{self.__cod},{self.__denumire},{self.__cantitate},{self.__pret}"
class DTO:
    def __init__(self,denumire,cantitate,valoare):
        self.__denumire=denumire
        self.__cantitate=cantitate
        self.__valoare=valoare
    def __str__(self):
        return f"{self.__denumire},{self.__cantitate},{self.__valoare}"
def test():
    x=Material(1,"ciment",120,175)
    assert x.get_cod()==1
    assert x.get_cantitate()==120
    assert x.get_denumire()=="ciment"
test()