from Exceptii.repo_error import RepoError
from Domeniu.laborator import Laborator
class LaboratorRepository:

    def __init__(self):
        self._toatelaboratoarele={}
    def stergere_laborator(self, numar):
        """
        sterge un element daca se afla numarul in lista
        :param numar: int
        """
        for key in list(self._toatelaboratoarele.keys()):
            if self._toatelaboratoarele[key].get_numar() == numar:
                del self._toatelaboratoarele[key]
                return
    def cauta_numar(self, numar):
        """
        cauta in lista un lab dupa numar
        :param id: id
        :return: lab din lista daca se afla altfel exception
        """
        if self.cauta_elem(numar) == 1:
            for key in list(self._toatelaboratoarele.keys()):
                if self._toatelaboratoarele[key].get_numar() == numar:
                    return self._toatelaboratoarele[key]
        else:
            raise RepoError("nu exista nr!\n")
    def cauta_elem(self,numar):
        """
        cauta un element dupa numar
        :param numar: int
        :return: 1 daca este gasit 0 altfel
        """
        for key in list(self._toatelaboratoarele.keys()):
            if self._toatelaboratoarele[key].get_numar()==numar:
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
            for key in list(self._toatelaboratoarele.keys()):
                if self._toatelaboratoarele[key].get_numar() == numar:
                    self._toatelaboratoarele[key].set_descriere(descriere)
                    self._toatelaboratoarele[key].set_deadline(deadline)
        else:
            raise RepoError("nu exista id!\n")


    def add_laborator(self, laborator):
        """
        adauga elementul laborator din parametru daca nu exista deja un element cu acelasi id
        :param laborator:entitate de tip laborator
        :return: exception daca exista deja un element cu id-ul respectiv
        """
        numar = laborator.get_numar()
        if numar in self._toatelaboratoarele:
            raise Exception("numar problema existent!\n")
        self._toatelaboratoarele[numar] = laborator

    def get_all(self):
        """
        :return: lista toatelaboratoarele
        """
        return [self._toatelaboratoarele[x] for x in self._toatelaboratoarele.keys()]
class FileRepoLaborator(LaboratorRepository):
    def __init__(self, cale_fisier):
        LaboratorRepository.__init__(self)
        self.__cale_fisier = cale_fisier

    def __read_all_laboratoare_from_file(self):
        """
        citeste elementele din fisier si le introduce in dictionar
        """
        with open(self.__cale_fisier, "r") as f:
            self._toatelaboratoarele.clear()
            lines = f.readlines()
            for line in lines:
                 if line != "":
                    parts = line.split(",")
                    if len(parts)==3:
                        id_laborator = parts[0]
                        descriere = parts[1]
                        data = parts[2]
                        laborator = Laborator(id_laborator, descriere, data)
                        self._toatelaboratoarele[id_laborator] = laborator

    def __write_all_laboratoare_to_file(self):
        """
        incarca lista in dictionar
        """
        with open(self.__cale_fisier, "w") as f:
            for id_laborator in self._toatelaboratoarele:
                f.write(str(self._toatelaboratoarele[id_laborator]) + "\n")

    def add_laborator(self, laborator):
        """

                citeste elemente din fisier , apeleaza add_laborator si incarca in fisier
                :param laborator:entitate de tip laborator
                :return: exception daca exista deja un element cu id-ul respectiv
        """
        self.__read_all_laboratoare_from_file()
        LaboratorRepository.add_laborator(self, laborator)
        self.__write_all_laboratoare_to_file()
    def cauta_numar(self, numar):
        """
        cauta in lista un lab dupa numar
        :param id: id
        :return: lab din lista daca se afla altfel exception
        """
        self.__read_all_laboratoare_from_file()
        if self.cauta_elem(numar) == 1:
            for key in list(self._toatelaboratoarele.keys()):
                if self._toatelaboratoarele[key].get_numar() == numar:
                    return self._toatelaboratoarele[key]
        else:
            raise RepoError("nu exista nr!\n")
    def cauta_elem(self,numar):
        """
        cauta un element dupa numar
        :param numar: int
        :return: 1 daca este gasit 0 altfel
        """
        self.__read_all_laboratoare_from_file()
        for key in list(self._toatelaboratoarele.keys()):
            if self._toatelaboratoarele[key].get_numar()==numar:
                return 1
        return 0

    def stergere_laborator(self, numar):
        """
        sterge un element daca se afla numarul in lista
        :param numar: int
        """
        self.__read_all_laboratoare_from_file()
        for key in list(self._toatelaboratoarele.keys()):
            if self._toatelaboratoarele[key].get_numar() == numar:
                del self._toatelaboratoarele[key]
        self.__write_all_laboratoare_to_file()

    def modifica(self, laborator):
        """
        modifica elementul din lista care are acelasi numar cu laborator si inlocuieste si restul stributelor laborator
        :param laborator:entitate de tip laborator
        :return:exception daca nu exista elementul cu acelasi nr ca si laborator
        """
        self.__read_all_laboratoare_from_file()
        numar = laborator.get_numar()
        descriere = laborator.get_descriere()
        deadline = laborator.get_deadline()
        if self.cauta_elem(numar) == 1:
            for key in list(self._toatelaboratoarele.keys()):
                if self._toatelaboratoarele[key].get_numar() == numar:
                    self._toatelaboratoarele[key].set_descriere(descriere)
                    self._toatelaboratoarele[key].set_deadline(deadline)
        else:
            raise RepoError("nu exista id!\n")
        self.__write_all_laboratoare_to_file()

    def get_all(self):
        """citeste elementele din fisier si le afiseaza"""
        self.__read_all_laboratoare_from_file()
        return LaboratorRepository.get_all(self)