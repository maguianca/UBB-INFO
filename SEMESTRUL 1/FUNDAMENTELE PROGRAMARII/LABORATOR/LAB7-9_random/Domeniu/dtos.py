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
