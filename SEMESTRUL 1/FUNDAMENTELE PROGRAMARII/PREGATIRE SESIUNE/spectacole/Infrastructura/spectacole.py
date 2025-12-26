from Domeniu.spectacole import Spectacol
class RepoSpectacole:
    def __init__(self):
        self._spectacole = []
    def adaugare(self,spectacol):
        self._spectacole.append(spectacol)
    def modificare(self,spectacol):
        ok=0
        for concert in self._spectacole:
            if concert.get_titlu()==spectacol.get_titlu() and concert.get_artist()==spectacol.get_artist():
                ok=1
                concert.set_gen(spectacol.get_gen())
                concert.set_durata(spectacol.get_durata())
        if ok==0:
            raise Exception("nu exista spectacol")

class FileRepoSpectacole:
    def __init__(self, cale_fisier):
        self.__cale_fisier = cale_fisier
        RepoSpectacole.__init__(self)
    def read_all_file(self):
        with open(self.__cale_fisier,'r')as f:
            self._spectacole.clear()
            lines=f.readlines()
            for line in lines:
                if line!="":
                    params=line.strip().split(",")
                    if len(params)==4:
                        titlu=params[0]
                        artist=params[1]
                        gen=params[2]
                        durata=int(params[3])
                        spectacol=Spectacol(titlu,artist,gen,durata)
                        self._spectacole.append(spectacol)
    def write_all_file(self):
        with open(self.__cale_fisier,"w")as f:
            for el in self._spectacole:
                f.write(str(el)+"\n")
    def adaugare(self,spectacol):
        self.read_all_file()
        RepoSpectacole.adaugare(self,spectacol)
        self.write_all_file()
    def modificare(self,spectacol):
        self.read_all_file()
        RepoSpectacole.modificare(self,spectacol)
        self.write_all_file()
