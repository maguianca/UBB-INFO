bclass Pacienti:
    def __init__(self,id,nume,adresa,data):
        self.__id=id
        self.__nume=nume
        self.__adresa=adresa
        self.__data=data
    def get_id(self):
        """metoda getter-id"""
        return self.__id
    def get_nume(self):
        """metoda getter-nume"""
        return self.__nume
    def get_adresa(self):
        """metoda getter-adresa"""
        return self.__adresa
    def get_data(self):
        """metoda getter-data_nasterii"""
        return self.__data
    def __str__(self):
        """cum afiseaza in fisier dupa ce atribute"""
        return f"{self.__id},{self.__nume},{self.__adresa},{self.__data}"

class Internari:
    def __init__(self,cod,id,diagnostic,data_internare,data_externare):
        self.__cod=cod
        self.__id=id
        self.__diagnostic=diagnostic
        self.__data_internare=data_internare
        self.__data_externare=data_externare

    def get_id(self):
        """metoda getter-id"""
        return self.__id
    def get_cod(self):
        """metoda getter-cod"""
        return self.__cod
    def get_diagnostic(self):
        """metoda getter-diagnostic"""
        return self.__diagnostic

    def get_data_internare(self):
        """metoda getter-data internare"""
        return self.__data_internare
    def get_data_externare(self):
        """metoda gette-data externare"""
        return self.__data_externare

class DTO:
    def __init__(self,id,nume,data_nasterii):
        self.__id=id
        self.__nume=nume
        self.__data_nasterii=data_nasterii
        self.__internari=0

    def get_id(self):
        """metoda getter-id"""
        return self.__id

    def get_nume(self):
        """metoda getter-nume"""
        return self.__nume

    def get_data_nasterii(self):
        """metoda getter-data_nasterii"""
        return self.__data_nasterii
    def get_internari(self):
        """metoda getter-internari"""
        return self.__internari
    def inc(self):
        """numara de cate ori pacientul a fost internat """
        self.__internari=self.__internari+1



def test():
    x=Pacienti(1,"Anca","Gheorghe Doja","13.09.2000")
    assert x.get_id()==1
    assert x.get_adresa()=="Gheorghe Doja"
    assert x.get_nume()=="Anca"
    y=Internari("C1",1,"covid","13.10.2023","26.10.2023")
    assert y.get_id()==1
    assert y.get_cod()=="C1"
    dto=DTO(1,"Ema","21.10.2023")
    assert dto.get_nume()=="Ema"
    assert dto.get_id()==1
    dto.inc()
    assert dto.get_internari()==1
test()