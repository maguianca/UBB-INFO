from Exceptii.repo_error import RepoError
from Domeniu.note import Note
from Domeniu.studenti import Student
from Domeniu.laborator import Laborator
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
    def adaugare_nota(self,nota,n):
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
                    if len(parts)==7:
                        id_student = int(parts[0])
                        nume=parts[1]
                        grup=int(parts[2])
                        id_laborator = parts[3]
                        desc=parts[4]
                        data=parts[5]
                        nota = float(parts[6])
                        student = Student(id_student, nume, grup)
                        laborator=Laborator(id_laborator,desc,data)
                        nota=Note(student,laborator,nota)
                        self._toatenotele.append(nota)

    def __write_all_studenti_to_file(self):
        with open(self.__cale_fisier, "w") as f:
            for nota in self._toatenotele:
                #f.write(str(nota) + "\n")
                f.write(f"{nota.get_student()},  {nota.get_laborator()},  {nota.get_nota()}\n")

   """def __write_all_studenti_to_file(self):
        note_list = NoteRepository.get_all(self)
        with open(self.__cale_fisier, 'w') as f:
            for note in note_list:
                note_string = str(note.get_student()) + ',' + str(note.get_laborator()) + ',' + str(
                    note.get_nota()) + '\n'
                f.write(note_string)"""
   def add_nota(self,nota):
        self.__read_all_studenti_from_file()
        n = self.cauta_nota(nota)
        if n is not None:
            raise Exception()
        self._toatenotele.append(nota)
        self.__write_all_studenti_to_file()

    def adaugare_nota(self,nota,n):
            """
            cauta in lista elementul nota si daca il gaseste ii modifica nota in n
            """
            self.__read_all_studenti_from_file()
            if self.cauta_nota(nota) is not None:
                    if self.cauta_nota(nota).get_nota()==0:
                        self.cauta_nota(nota).set_nota(n)
            else:
                raise RepoError("nu exista id!\n")
            self.__write_all_studenti_to_file()
    def get_all(self):
        self.__read_all_studenti_from_file()
        return NoteRepository.get_all(self)




    """def cauta_elem(self,numar):
        
        for key in list(self.__toatenotele.keys()):
            if self.__toatenotele[key].get_nota()==numar:
                return 1
        return 0
    def add_asignare(self,):

    def add_nota(self, nota):
        
        notare = nota.get_nota()
        if notare in self.__toatenotele:
            raise Exception("numar problema existent!\n")
        self.__toatenotele[notare] = nota

    def get_all(self):
        
        return [self.__toatenotele[x] for x in self.__toatenotele.keys()]
        """