from Domeniu.emisiune import Emisiune
class RepoEmisiune:
    def __init__(self):
        self._emisiuni={}
    def stergere(self,id):
        if id in self._emisiuni.keys():
            del self._emisiuni[id]
        else:
            raise Exception("id inexistent\n")
    def get_all(self):
        return [self._emisiuni[id] for id in self._emisiuni.keys()]
    def modificare(self,emisiune):
        id=emisiune.get_id()
        descriere=emisiune.get_descriere()
        durata=emisiune.get_durata()
        if id not in self._emisiuni.keys():
            raise Exception("id inexistent\n")
        else:
            self._emisiuni[id].set_descriere(descriere)
            self._emisiuni[id].set_durata(durata)


class FileRepoEmisiune:
    def __init__(self,cale_fisier):
        RepoEmisiune.__init__(self)
        self.__cale_fisier=cale_fisier
    def __read_all_files(self):
        index=1
        with open(self.__cale_fisier,'r')as f:
            lines=f.readlines()
            for line in lines:
                 if line!="":
                     parts=line.split(",")
                     if len(parts)==4:
                         nume=parts[0]
                         tip=parts[1]
                         durata=int(parts[2])
                         descriere=parts[3]
                         x=Emisiune(nume,tip,durata,descriere)
                         x.set_id(index)
                         self._emisiuni[index]=x
                         index=index+1
    def __write_all_files(self):
        with open(self.__cale_fisier,"w")as f:
            for id in self._emisiuni:
                f.write(str(self._emisiuni[id])+"\n")
    def stergere(self,id):
        self.__read_all_files()
        RepoEmisiune.stergere(self,id)
        self.__write_all_files()
    def get_all(self):
        self.__read_all_files()
        return RepoEmisiune.get_all(self)
    def modificare(self,emisiune):
        self.__read_all_files()
        RepoEmisiune.modificare(self,emisiune)
        self.__write_all_files()



