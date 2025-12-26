
class Student:
    def __init__(self,id_student,nume,grup):
        self.__id_student = id_student
        self.__nume = nume
        self.__grup = grup

    def get_id_student(self):
        """
        :return:atributul id al clasei student
        """
        return self.__id_student

    def get_nume(self):
        """
        :return:atributul nume al clasei student
        """
        return self.__nume

    def get_grup(self):
        """
            :return:atributul grup al clasei student
        """
        return self.__grup

    def set_nume(self,new_nume):
        """
        seteaza atributul nume al clasei student
        :param new_nume: string
        """
        self.__nume=new_nume

    def set_grup(self,new_grup):
        """
                seteaza atributul grup al clasei student
                :param new_nume: int
        """
        self.__grup=new_grup

    def __eq__(self,gigi):
        """
        verifica daca atributele a doua entitati sunt egale;suprascrie
        :param gigi:student
        """
        return self.__id_student == gigi.__id_student

    def __str__(self):
        """
        :return: afiseaza lista sub forma de id nume grupa
        """
        return f"ID:{self.__id_student}  NUME:{self.__nume}  GRUPA:{self.__grup}"