from Domeniu.mobilier import Mob,Mobilier
from Infrastructura.mobilier import FileMobilierRepository,MobilierRepository
class MobilierBusiness:
    def __init__(self,repo_mobilier):
        self.__repo_mobilier=repo_mobilier

    def cautare(self,tip):
        #self.__validator_mobilier.valideaza_tip(tip)
        if tip not in ["corp_iluminat", "spatiu_depozitare", "canapea", "scaun"]:
            raise Exception("tip invalid\n")
        #lista=self.__repo_mobilier.cautare(tip)
        lista=self.__repo_mobilier.get_all()
        list=[]
        for cod in lista:
            if cod.get_tip()==tip:
                list.append(cod)
        if list==[]:
            raise Exception("nu exista")
        else:
            return list

    def cumpara(self,cod,nr):
        lista = self.__repo_mobilier.cautare_dupa_cod(cod)
        if nr<0 or lista.get_stock()<nr:
            raise Exception("nr invalid/imposibil de cumparat")
        nume=lista.get_nume()
        pret=lista.get_pret()*nr
        stock=lista.get_stock()-nr
        dto=Mob(nume,stock,pret)
        self.__repo_mobilier.modifica(cod, stock)
        return dto

    def get_all(self):
        return self.__repo_mobilier.get_all()
def test_business():
    file=("C:\\215-simulare\\Teste\\test1.txt")
    repo=FileMobilierRepository(file)
    service=MobilierBusiness(repo)
    x1=Mobilier("C1","corp_iluminat","Lampa A",3,300.0)
    x2=Mobilier("C2","corp_iluminat","Veioza B",7,100.0)
    x3=Mobilier("C3","spatiu_depozitare","Dulap",9,1000.0)
    x4=Mobilier("C4","canapea","Alma",4,1500.0)
    assert service.cautare("canapea")==[x4]
    assert service.cautare("corp_iluminat")==[x1,x2]
    x=service.cumpara("C2",2)
    assert x.get_stock()==5
    assert x.get_pret()==200.0
    repo.modifica("C2",7)
test_business()