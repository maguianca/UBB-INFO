
from Domeniu.laborator import Laborator
#from Domeniu import Student
#from Validare import ValidatorStudent

class LaboratoareBusiness:

    def __init__(self,repo_laborator,validator_laborator):
        self.__repo_laborator = repo_laborator
        self.__validator_laborator = validator_laborator

    def add_laborator(self,numar,descriere,deadline):
        laborator = Laborator(numar,descriere,deadline)
        self.__validator_laborator.valideaza_laborator(laborator)
        self.__repo_laborator.add_laborator(laborator)
    def modifica_laborator(self,numar,descriere,deadline):
        laborator=Laborator(numar,descriere,deadline)
        self.__validator_laborator.valideaza_laborator(laborator)
        self.__repo_laborator.modifica(laborator)
    def stergere_laborator(self,numar):
        self.__validator_laborator.valideaza_numar(numar)
        self.__repo_laborator.stergere_laborator(numar)
    def get_all_laboratoare(self):
        return self.__repo_laborator.get_all()