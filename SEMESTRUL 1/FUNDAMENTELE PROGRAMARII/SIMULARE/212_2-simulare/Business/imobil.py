from Infrastructura.imobil import FileRepoImobil
from Domeniu.imobil import DTO
class BusinessImobil:
    def __init__(self,repo):
        self.__repo=repo
    def media(self,tip):
        if tip not in ["vanzare","inchiriere"]:
            return Exception("tip invalid")
        lista=self.__repo.get_all()
        pret=0
        nr=0
        media=0
        ok=0
        for x in lista:
            if x.get_tip().strip()==tip:
                pret=pret+int(x.get_pret())
                nr+=1
                ok=1
        if ok==1:
            media=pret/nr
        return media
    def inchiriere(self,id,pret):
        if id<0 or pret<0:
            raise Exception("date invalide")
        x=self.__repo.cautare(id)
        id=x.get_id()
        adresa=x.get_adresa()
        dto=DTO(id,adresa,pret)
        if x.get_tip()=="vanzare":
            dto.vanzare()
        else:
            dto.inchiriere()
        return dto




def test():
    file = "C:\\212_2-simulare\\Data\\test1.txt"
    repo = FileRepoImobil(file)
    service=BusinessImobil(repo)
    media=service.media("vanzare")
    d=service.inchiriere(1,2000)
    assert media==60600


test()