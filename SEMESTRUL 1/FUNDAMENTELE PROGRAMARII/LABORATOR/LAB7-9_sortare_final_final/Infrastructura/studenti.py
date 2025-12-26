from Exceptii.repo_error import RepoError
from Domeniu.studenti import Student
class StudentRepository:

    def __init__(self):
        self._totistudentii = {}

    def add_student(self,student):
        """
                adauga elementul laborator din parametru daca nu exista deja un element cu acelasi id
                :param student:entitate de tip laborator
                :return: exception daca exista deja un element cu id-ul respectiv
                """
        id_student = student.get_id_student()
        if id_student in self._totistudentii:
            raise RepoError("id existent!\n")
        self._totistudentii[id_student] = student

    def stergere_student(self, id_student):
        """
                sterge un element daca se afla numarul in lista
                :param id_student: int
                """
        for key in list(self._totistudentii.keys()):
            if self._totistudentii[key].get_id_student() == id_student:
                del self._totistudentii[key]
                return

    def cauta_elem(self,id_student):
        """
                cauta un element dupa id
                :param id_student: int
                :return: 1 daca este gasit 0 altfel
                """
        for key in list(self._totistudentii.keys()):
            if self._totistudentii[key].get_id_student()==id_student:
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
            for key in list(self._totistudentii.keys()):
                if self._totistudentii[key].get_id_student() == id_student:
                    self._totistudentii[key].set_nume(nume)
                    self._totistudentii[key].set_grup(grupa)
        else:
            raise RepoError("nu exista id!\n")

    def cauta_id(self, id):
        """
        cauta in lista un om dupa id
        :param id: id
        :return: studentul din lista daca se afla altfel exception
        """
        if self.cauta_elem(id) == 1:
            for key in list(self._totistudentii.keys()):
                if self._totistudentii[key].get_id_student() == id:
                    return self._totistudentii[key]
        else:
            raise RepoError("nu exista id!\n")

    def get_all(self):
        """
                :return: lista totistudentii
                """
        return [self._totistudentii[x] for x in self._totistudentii.keys()]

class FileRepoStudenti(StudentRepository):
    def __init__(self, cale_fisier):
        StudentRepository.__init__(self)
        self.__cale_fisier = cale_fisier

    def __read_all_studenti_from_file(self):
        """citeste elementele din fisier si le introduce in dictionar"""
        with open(self.__cale_fisier, "r") as f:
            self._totistudentii.clear()
            lines = f.readlines()
            for line in lines:
                 if line != "":
                    parts = line.split(",")
                    if len(parts)==3:
                        id_student = int(parts[0])
                        nume = parts[1]
                        valoare = int(parts[2])
                        student = Student(id_student, nume, valoare)
                        self._totistudentii[id_student] = student

    def __write_all_studenti_to_file(self):
        """introduce elementele din dictionar in fisier"""
        with open(self.__cale_fisier, "w") as f:
            for id_student in self._totistudentii:
                f.write(str(self._totistudentii[id_student]) + "\n")

    def add_student(self, student):
        """

                citeste elemente din fisier , apeleaza add_student si incarca in fisier
                :param student:entitate de tip student
                :return: exception daca exista deja un element cu id-ul respectiv
        """
        self.__read_all_studenti_from_file()
        StudentRepository.add_student(self, student)
        self.__write_all_studenti_to_file()

    def cauta_elem(self,id_student):
        """
        citeste si fisier si cauta elementul in lista
        :param id_student: entitate de tip student
        :return:
        """
        self.__read_all_studenti_from_file()
        for key in list(self._totistudentii.keys()):
            if self._totistudentii[key].get_id_student()==id_student:
                return 1
        return 0
    def cauta_id(self, id):
        """
        citeste si cauta dupa id
        :param id: atribut de tip student
        :return:
        """
        #COMPLEXITY Theta(n)
        # Best case (BC): cand elementul cu id nu exista si se arunca exceptie => Theta(1)
        # Worst case (WC): cand exista elementul cu id si este ultimul in lista => se parcurge de n ori
        #                  Theta(n)
        # Average case (AC): cand exista elementul si se parcurge forul (1+2+..+n)/n=(n+1)/2 => Theta(n)

        # Overall complexity: Theta(n)
        self.__read_all_studenti_from_file()
        if self.cauta_elem(id) == 1:
            for key in list(self._totistudentii.keys()):
                if self._totistudentii[key].get_id_student() == id:
                    return self._totistudentii[key]
        else:
            raise RepoError("nu exista id!\n")
    def modifica(self,student):
        """
        citeste din fisier si modifica entitatea student
        :param student: entitate student
        :return: lista modificata si incarca in fisier
        """
        self.__read_all_studenti_from_file()
        id_student = student.get_id_student()
        nume = student.get_nume()
        grupa = student.get_grup()
        if self.cauta_elem(id_student)==1:
            for key in list(self._totistudentii.keys()):
                if self._totistudentii[key].get_id_student() == id_student:
                    self._totistudentii[key].set_nume(nume)
                    self._totistudentii[key].set_grup(grupa)
        else:
            raise RepoError("nu exista id!\n")
        self.__write_all_studenti_to_file()

    def stergere_student(self, id_student):
        """
        citeste din fisier si sterge id_student
        :param id_student: entitate de tip student
        :return: incarca in fisier noua lista
        """
        # COMPLEXITY Theta(n)
        # Best case (BC): cand elementul cu id care trebuie sters se afla pe prima poz => Theta(1)
        # Worst case (WC): cand exista elementul cu id si este ultimul in lista sau nu exista => se parcurge de n ori
        #                  Theta(n)
        # Average case (AC): cand exista elementul si se parcurge forul (1+2+..+n)/n=(n+1)/2 => Theta(n)

        # Overall complexity: Theta(n)
        self.__read_all_studenti_from_file()
        for key in list(self._totistudentii.keys()):
            if self._totistudentii[key].get_id_student() == id_student:
                del self._totistudentii[key]
        self.__write_all_studenti_to_file()

    def get_all(self):
        """citeste din fisier si returneaza dictionarul"""
        self.__read_all_studenti_from_file()
        return StudentRepository.get_all(self)


