class Jucator:
    def __init__(self,nume,prenume,inaltime,post):
        self.__nume=nume
        self.__prenume=prenume
        self.__post=post
        self.__inaltime=inaltime
    def get_nume(self):
        return self.__nume
    def get_prenume(self):
        return self.__prenume
    def get_post(self):
        return self.__post
    def get_inaltime(self):
        return self.__inaltime
    def set_nume(self,n):
        self.__nume=n
    def set_prenume(self,n):
        self.__prenume=n
    def set_post(self,n):
        self.__post=n
    def set_inaltime(self,n):
        self.__inaltime=n
    def __str__(self):
        return f"{self.__nume},{self.__prenume},{self.__inaltime},{self.__post}"
def test_domeniu():
    juc=Jucator("Angel","Simon",538,"atacant")
    assert juc.get_nume()=="Angel"
    assert juc.get_inaltime()==538
    assert juc.get_post()=="atacant"
    juc.set_prenume("Vasiliu")
    assert juc.get_prenume()=="Vasiliu"


test_domeniu()