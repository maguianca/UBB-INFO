class Imobil:
    def __init__(self,id,adresa,pret,tip):
        self.__id=id
        self.__adresa=adresa
        self.__pret=pret
        self.__tip=tip
    def get_id(self):
        """methoda getter"""
        return self.__id
    def get_adresa(self):
        """methoda getter"""
        return self.__adresa
    def get_pret(self):
        """methoda getter"""
        return self.__pret
    def get_tip(self):
        """methoda getter"""
        return self.__tip
    def __str__(self):
        return f"{self.__id},{self.__adresa},{self.__pret},{self.__tip}"
    def __eq__(self,val):
        return val.get_id()==self.get_id()
class DTO:
    def __init__(self,id,adresa,pret):
        self.__id=id
        self.__adresa=adresa
        self.__pret=pret
        self.__comision=0
    def get_adresa(self):
        return self.__adresa
    def get_comision(self):
        return self.__comision
    def vanzare(self):
        self.__comision=2*self.__pret/100
    def inchiriere(self):
        self.__comision=self.__pret/2


def test():
    x=Imobil(4,"str.Mia",400,"vanzare")
    y = Imobil(4, "str.Mi", 400, "vanzare")
    assert x.get_id()==4
    assert x.get_tip()=="vanzare"
    assert x==y
    dto=DTO(1,"mia",1000)
    dto.inchiriere()
    assert dto.get_comision()==500
    dto1=DTO(1,"mia",1000)
    dto.vanzare()
    assert dto.get_comision()==20
test()