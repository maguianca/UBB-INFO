
class Student:
    def __init__(self,id_student,nume ):
        self.__id_student = id_student
        self.__nume = nume
        "self.__grup = grup"

    def get_id_student(self):
        return self.__id_student

    def get_nume(self):
        return self.__nume

    #def get_grup(self):
    #   return self.__grup

    def set_nume(self,new_nume):
        self.__nume=new_nume

    #def set_grup(self,new_grup):
    #    self.__grup=new_grup

    def __eq__(self,gigi):
        return self.__id_student == gigi.__id_student

    def __str__(self):
        return f"ID:{self.__id_student}  NUME:{self.__nume}  "