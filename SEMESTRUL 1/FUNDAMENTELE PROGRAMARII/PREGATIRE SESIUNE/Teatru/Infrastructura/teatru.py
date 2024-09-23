from Domeniu.teatru import Piesa
class RepoTeatru:
    def __init__(self):
        self._piese=[]
    def adaugare(self,piesa):
        self._piese.append(piesa)
    def get_all(self):
        return [x for x in self._piese]
    def modificare(self,piesa):
        ok=0
        for el in self._piese:
            if el.get_titlu()==piesa.get_titlu() and el.get_regizor()==piesa.get_regizor():
                ok=1
                el.set_gen(piesa.get_gen())
                el.set_durata(piesa.get_durata())
        if ok==0:
            raise Exception("nu exista piesa")

class FileRepoTeatru:
    def __init__(self,cale_fisier):
        RepoTeatru.__init__(self)
        self.__cale_fisier=cale_fisier
    def read_all_files(self):
        with open(self.__cale_fisier,"r")as f:
            self._piese.clear()
            lines=f.readlines()
            for line in lines:
                if line!="":
                    params=line.strip().split(",")
                    if len(params)==4:
                        titlu=params[0]
                        regizor=params[1]
                        gen=params[2]
                        durata=int(params[3])
                        piesa=Piesa(titlu,regizor,gen,durata)
                        self._piese.append(piesa)
    def write_all_files(self):
        with open(self.__cale_fisier,"w")as f:
            for el in self._piese:
                f.write(str(el)+"\n")
    def adaugare(self,piesa):
        self.read_all_files()
        RepoTeatru.adaugare(self,piesa)
        self.write_all_files()
    def len(self):
        return len(self._piese)
    def seteaza(self):
        self._piese=[]
    def get_all(self):
        self.read_all_files()
        return RepoTeatru.get_all(self)
    def modificare(self,piesa):
        self.read_all_files()
        RepoTeatru.modificare(self,piesa)
        self.write_all_files()
def test_repo():
    repo=FileRepoTeatru("C:\Proiecte\Pregatire Sesiune\Teatru\data\\repo.txt")
    repo.seteaza()
    repo.write_all_files()
    assert repo.len()==0
    piesa=Piesa("Nume","Pop","Drama",5)
    repo.adaugare(piesa)
    assert repo.len()==1
    lista=repo.get_all()
    assert len(lista)==1
    assert lista[0].get_titlu()=="Nume"
    piesa1 = Piesa("Nume", "Pop", "Satira", 2)
    repo.modificare(piesa1)
    lista1 = repo.get_all()
    assert lista1[0].get_gen() == "Satira"
    assert lista1[0].get_durata() == 2

test_repo()


