from Domeniu.eveniment import Eveniment
class RepoTime:
    def __init__(self):
        self._evenimente=[]
    def get_all(self):
        return [x for x in self._evenimente]
    def adaugare(self,data):
        self._evenimente.append(data)

class FileRepoTime:
    def __init__(self,cale_fisier):
        RepoTime.__init__(self)
        self.__cale_fisier=cale_fisier
    def read_all_files(self):
        with open(self.__cale_fisier,"r")as f:
            self._evenimente.clear()
            lines=f.readlines()
            for line in lines:
                if line!="":
                    params=line.strip().split(",")
                    if len(params)==3:
                        data=params[0]
                        ora=params[1]
                        descriere=params[2]
                        ev=Eveniment(data,ora,descriere)
                        self._evenimente.append(ev)
    def write_all_files(self):
        with open(self.__cale_fisier,"w") as f:
            for el in self._evenimente:
                f.write(str(el)+"\n")

    def get_all(self):
        self.read_all_files()
        return RepoTime.get_all(self)
    def adaugare(self,data):
        self.read_all_files()
        RepoTime.adaugare(self,data)
        self.write_all_files()