class Animale:
    def __init__(self, id, nume, data, locatie, tip, life):
        self.__id = id
        self.__nume = nume
        self.__data = data
        self.__locatie = locatie
        self.__tip = tip
        self.__life = life

    def get_id(self):
        "returneaza id"
        return self.__id

    def get_nume(self):
        """returneaza nume"""
        return self.__nume

    def get_data(self):
        """returneaza data"""
        return self.__data

    def get_locatie(self):
        """returneaza locatie"""
        return self.__locatie

    def get_tip(self):
        """returneaza tip"""
        return self.__tip

    def get_life(self):
        """returneaza life span"""
        return self.__life

    def __str__(self):
        return f"{self.__id},{self.__nume},{self.__data},{self.__locatie},{self.__tip},{self.__life}"
class DTO:
    def __init__(self,tip,nume,data,durata):
        self.__tip=tip
        self.__nume=nume
        self.__durata=durata
        self.__data=data
        self.__medie=0
        self.__inc=1
        self.__ani=0

    def get_nume(self):
        """returneaza nume"""
        return self.__nume
    def get_data(self):
        """returneaza data"""
        return self.__data
    def get_tip(self):
        """returneaza tip"""
        return self.__tip
    def set_data(self,value):
        """returneaza data"""
        self.__data=value
    def get_durata(self):
        """returneaza durata viata"""
        return self.__durata
    def set_nume(self,val):
        """seteaza nume"""
        self.__nume=val
    def set_tip(self,val):
        """seteaza tip"""
        self.__tip=val
    def set_durata(self,val):
        """returneaza durata viata"""
        self.__durata = val
    def get_medie(self):
        """returneaza media"""
        return self.__medie
    def ani(self):
        """face total de ani al animalelor cu tipul respectiv"""
        self.__ani+=self.__durata
    def inc(self):
        """seteaza nr de ob cu un tip anume"""
        self.__inc+=1
    def medie(self):
        """face media """
        self.__medie=self.__ani/self.__inc



def test_DTO():
    dto=DTO("reptila","Cici","2020/1/1",10)
    lista=[]
    lista.append(dto)
    assert dto.get_tip()=="reptila"
    assert dto.get_nume()=="Cici"
    assert dto.get_durata()==10
    dto.inc()
    dto.ani()
    dto.medie()
    assert dto.get_medie()==5
def test_animale():
    x=Animale(1,"Tapi","2023/12/12","Romania","mammal",15)
    assert x.get_nume()=="Tapi"
    assert x.get_id()==1
    assert x.get_tip()=="mammal"
test_animale()
test_DTO()