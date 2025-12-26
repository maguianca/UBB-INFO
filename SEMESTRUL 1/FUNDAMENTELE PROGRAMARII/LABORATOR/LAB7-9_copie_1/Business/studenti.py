
from Domeniu.studenti import Student
#from Domeniu import Student
#from Validare import ValidatorStudent

class StudentiBusiness:

    def __init__(self,repo_studenti,validator_studenti):
        self.__repo_studenti = repo_studenti
        self.__validator_studenti = validator_studenti

    def add_student(self,id_student,nume):
        student = Student(id_student,nume)
        self.__validator_studenti.valideaza_student(student)
        self.__repo_studenti.add_student(student)
    def modifica_student(self,id_student,nume):
        student=Student(id_student,nume)
        self.__validator_studenti.valideaza_student(student)
        self.__repo_studenti.modifica(student)
    def stergere_student(self,id_student):
        self.__validator_studenti.valideaza_id(id_student)
        self.__repo_studenti.stergere_student(id_student)
    def get_all_studenti(self):
        return self.__repo_studenti.get_all()