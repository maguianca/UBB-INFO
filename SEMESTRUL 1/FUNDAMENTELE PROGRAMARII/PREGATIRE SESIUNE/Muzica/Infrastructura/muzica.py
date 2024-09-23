from Domeniu.muzica import Melodie
class RepoMuzica:
    def __init__(self):
        self._toatemelodiile={}
    def modificare(self,melodie):
        id=melodie.get_id()
        if id in self._toatemelodiile.keys():
            self._toatemelodiile[id].set_gen(melodie.get_gen())
            self._toatemelodiile[id].set_durata(melodie.get_durata())
        else:
            raise Exception("id inexistent")
    def get_all(self):
        return [self._toatemelodiile[id] for id in self._toatemelodiile.keys()]
    """def adauga(self,melodie):
        self._toatemelodiile[self.__index]=melodie
        self.__index+=1"""

class FileRepoMuzica:
    def __init__(self,cale_fisier):
         RepoMuzica.__init__(self)
         self.__cale_fisier=cale_fisier
         self.__index=1
    def __read_all_files(self):
        with open(self.__cale_fisier,"r")as f:
            self._toatemelodiile.clear()
            lines=f.readlines()
            for line in lines:
                if line!="":
                    parts=line.split(",")
                    if len(parts)==4:
                        titlu=parts[0]
                        artist=parts[1]
                        gen=parts[2]
                        durata=int(parts[3])
                        x=Melodie(titlu,artist,gen,durata)
                        x.set_id(self.__index)
                        self._toatemelodiile[self.__index]=x
                        self.__index+=1
    def __write_all_files(self):
        with open(self.__cale_fisier,"w") as f:
            for id in self._toatemelodiile.keys():
                f.write(str(self._toatemelodiile[id])+"\n")
    def modificare(self,melodie):
        self.__read_all_files()
        RepoMuzica.modificare(self,melodie)
        self.__write_all_files()
    def get_all(self):
        self.__read_all_files()
        return RepoMuzica.get_all(self)
    def adauga(self,melodie):
        self.__read_all_files()
        self._toatemelodiile[self.__index] = melodie
        self.__index += 1
        self.__write_all_files()