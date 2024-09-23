import string

from Domeniu.studenti import Student
#from Domeniu import Student
#from Validare import ValidatorStudent
import random
class StudentiBusiness:

    def __init__(self,repo_studenti,validator_studenti):
        self.__repo_studenti = repo_studenti
        self.__validator_studenti = validator_studenti

    def add_student(self,id_student,nume,grup):
        """
        formateaza elementul student dupa id,nume,grup
        valideaza elementul
        adauga in lista
        :param id_student: int
        :param nume: string
        :param grup: int
        """
        student = Student(id_student,nume,grup)
        self.__validator_studenti.valideaza_student(student)
        self.__repo_studenti.add_student(student)
    def modifica_student(self,id_student,nume,grup):
        """
        formateaza elementul student dupa id,nume,grup
        valideaza elementul
        modifica in lista
        :param id_student: int
        :param nume: string
        :param grup: int
        """
        student=Student(id_student,nume,grup)
        self.__validator_studenti.valideaza_student(student)
        self.__repo_studenti.modifica(student)
    def stergere_student(self,id_student):
        """
            valideaza id
            sterge element dupa id
            :param id_student: int
                """
        self.__validator_studenti.valideaza_id(id_student)
        self.__repo_studenti.stergere_student(id_student)
    def cauta_student(self,id_student):
        """
        cauta in lista student dupa id
        valideaza id
        :param id_student:id
        """
        self.__validator_studenti.valideaza_id(id_student)
        return self.__repo_studenti.cauta_id(id_student)
    def generare_studenti(self,numar):
        """
        genereaza random id(1,100),nume din lista_nume,gruo(1,15)
        :param numar:int- de cate ori genereaza random
        """
        lista_nume=['Anca','Georgiana','Matei','Andrei','Mihai','Maria','Irina','Gigel','Angel','Elena']
        cnt=0
        random.seed(3)
        while cnt!=numar:
            id_nou=random.randint(1,max(100,numar))
            nume_nou=random.choice(lista_nume)
            grup_nou=random.randint(1,15)
            student=Student(id_nou,nume_nou,grup_nou)
            try:
                self.__validator_studenti.valideaza_student(student)
                self.__repo_studenti.add_student(student)
                cnt=cnt+1
            except:
                pass
    def get_all_studenti(self):
        """
        apeleaza functia din repository care returneaza lista
        """
        return self.__repo_studenti.get_all()