class StudentRepository:

    def __init__(self):
        self.__totistudentii = {}

    def add_student(self,student):
        id_student = student.get_id_student()
        if id_student in self.__totistudentii:
            raise Exception("id existent!\n")
        self.__totistudentii[id_student] = student

    def stergere_student(self, id_student):
        for key in list(self.__totistudentii.keys()):
            if self.__totistudentii[key].get_id_student() == id_student:
                del self.__totistudentii[key]
                return

    def cauta_elem(self,id_student):
        for key in list(self.__totistudentii.keys()):
            if self.__totistudentii[key].get_id_student()==id_student:
                return 1
        return 0

    def modifica(self,student):
        id_student=student.get_id_student()
        nume=student.get_nume()
       # grupa=student.get_grup()
        if self.cauta_elem(id_student)==1:
            for key in list(self.__totistudentii.keys()):
                if self.__totistudentii[key].get_id_student() == id_student:
                    self.__totistudentii[key].set_nume(nume)
                   # self.__totistudentii[key].set_grup(grupa)
        else:
            raise Exception("nu exista id!\n")

    def get_all(self):
        return [self.__totistudentii[x] for x in self.__totistudentii.keys()]