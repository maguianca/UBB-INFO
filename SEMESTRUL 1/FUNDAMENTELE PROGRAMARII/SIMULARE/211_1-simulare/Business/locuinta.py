from Exceptii.exceptii import BusinessError
from Infrastructura.locuinta import FileRepoLocuinta
from Domeniu.locuinta import Locuinta,DTO
class BusinessLocuinta:
    def __init__(self,repo):
        self.__repo=repo

    def filtrare_dupa_buget(self):
        lista=self.__repo.get_all()
        lista.sort(key=lambda x:x.get_pret())
        return lista

    def filtrare(self,buget,oras):
        if oras=="" or buget<=0:
            raise BusinessError("date invalide")
        lista=self.filtrare_dupa_buget()
        final=[]
        for x in lista:
            if x.get_oras()==oras and x.get_pret()<buget:
                final.append(x)
        if final==[]:
            raise Exception("lista goala")
        else:
            return final

    def cautare(self,id):
        if id<0:
            raise BusinessError("id invalid")
        return self.__repo.cautare_dupa_id(id)


    def inchiriere(self,id):
        lista=self.__repo.get_all()
        if id<0:
            raise BusinessError("id invalid")
        x=self.__repo.cautare_dupa_id(id)
        id=x.get_id()
        adresa=x.get_adresa()
        oras=x.get_oras()
        pret=x.get_pret()
        buget=x.get_garantie()
        dto=DTO(id,adresa,oras,pret,buget)
        dto.calculeaza()
        self.__repo.stergere(id)
        return dto

def test_sort():
    repo=FileRepoLocuinta("C:\\211_1-simulare\\Teste\\test_service1.txt")
    service=BusinessLocuinta(repo)
    repo.goleste_fisierul()
    assert len(repo.get_all())==0
    x = Locuinta(1, "dorobanti", "Cluj", 1700.0, 800.0)
    y = Locuinta(2, "dorobanti", "Cluj", 2000.0, 800.0)
    repo.adauga(y)
    repo.adauga(x)
    assert len(repo.get_all())==2
    lista=service.filtrare_dupa_buget()
    assert len(lista) == 2
    assert lista == [x, y]
    assert lista[0].get_id() == x.get_id()
    assert lista[1].get_id() == y.get_id()
    list=service.filtrare(2000,"Cluj")
    assert len(list)==1
    assert list==[x]
test_sort()