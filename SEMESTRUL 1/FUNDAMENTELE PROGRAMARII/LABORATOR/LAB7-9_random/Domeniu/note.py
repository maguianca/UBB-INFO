from Domeniu.laborator import Laborator
from Domeniu.studenti import Student
class Note:
    def __init__(self,student,laborator,nota):
        self.__student = student
        self.__laborator =laborator
        self.__nota=nota

    def get_student(self):
        """
        :return:atributul id al clasei student
        """
        return self.__student

    def get_laborator(self):
        """
        :return:atributul nume al clasei student
        """
        return self.__laborator

    def get_nota(self):
        """
            :return:atributul grup al clasei student
        """
        return self.__nota

    def set_nota(self,new_nota):

        self.__nota=new_nota

    def set_laborator(self,new_laborator):

        self.__nota=new_laborator

    def set_student(self,new_student):

        self.__student=new_student

    def __eq__(self,other):
        """
        verifica daca atributele a doua entitati sunt egale;suprascrie
        :param other:student
        """
        if self.__student == other.__student and self.__laborator == other.__laborator :
            return True
        return False

    def __str__(self):
        
        return f"<<STUDENT:{self.__student}  >>   <<LABORATOR:{self.__laborator}  >>  <<NOTA:{self.__nota}>>"

    """
     return 'Student: [' + str(self.__student.get_id_student()) + '; ' + str(self.__student.get_nume()) + ']' + \
            'Laborator: [' + str(self.__laborator.get_numar()) + ';' + ']' + 'Nota: ' + str(
                self.__nota.get_nota())
    """
#DTOS
class RaportStudenti:
    def __init__(self, id_student, nume_student, nota):
        # fields: nume client, nume serial, no. stars
        self.__id_student=id_student
        self.__nume_student=nume_student
        self.__nota=nota

    def get_id(self):
        return self.__id_student

    def get_nume(self):
        return self.__nume_student

    def get_nota(self):
        return self.__nota

    def set_id(self, value):
        self.__id_student = value

    def set_nume(self, value):
        self.__nume_student = value

    def set_nota(self, value):
        self.__nota = value
class Stud:
    def __init__(self,nume_stud,nota):
        self.__nume_stud = nume_stud
        self.__nr_stud = 1
        self.__total_nota = nota
        self.__avg_nota = 0

    def get_nume(self):
        return self.__nume_stud

    def get_medie_nota(self):
        return self.__avg_nota

    def get_numar_studenti(self):
        return self.__nr_stud

    def inc_nr_stud(self):
        self.__nr_stud += 1

    def add_to_nota(self, value):
        self.__total_nota += value

    def medie(self):
        self.__avg_nota = self.__total_nota / self.__nr_stud
