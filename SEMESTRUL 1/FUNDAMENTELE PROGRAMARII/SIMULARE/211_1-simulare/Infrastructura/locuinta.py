from Exceptii.exceptii import RepoError
from Domeniu.locuinta import Locuinta
class RepoLocuinta:
    def __init__(self):
        self._locuinte={}

    def adauga(self,locuinta):
        id=locuinta.get_id()
        if id in self._locuinte:
            raise RepoError("id existent")
        self._locuinte[id]=locuinta


    def get_all(self):
        return[self._locuinte[id] for id in self._locuinte.keys()]
    def cautare_dupa_id(self,id):
        if id in self._locuinte.keys():
            return self._locuinte[id]
        else:
            raise RepoError("id negasit")
    def stergere(self,id):
        if id in self._locuinte.keys():
            del self._locuinte[id]
        else:
            raise RepoError("id negasit")

class FileRepoLocuinta(RepoLocuinta):
    def __init__(self,cale_fisier):
        self.__cale_fisier=cale_fisier
        RepoLocuinta.__init__(self)

    def __read_all_from_file(self):
        with open(self.__cale_fisier,"r") as f:
            self._locuinte.clear()
            lines=f.readlines()
            for line in lines:
                if line!="":
                    parts=line.split(",")
                    if len(parts)==5:
                        id=int(parts[0])
                        adresa=parts[1]
                        oras=parts[2]
                        pret=float(parts[3])
                        garantie=float(parts[4])
                        x=Locuinta(id,adresa,oras,pret,garantie)
                        self._locuinte[id]=x

    def __write_all_in_file(self):
        with open(self.__cale_fisier,"w") as f:
            for id in self._locuinte:
                f.write(str(self._locuinte[id])+"\n")

    def get_all(self):
        self.__read_all_from_file()
        return RepoLocuinta.get_all(self)
        #return[self._locuinte[id] for id in self._locuinte.keys()]

    def cautare_dupa_id(self,id):
        self.__read_all_from_file()
        if id in self._locuinte.keys():
            return self._locuinte[id]
        else:
            raise RepoError("id negasit")
    def goleste_fisierul(self):
        with open(self.__cale_fisier, "w") as f:
                f.write("")

    def __len__(self):
        return len(self._locuinte)

    def adauga(self, locuinta):
        self.__read_all_from_file()
        id = locuinta.get_id()
        if id in self._locuinte:
            raise RepoError("id existent")
        self._locuinte[id] = locuinta
        self.__write_all_in_file()

    def stergere(self,id):
        self.__read_all_from_file()
        if id in self._locuinte.keys():
            del self._locuinte[id]
        else:
            raise RepoError("id negasit")
        self.__write_all_in_file()


def test():
    file="C:\\211_1-simulare\\Teste\\test_repo.txt"
    repo=FileRepoLocuinta(file)
    x=Locuinta(1,"dorobanti","Cluj",1700,800)
    assert len(repo.get_all())==2
    assert repo.cautare_dupa_id(1).get_id()==x.get_id()
test()