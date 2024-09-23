from Domeniu.imobil import Imobil

class RepoImobil:
    def __init__(self):
        self._imobil={}
    def get_all(self):
        return [self._imobil[id] for id in self._imobil.keys()]
    def cautare(self,id):
        if id not in self._imobil.keys():
            raise Exception("id negasit")
        return self._imobil[id]

class FileRepoImobil(RepoImobil):
    def __init__(self,cale_fisier):
        self.__cale_fisier=cale_fisier
        RepoImobil.__init__(self)
    def __read_all_file(self):
        with open(self.__cale_fisier,"r") as f:
            self._imobil.clear()
            lines=f.readlines()
            for line in lines:
                if line!="":
                    parts=line.split(",")
                    if len(parts)==4:
                        id=int(parts[0])
                        adresa=parts[1]
                        pret=int(parts[2])
                        tip=parts[3]
                        im=Imobil(id,adresa,pret,tip)
                        self._imobil[id]=im

    def __write_all_file(self):
        with open(self.__cale_fisier,"w") as f:
            for id in self._imobil.keys():
                f.write(str(self._imobil[id])+"\n")
    def get_all(self):
        self.__read_all_file()
        return RepoImobil.get_all(self)
    def __len__(self):
        return len(self._imobil)
    def cautare(self,id):
        self.__read_all_file()
        return RepoImobil.cautare(self,id)

def test():
    file="C:\\212_2-simulare\\Data\\test1.txt"
    repo=FileRepoImobil(file)
    assert len(repo.get_all())==3
    assert repo.cautare(1) is not None
test()