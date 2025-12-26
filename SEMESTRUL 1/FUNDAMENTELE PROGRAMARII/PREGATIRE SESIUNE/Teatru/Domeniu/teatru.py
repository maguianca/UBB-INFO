class Piesa:
    def __init__(self,titlu,regizor,gen,durata):
        self.__titlu=titlu
        self.__regizor=regizor
        self.__gen=gen
        self.__durata=durata
    def set_titlu(self,n):
        self.__titlu=n
    def set_regizor(self,n):
        self.__regizor=n
    def set_durata(self,n):
        self.__durata=n
    def set_gen(self,n):
        self.__gen=n
    def get_titlu(self):
        return self.__titlu
    def get_regizor(self):
        return self.__regizor
    def get_durata(self):
        return self.__durata
    def get_gen(self):
        return self.__gen
    def __str__(self):
        return f"{self.__titlu},{self.__regizor},{self.__gen},{self.__durata}"

def test_domeniu():
    piesa=Piesa("Doi","Pop","Drama",3)
    assert piesa.get_titlu()=="Doi"
    assert piesa.get_regizor()=="Pop"
    assert piesa.get_durata()==3
    piesa.set_gen("comedie")
    assert piesa.get_gen()=="comedie"
test_domeniu()