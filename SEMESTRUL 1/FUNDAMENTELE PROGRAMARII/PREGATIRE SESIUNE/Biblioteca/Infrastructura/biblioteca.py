from Domeniu.biblioteca import Carte
class RepoBiblioteca:
    def __init__(self):
        self._carti={}
    def adaugare(self,carte):
        id=carte.get_id()
        if id not in self._carti.keys():
            self._carti[id]=carte
        else:
            raise Exception("id existent")
    def stergere(self,id):
        if id not in self._carti.keys():
            raise Exception("id inexistent")
        else:
            del self._carti[id]
    def get_all(self):
        return [self._carti[id]for id in self._carti.keys()]
class FileRepoBiblioteca:
    def __init__(self,cale_fisier):
        self.__cale_fisier=cale_fisier
        RepoBiblioteca.__init__(self)
    def read_all_files(self):
        with open(self.__cale_fisier,"r")as f:
            self._carti.clear()
            lines=f.readlines()
            for line in lines:
                if line!="":
                    params=line.strip().split(",")
                    if len(params)==4:
                        id=int(params[0])
                        titlu=params[1]
                        autor=params[2]
                        an=int(params[3])
                        carte=Carte(id,titlu,autor,an)
                        self._carti[id]=carte
    def write_all_files(self):
        with open(self.__cale_fisier,"w")as f:
            for el in self._carti.keys():
                f.write(str(self._carti[el])+"\n")
    def adaugare(self,carte):
        self.read_all_files()
        RepoBiblioteca.adaugare(self,carte)
        self.write_all_files()
    def seteaza(self):
        self._carti={}
    def len(self):
        return len(self._carti)
    def get_all(self):
        self.read_all_files()
        return RepoBiblioteca.get_all(self)
    def stergere(self,id):
        self.read_all_files()
        RepoBiblioteca.stergere(self,id)
        self.write_all_files()
def test_repo():
    repo=FileRepoBiblioteca("C:\Proiecte\Pregatire Sesiune\Biblioteca\data\\repo.txt")
    repo.seteaza()
    repo.write_all_files()
    carte=Carte(12,"Ana","Pop Marcel",2000)
    repo.adaugare(carte)
    assert repo.len()==1
    try:
        repo.adaugare(carte)
    except Exception as ex:
        assert str(ex)=="id existent"
    repo.stergere(12)
    assert repo.len()==0
    try:
        repo.stergere(128947)
    except Exception as ex:
        assert str(ex)=="id inexistent"

test_repo()