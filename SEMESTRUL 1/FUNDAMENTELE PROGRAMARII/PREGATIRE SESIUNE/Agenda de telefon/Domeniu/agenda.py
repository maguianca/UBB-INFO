class Contact:
    def __init__(self,id,nume,nrtel,grup):
        self.__nume=nume
        self.__id=id
        self.__nrtel=nrtel
        self.__grup=grup
    def get_nume(self):
        return self.__nume
    def get_id(self):
        return self.__id
    def get_nrtel(self):
        return self.__nrtel
    def get_grup(self):
        return self.__grup
    def set_nume(self,n):
        self.__nume=n
    def set_id(self,n):
        self.__id=n
    def set_nrtel(self,n):
        self.__nrtel=n
    def set_grup(self,n):
        self.__grup=n
    def __str__(self):
        return f"{self.__id},{self.__nume},{self.__nrtel},{self.__grup}"
class DTO:
    def __init__(self,nume,nrtel):
        self.__nume=nume
        self.__nrtel=nrtel
    def get_nume(self):
        return self.__nume

    def get_nrtel(self):
        return self.__nrtel

    def __str__(self):
        return f"{self.__nume},{self.__nrtel}"

def test_domeniu():
    contact=Contact("1","John","01273","Familie")
    assert contact.get_nume()=="John"
    assert contact.get_id()=="1"
    assert contact.get_grup()=="Familie"
    contact.set_nume("Ion")
    contact.set_nrtel("0123456789")
    assert contact.get_nume()=="Ion"
    assert contact.get_nrtel()=="0123456789"
test_domeniu()