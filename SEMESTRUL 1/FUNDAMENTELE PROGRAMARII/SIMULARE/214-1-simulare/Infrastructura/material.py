from Domeniu.material import Material
class RepoMaterial:
    def __init__(self):
        self._materiale={}

    def get_all(self):
        return[self._materiale[id] for id in self._materiale.keys()]
    def modificare(self,obiect):
        cod=obiect.get_cod()
        if cod not in self._materiale.keys():
            raise Exception("cod negasit")
        self._materiale[cod]=obiect
    def cautare(self,cod):
        if cod not in self._materiale.keys():
            raise Exception("cod negasit")
        return self._materiale[cod]

class FileRepoMaterial(RepoMaterial):
    def __init__(self,cale_fisier,salvare):
        self.__cale_fisier=cale_fisier
        self.__salvare=salvare
        RepoMaterial.__init__(self)

    def __read_all_from_file(self):
        with open(self.__cale_fisier,"r") as f:
            self._materiale.clear()
            lines=f.readlines()
            for line in lines:
                if line!="":
                    parts=line.split(",")
                    if len(parts)==4:
                        cod=int(parts[0])
                        denumire=parts[1]
                        cant=int(parts[2])
                        pret=int(parts[3])
                        x=Material(cod,denumire,cant,pret)
                        self._materiale[cod]=x
    def __write_all_from_file(self):
        with open(self.__cale_fisier,"w")as f:
            for id in self._materiale:
                f.write(str(self._materiale[id])+"\n")

    def __append(self,entitate):
        with open(self.__salvare,"a") as f:
            f.write(str(entitate)+"\n")
    def adaugare(self,entitate):
        self.__append(entitate)
    def cautare(self,cod):
        self.__read_all_from_file()
        return RepoMaterial.cautare(self,cod)

    def golire(self):
        with open(self.__salvare,"w") as f:
            f.write("")
    def get_all(self):
        self.__read_all_from_file()
        return RepoMaterial.get_all(self)
    def modificare(self,obiect):
        self.__read_all_from_file()
        RepoMaterial.modificare(self,obiect)
        self.__write_all_from_file()
    def __len__(self):
        return len(self._materiale)
def test():
    file="C:\\214-1-simulare\\Data\\test1.txt"
    salvare="C:\\214-1-simulare\\Data\\test_salvare.txt"
    repo=FileRepoMaterial(file,salvare)
    x=Material(1,"ciment",100,250)
    repo.golire()
    repo.adaugare(x)
    assert len(repo.get_all())==3
    y=Material(1,"cim",90,500)
    repo.modificare(y)
    assert repo.cautare(1)==y

test()
