
from Domeniu import *
class NoteRepository:

    def __init__(self):
        self.__toatenotele=[]

    def cauta_nota(self, nota):
        #note este de tipul NOTE
        for n in self.__toatenotele:
            if n == nota:
                return n
        return None

    def cautare_dupa_id(self,id_student,id_laborator):
        for i in self.__toatenotele:
            if i.get_student().get_id_student()==id_student and i.get_laborator().get_numar()==id_laborator:
                return i
        return None
    def add_nota(self,nota):
        n = self.cauta_nota(nota)
        if n is not None:
            raise Exception()
        self.__toatenotele.append(nota)
    def adaugare_nota(self,nota,n):
            """
            cauta in lista elementul nota si daca il gaseste ii modifica nota in n
            """
            if self.cauta_nota(nota) is not None:
                    if self.cauta_nota(nota).get_nota()==0:
                        self.cauta_nota(nota).set_nota(n)
            else:
                raise Exception("nu exista id!\n")
    def get_all(self):
        return self.__toatenotele
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