class RaportStudenti:
    def __init__(self, id_student, nume_student, nota):
        # fields: nume client, nume serial, no. stars
        self.__id_student=id_student
        self.__nume_student=nume_student
        self.__nota=nota

    def get_id(self):
        """
                :return:atributul id al clasei student
        """
        return self.__id_student

    def get_nume(self):
        """
                :return:atributul nume al clasei student
        """
        return self.__nume_student

    def get_nota(self):
        """
                :return:atributul nota
                """
        return self.__nota

    def set_id(self, value):
        """
        seteaza atributul id la value
        :param value: int
        """
        self.__id_student = value

    def set_nume(self, value):
        """
        seteaza atributul nume la value
        :param value=string
        """
        self.__nume_student = value

    def set_nota(self, value):
        """
        seteaza tributul nota la value
        :param value: float
        """
        self.__nota = value
class Stud:
    def __init__(self,nume_stud,nota):
        self.__nume_stud = nume_stud
        self.__nr_stud = 1
        self.__total_nota = nota
        self.__avg_nota = 0

    def get_nume(self):
        """
         :return:atributul nume
        """
        return self.__nume_stud

    def get_medie_nota(self):
        """
        :return:media notelor
        """
        return self.__avg_nota

    def get_numar_studenti(self):
        """ :return numar note"""
        return self.__nr_stud

    def inc_nr_stud(self):
        """ incrementeaza nr stud"""
        self.__nr_stud += 1

    def add_to_nota(self, value):
        """ face suma notelor"""
        self.__total_nota += value

    def medie(self):
        """calculul propriu-zis al mediei"""
        self.__avg_nota = self.__total_nota / self.__nr_stud

class Notare:
    def __init__(self, id_student, id_laborator, nota):
        # fields: nume client, nume serial, no. stars
        self.__id_student=id_student
        self.__id_laborator=id_laborator
        self.__nota=nota

    def get_id_student(self):
        """
                :return:atributul id al clasei student
        """
        return self.__id_student
    def get_id_laborator(self):
        """
                :return:atributul id al clasei student
        """
        return self.__id_laborator

    def get_nota(self):
        """
                :return:atributul nota
                """
        return self.__nota

    def set_id_student(self, value):
        """
        seteaza atributul id la value
        :param value: int
        """
        self.__id_student = value

    def set_id_laborator(self, value):
        """
        seteaza atributul id la value
        :param value: int
        """
        self.__id_laborator = value

    def set_nota(self, value):
        """
        seteaza tributul nota la value
        :param value: float
        """
        self.__nota = value

    def __str__(self):
        return f"{self.__id_student},{self.__id_laborator},{self.__nota}"