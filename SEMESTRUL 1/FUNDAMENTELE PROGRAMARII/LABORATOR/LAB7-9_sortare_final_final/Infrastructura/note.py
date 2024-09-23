from Exceptii.repo_error import RepoError
from Domeniu.note import Note
from Domeniu.studenti import Student
from Domeniu.laborator import Laborator
from Domeniu.dtos import Notare
class NoteRepository:

    def __init__(self):
        self._toatenotele=[]

    def cauta_nota(self, nota):
        #note este de tipul NOTE
        for n in self._toatenotele:
            if n == nota:
                return n
        return None

    def cautare_dupa_id(self,id_student,id_laborator):
        for i in self._toatenotele:
            if i.get_student().get_id_student()==id_student and i.get_laborator().get_numar()==id_laborator:
                return i
        return None
    def add_nota(self,nota):
        n = self.cauta_nota(nota)
        if n is not None:
            raise Exception()
        self._toatenotele.append(nota)
    def modifica_nota(self,nota,n):
            """
            cauta in lista elementul nota si daca il gaseste ii modifica nota in n
            """
            if self.cauta_nota(nota) is not None:
                    if self.cauta_nota(nota).get_nota()==0:
                        self.cauta_nota(nota).set_nota(n)
            else:
                raise RepoError("nu exista id!\n")
    def get_all(self):
        return self._toatenotele

class FileRepoNote(NoteRepository):
    def __init__(self, cale_fisier):
        NoteRepository.__init__(self)
        self.__cale_fisier = cale_fisier

    def __read_all_studenti_from_file(self):
        with open(self.__cale_fisier, "r") as f:
            self._toatenotele.clear()
            lines = f.readlines()
            for line in lines:
                 if line != "":
                    parts = line.split(",")
                    if len(parts) == 7:
                        id_student = int(parts[1])
                        nume = parts[2]
                        grup = int(parts[3])
                        id_laborator = parts[4]
                        desc = parts[5]
                        data = parts[6]
                        nota = float(parts[0])
                        student = Student(id_student, nume, grup)
                        laborator = Laborator(id_laborator, desc, data)
                        elem = Note(student, laborator, nota)
                        self._toatenotele.append(elem)

    """def __write_all_studenti_to_file(self):
        with open(self.__cale_fisier, "w") as f:
            for nota in self._toatenotele:
                #f.write(str(self._toatenotele) + "\n")
                f.write(f"{nota.get_student()},  {nota.get_laborator()},  {nota.get_nota()}\n")"""

    def __write_all_studenti_to_file(self):
        note_list =NoteRepository.get_all(self)
        with open(self.__cale_fisier, 'w') as f:
            for note in note_list:
                note_string = str(note.get_nota())+','+str(note.get_student()) +','+ str(note.get_laborator()) + '\n'
                f.write(note_string)

    def add_nota(self,nota):
        self.__read_all_studenti_from_file()
        NoteRepository.add_nota(self,nota)
        self.__write_all_studenti_to_file()

    """def modifica_nota(self,nota,n):
            self.__read_all_studenti_from_file()
            if nota is not None:
                    if nota.get_nota()==0:
                        nota.set_nota(n)
            else:
                raise RepoError("nu exista id!\n")
            self.__write_all_studenti_to_file()
            #if nota is None or nota.get_nota() != 0:
            #    raise RepoError("imposibil de atribuit nota\n")
            #if self.cauta_elem(id_student) == 1:
            #nota.set_nota(n)"""

    def modifica_nota(self, nota, n):
        """
        Cauta in lista elementul nota si daca il gaseste ii modifica nota in n.
        """
        studenti_list = NoteRepository.get_all(self)

        for student in studenti_list:
            if student == nota:
                if nota.get_nota() == 0:
                    nota.set_nota(n)
                    break
                else:
                    raise RepoError("operatie invalida\n")

        else:
            raise RepoError("nu este asignat laboratorul\n")
        self.__write_all_studenti_to_file()

    """def cauta_nota(self, nota):
        #note este de tipul NOTE
        self.__read_all_studenti_from_file()
        for n in self._toatenotele:
            if n == nota:
                return n
        return None

    def cautare_dupa_id(self,id_student,id_laborator):
        self.__read_all_studenti_from_file()
        #note_list = NoteRepository.get_all(self)
        for i in self._toatenotele:
            if i.get_student().get_id_student()==id_student and i.get_laborator().get_numar()==id_laborator:
                return i
        return None"""

    def get_all(self):
        self.__read_all_studenti_from_file()
        return NoteRepository.get_all(self)