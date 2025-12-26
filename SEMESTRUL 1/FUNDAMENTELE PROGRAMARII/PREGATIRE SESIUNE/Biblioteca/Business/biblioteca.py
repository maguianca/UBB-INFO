from Domeniu.biblioteca import Carte
from Infrastructura.biblioteca import FileRepoBiblioteca
from Domeniu.validator import Validator
class BusinessBiblioteca:
    def __init__(self,repo,validator):
        self.__repo=repo
        self.__validator=validator
    def adaugare(self,id,titlu,autor,an):
        carte=Carte(id,titlu,autor,an)
        self.__validator.valideaza_carte(carte)
        self.__repo.adaugare(carte)
    def exista(self,numar,cif):
        while numar>0:
            cifra=numar%10
            numar=numar//10
            if cifra==cif:
                return True
        return False
    def stergere(self,cifra):
        lista=self.__repo.get_all()
        for el in lista:
            if self.exista(el.get_an(),cifra)==True:
                    self.__repo.stergere(el.get_id())
    def filtrare(self,sir="",numar=-1):
        lista=self.__repo.get_all()
        if sir=="" and numar==-1:
            return lista
        elif sir !="" and numar!=-1:
            lista1=[x for x in lista if x.get_an()<numar and sir in x.get_titlu()]
            return lista1
        elif sir!="" and numar==-1:
            lista2 = [x for x in lista if sir in x.get_titlu()]
            return lista2
        elif sir=="" and numar!=-1:
            lista3 = [x for x in lista if x.get_an() < numar]
            return lista3
    def undo(self,lista_undo):
        if len(lista_undo)<1:
            raise Exception("nu se mai poate face undo")
        else:
            for el in lista_undo[-1]:
                self.adaugare(el.get_id(),el.get_titlu(),el.get_autor(),el.get_an())
        lista_undo.pop(-1)
        return lista_undo
    def update_undo(self,lista_undo,cif):
        lista=self.__repo.get_all()
        lista1=[x for x in lista if self.exista(x.get_an(),cif)==True]
        copylist=[]
        for el in lista1:
            copylist.append(Carte(el.get_id(),el.get_titlu(),el.get_autor(),el.get_an()))
        lista_undo.append(copylist)
        return lista_undo
def test_business():
    repo = FileRepoBiblioteca("C:\Proiecte\Pregatire Sesiune\Biblioteca\data\\business.txt")
    repo.seteaza()
    repo.write_all_files()
    val=Validator()
    service=BusinessBiblioteca(repo,val)
    service.adaugare(1,"Ema","Petru",1999)
    service.adaugare(2,"Razboi","Vasile",1888)
    carte=Carte(2,"Razboi","Vasile",1888)
    assert repo.len()==2
    service.stergere(8)
    assert repo.len()==1
    assert service.exista(487665,4)==True
    assert service.exista(123,8)==False
    assert service.exista(0,0)==False
    try:
        service.adaugare(-2,"","",1999)
        assert False
    except Exception:
        assert True
    try:
        service.undo([])
    except Exception as ex:
        assert str(ex)=="nu se mai poate face undo"
    undo=[]
    service.adaugare(2, "Razboi", "Vasile", 1888)
    undo=service.update_undo(undo,8)
    service.stergere(8)
    assert repo.len()==1
    service.undo(undo)
    assert repo.len()==2
    lista_filtrare=service.filtrare("Ema",-1)
    assert len(lista_filtrare)==1
    lista_filtrare2=service.filtrare()
    assert len(lista_filtrare2)==2
test_business()