from Domeniu.baschet import Jucator
import random
class RepoBaschet:
    def __init__(self):
        self._jucatori=[]
    def adaugare(self,juc):
        self._jucatori.append(juc)
    def modificare(self,nume,prenume,inaltime):
        ok=0
        lista=list(self._jucatori)
        for el in list(self._jucatori):
            if el.get_nume()==nume and el.get_prenume()==prenume:
                el.set_inaltime(inaltime)
                ok=1
        if ok==0:
            raise Exception("nu exista jucator")
    def get_all(self):
        return [x for x in self._jucatori]
    def cautare(self,nume,prenume):
        for x in list(self._jucatori):
            if x.get_nume()==nume and x.get_prenume()==prenume:
                return True
        return False

class FileRepoBaschet:
    def __init__(self,cale_fisier):
        self.__cale_fisier=cale_fisier
        RepoBaschet.__init__(self)
    def read_all_files(self):
        with open(self.__cale_fisier,"r")as f:
            self._jucatori.clear()
            lines=f.readlines()
            for line in lines:
                if line!="":
                    params = line.strip().split(",")
                    #params=line.split(" ")
                    if len(params)==4:
                        nume=params[0]
                        prenume=params[1]
                        inaltime=int(params[2])
                        post=params[3]
                        juc=Jucator(nume,prenume,inaltime,post)
                        self._jucatori.append(juc)
    def write_all_files(self):
        with open(self.__cale_fisier,"w")as f:
            for juc in self._jucatori:
                f.write(str(juc)+"\n")
    def adaugare(self,jucator):
        self.read_all_files()
        RepoBaschet.adaugare(self,jucator)
        self.write_all_files()
    def len(self):
        return len(self._jucatori)
    def setare(self):
        self._jucatori=[]
    def modificare(self,nume,prenume,inaltime):
        self.read_all_files()
        RepoBaschet.modificare(self,nume,prenume,inaltime)
        self.write_all_files()
    def get_all(self):
        self.read_all_files()
        return RepoBaschet.get_all(self)
    def cautare(self,nume,prenume):
        self.read_all_files()
        return RepoBaschet.cautare(self,nume,prenume)
    def importa(self,fisier):
        lista=["Fundas","Pivot","Extrema"]
        cnt=0
        #"C:\Proiecte\Pregatire Sesiune\Antrenor de baschet\Data\\baschet.txt"
        with open(fisier,'r')as f:
            lines=f.readlines()
            for line in lines:
                if line!="":
                    params=line.strip().split(" ")
                    if len(params)==2:
                        nume=params[0]
                        prenume=params[1]
                        inaltime=random.randint(160,210)
                        post=random.choice(lista)
                        jucator=Jucator(nume,prenume,inaltime,post)
                        if self.cautare(nume,prenume) is not True:
                            cnt+=1
                            self.adaugare(jucator)
        return cnt

def test_repo():
    repo=FileRepoBaschet("C:\Proiecte\Pregatire Sesiune\Antrenor de baschet\Data\\test_repo.txt")
    repo.setare()
    repo.write_all_files()
    juc=Jucator("Michael","Jordan",205,"Pivot")
    repo.adaugare(juc)
    assert len(repo.get_all())==1
    lista=repo.get_all()
    assert lista[0].get_inaltime() == 205
    juc1 = Jucator("Michael", "Jordan", 200, "Pivot")
    repo.modificare("Michael","Jordan",200)
    assert repo.get_all()[0].get_inaltime()==200
    assert repo.cautare("Michael","Jordan") is True
    assert repo.len()==1
    repo.importa("C:\Proiecte\Pregatire Sesiune\Antrenor de baschet\Business\\baschet1.txt")
    repo.read_all_files()
    assert repo.len()==8
test_repo()

