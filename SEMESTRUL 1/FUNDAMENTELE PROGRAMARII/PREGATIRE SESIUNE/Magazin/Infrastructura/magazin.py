from Domeniu.magazin import Produs

class RepoMagazin:
    def __init__(self):
        self._produse={}

    def add_produs(self,produs):
        id=produs.get_id()
        if id in self._produse:
            raise Exception("id existent\n")
        self._produse[id]=produs
    def stergere_produs(self,id):
        for key in list(self._produse.keys()):
            if self._produse[key].get_id()==id:
                del self._produse[key]
                return
    def get_all(self):
        return[self._produse[id] for id in self._produse.keys()]

class FileRepoMagazin(RepoMagazin):
    def __init__(self,cale_fisier):
        RepoMagazin.__init__(self)
        self.__cale_fisier=cale_fisier

    def __read_all_produse_from_file(self):
        with open(self.__cale_fisier,"r") as f:
            self._produse.clear()
            lines=f.readlines()
            for line in lines:
                if line!="":
                    parts=line.split(",")
                    if len(parts)==3:
                        id=int(parts[0])
                        denumire=parts[1]
                        pret=float(parts[2])
                        x=Produs(id,denumire,pret)
                        self._produse[id]=x

    def __write_all_produse_to_file(self):
        with open(self.__cale_fisier,"w")as f:
            for id in self._produse:
                f.write(str(self._produse[id])+"\n")
    def add_produs(self,produs):
        self.__read_all_produse_from_file()
        RepoMagazin.add_produs(self,produs)
        self.__write_all_produse_to_file()
    def stergere_produs(self,id):
        self.__read_all_produse_from_file()
        RepoMagazin.stergere_produs(self,id)
        self.__write_all_produse_to_file()
    def get_all(self):
        self.__read_all_produse_from_file()
        return RepoMagazin.get_all(self)