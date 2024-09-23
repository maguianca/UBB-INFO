
from Domeniu.laborator import Laborator
#from Domeniu import Student
#from Validare import ValidatorStudent

class LaboratoareBusiness:

    def __init__(self,repo_laborator,validator_laborator):
        self.__repo_laborator = repo_laborator
        self.__validator_laborator = validator_laborator

    def add_laborator(self,numar,descriere,deadline):
        """
        formateaza elementul student dupa numar,descriere,deadline
        valideaza elementul
        adauga in lista
        :param numar: int
        :param descriere: string
        :param deadline:string
        """
        laborator = Laborator(numar,descriere,deadline)
        self.__validator_laborator.valideaza_laborator(laborator)
        self.__repo_laborator.add_laborator(laborator)
    def modifica_laborator(self,numar,descriere,deadline):
        """
        formateaza elementul student dupa numar,descriere,deadline
        valideaza elementul
        modifica in lista
        :param numar: int
        :param descriere: string
        :param deadline: string
        """
        laborator=Laborator(numar,descriere,deadline)
        self.__validator_laborator.valideaza_laborator(laborator)
        self.__repo_laborator.modifica(laborator)
    def cauta_laborator(self,numar):
        """
        cauta in lista lab dupa nr
        valideaza numar
        :param numar:numar
        """
        self.__validator_laborator.valideaza_numar(numar)
        return self.__repo_laborator.cauta_numar(numar)
    def stergere_laborator(self,numar):
        """
        valideaza numar
        sterge elementul cu numar respectiv
        :param numar: int
        """
        self.__validator_laborator.valideaza_numar(numar)
        self.__repo_laborator.stergere_laborator(numar)
    def get_all_laboratoare(self):
        """
        apeleaza functia din repository care returneaza lista
        :return:
        """
        return self.__repo_laborator.get_all()