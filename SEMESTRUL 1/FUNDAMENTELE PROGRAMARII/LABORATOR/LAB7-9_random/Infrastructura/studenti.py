class StudentRepository:

    def __init__(self):
        self.__totistudentii = {}

    def add_student(self,student):
        """
                adauga elementul laborator din parametru daca nu exista deja un element cu acelasi id
                :param student:entitate de tip laborator
                :return: exception daca exista deja un element cu id-ul respectiv
                """
        id_student = student.get_id_student()
        if id_student in self.__totistudentii:
            raise Exception("id existent!\n")
        self.__totistudentii[id_student] = student

    def stergere_student(self, id_student):
        """
                sterge un element daca se afla numarul in lista
                :param id_student: int
                """
        for key in list(self.__totistudentii.keys()):
            if self.__totistudentii[key].get_id_student() == id_student:
                del self.__totistudentii[key]
                return

    def cauta_elem(self,id_student):
        """
                cauta un element dupa id
                :param id_student: int
                :return: 1 daca este gasit 0 altfel
                """
        for key in list(self.__totistudentii.keys()):
            if self.__totistudentii[key].get_id_student()==id_student:
                return 1
        return 0

    def modifica(self,student):
        """
                modifica elementul din lista care are acelasi id_student cu student si inlocuieste si restul stributelor student
                :param student:entitate de tip student
                :return:exception daca nu exista elementul cu acelasi id ca si student
                """
        id_student=student.get_id_student()
        nume=student.get_nume()
        grupa=student.get_grup()
        if self.cauta_elem(id_student)==1:
            for key in list(self.__totistudentii.keys()):
                if self.__totistudentii[key].get_id_student() == id_student:
                    self.__totistudentii[key].set_nume(nume)
                    self.__totistudentii[key].set_grup(grupa)
        else:
            raise Exception("nu exista id!\n")

    def cauta_id(self, id):
        """
        cauta in lista un om dupa id
        :param id: id
        :return: studentul din lista daca se afla altfel exception
        """
        if self.cauta_elem(id) == 1:
            for key in list(self.__totistudentii.keys()):
                if self.__totistudentii[key].get_id_student() == id:
                    return self.__totistudentii[key]
        else:
            raise Exception("nu exista id!\n")

    def get_all(self):
        """
                :return: lista totistudentii
                """
        return [self.__totistudentii[x] for x in self.__totistudentii.keys()]