from Infrastructura.magazin import RepoMagazin
from Domeniu.magazin import Produs
class BusinessMagazin:
    def __init__(self,repo,validator):
        self.__repo_magazin=repo
        self.__validator=validator
    def add_produs(self,id,denumire,pret):
        prod=Produs(id,denumire,pret)
        self.__validator.valideaza_produs(prod)
        self.__repo_magazin.add_produs(prod)

    def exista_cifra(self, x, cifra):
        while x > 0:
            if x % 10 == cifra:
                return True
            x = x / 10
        return False
    def stergere_produs(self,cifra):
        lista=self.__repo_magazin.get_all()
        cnt=0
        for x in lista:
            id=x.get_id()
            if self.exista_cifra(id,cifra)==True:
                cnt=cnt+1
                self.__repo_magazin.stergere_produs(id)
        return cnt
    def filtrare(self,str = '',nr = -1):
        lista = self.__repo_magazin.get_all()
        if str != '' and nr > -1:
            lista_noua = [el for el in lista if str in el.get_denumire() and float(el.get_pret())<=float(nr)]
        elif str == '' and nr >-1:
            lista_noua = [el for el in lista if float(el.get_pret())<=float(nr)]
        elif str != '' and nr == -1:
            lista_noua = [el for el in lista if str in el.get_denumire()]
        else:
            lista_noua = lista

        return lista_noua

    def undo(self,undo):
        error=[]
        if len(undo)<1:
            error.append("Nu se mai poate face undo")
        else:
            for el in undo[-1]:
                self.add_produs(el.get_id(),el.get_denumire(),el.get_pret())
        if len(error)>0:
            raise ValueError(error)
        undo.pop(-1)
        return undo
    """ def update_undo(self,undo,cif):
        lista=self.__repo_magazin.get_all()
        lista=[el for el in lista if str(cif) in str(el.get_pret())]
        copylist=[]
        for el in lista:
            copylist.append(Produs(el.get_id(),el.get_denumire(),el.get_pret()))
        undo.append(copylist)
        return undo"""
    def update_undo(self, undo, cif):
        lista = self.__repo_magazin.get_all()
        lista = [el for el in lista if self.exista_cifra(el.get_id(),cif)==True]
        copylist = []
        for el in lista:
            copylist.append(Produs(el.get_id(), el.get_denumire(), el.get_pret()))
        undo.append(copylist)
        return undo

