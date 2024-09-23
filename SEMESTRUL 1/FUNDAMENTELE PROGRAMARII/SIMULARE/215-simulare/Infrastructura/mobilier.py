from Domeniu.mobilier import Mobilier

class MobilierRepository():
    def __init__(self):
        self._mobilier={}
    def get_all(self):
        return [self._mobilier[cod] for cod in self._mobilier.keys()]
    def cautare(self,tip):
        cauta=[]
        for cod in self._mobilier:
            if self._mobilier[cod].get_tip()==tip:
                cauta.append(self._mobilier[cod])
        return cauta
    def modifica(self,cod,nr):
        if cod in self._mobilier.keys():
           # x = self._mobilier[cod].get_stock()
            self._mobilier[cod].set_stock(nr)
        else:
            raise Exception("nu exista cod\n")
    def cautare_dupa_cod(self,cod):
        if cod in self._mobilier.keys():
            return self._mobilier[cod]
        else:
            raise Exception("cod negasit")
class FileMobilierRepository(MobilierRepository):
    def __init__(self,cale_fisier):
        self.__cale_fisier=cale_fisier
        MobilierRepository.__init__(self)

    def __read_all_mobila_from_file(self):
        with open(self.__cale_fisier,"r") as f:
            self._mobilier.clear()
            lines=f.readlines()
            for line in lines:
                if line!="":
                    parts=line.split(",")
                    if len(parts)==5:
                        cod=parts[0]
                        tip=parts[1]
                        nume=parts[2]
                        stock=int(parts[3])
                        pret=float(parts[4])
                        obiect=Mobilier(cod,tip,nume,stock,pret)
                        self._mobilier[cod]=obiect
    def __write_all_mobila_to_file(self):
        with open(self.__cale_fisier,"w")as f:
            for cod in self._mobilier:
                f.write(str(self._mobilier[cod])+"\n")
    def __len__(self):
        return len(self._mobilier)

    def __goleste_fisier(self):
        with open(self.__cale_fisier,"w")as f:
            f.write("")

    def cautare(self,tip):
        self.__read_all_mobila_from_file()
        cauta = []
        for cod in self._mobilier:
            if self._mobilier[cod].get_tip() == tip:
                cauta.append(self._mobilier[cod])
        return cauta
    def modifica(self,cod,nr):
        self.__read_all_mobila_from_file()
        MobilierRepository.modifica(self,cod,nr)
        self.__write_all_mobila_to_file()

    def cautare_dupa_cod(self, cod):
         self.__read_all_mobila_from_file()
         if cod in self._mobilier.keys():
              return self._mobilier[cod]
         else:
            raise Exception("cod negasit")

    def get_all(self):
        self.__read_all_mobila_from_file()
        return MobilierRepository.get_all(self)


def teste_repo():
        file=("C:\\215-simulare\\Teste\\test.txt")
        repo=FileMobilierRepository(file)
        x=Mobilier("C1","corp_iluminat","Lampa A",3,300.0)
        assert len(repo)==0
        assert repo.cautare_dupa_cod("C1") is not None
        assert repo.cautare_dupa_cod("C1")==x
        y=repo.cautare_dupa_cod("C1")
        assert y.get_stock()==3
        repo.modifica("C1",2)
        assert repo.cautare_dupa_cod("C1").get_stock()==2
        repo.modifica("C1",3)
        assert repo.cautare_dupa_cod("C1").get_stock()==3
        assert len(repo.get_all())==1

teste_repo()