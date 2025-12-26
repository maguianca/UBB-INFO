class LaboratorRepository:

    def __init__(self):
        self.__toatelaboratoarele={}
    def stergere_laborator(self, numar):
        """
        sterge un element daca se afla numarul in lista
        :param numar: int
        """
        for key in list(self.__toatelaboratoarele.keys()):
            if self.__toatelaboratoarele[key].get_numar() == numar:
                del self.__toatelaboratoarele[key]
                return
    def cauta_numar(self, numar):
        """
        cauta in lista un lab dupa numar
        :param id: id
        :return: lab din lista daca se afla altfel exception
        """
        if self.cauta_elem(numar) == 1:
            for key in list(self.__toatelaboratoarele.keys()):
                if self.__toatelaboratoarele[key].get_numar() == numar:
                    return self.__toatelaboratoarele[key]
        else:
            raise Exception("nu exista nr!\n")
    def cauta_elem(self,numar):
        """
        cauta un element dupa numar
        :param numar: int
        :return: 1 daca este gasit 0 altfel
        """
        for key in list(self.__toatelaboratoarele.keys()):
            if self.__toatelaboratoarele[key].get_numar()==numar:
                return 1
        return 0

    def modifica(self,laborator):
        """
        modifica elementul din lista care are acelasi numar cu laborator si inlocuieste si restul stributelor laborator
        :param laborator:entitate de tip laborator
        :return:exception daca nu exista elementul cu acelasi nr ca si laborator
        """
        numar=laborator.get_numar()
        descriere=laborator.get_descriere()
        deadline=laborator.get_deadline()
        if self.cauta_elem(numar)==1:
            for key in list(self.__toatelaboratoarele.keys()):
                if self.__toatelaboratoarele[key].get_numar() == numar:
                    self.__toatelaboratoarele[key].set_descriere(descriere)
                    self.__toatelaboratoarele[key].set_deadline(deadline)
        else:
            raise Exception("nu exista id!\n")


    def add_laborator(self, laborator):
        """
        adauga elementul laborator din parametru daca nu exista deja un element cu acelasi id
        :param laborator:entitate de tip laborator
        :return: exception daca exista deja un element cu id-ul respectiv
        """
        numar = laborator.get_numar()
        if numar in self.__toatelaboratoarele:
            raise Exception("numar problema existent!\n")
        self.__toatelaboratoarele[numar] = laborator

    def get_all(self):
        """
        :return: lista toatelaboratoarele
        """
        return [self.__toatelaboratoarele[x] for x in self.__toatelaboratoarele.keys()]