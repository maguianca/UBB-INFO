from Infrastructura.studenti import StudentRepository
from Infrastructura.note import NoteRepository
from Infrastructura.laborator import LaboratorRepository
from Validare.note import ValidatorNote
from Domeniu.note import Note,RaportStudenti,Stud
#from Domeniu.dtos import RaportStudenti
#from Domeniu.dtos import Stud
from Domeniu.studenti import Student
from Domeniu.laborator import Laborator
from functools import cmp_to_key

class NoteBusiness:
   def __init__(self,repo_laborator,repo_studenti,repo_note,validator_note):
        self.__repo_laborator=repo_laborator
        self.__repo_studenti=repo_studenti
        self.__repo_note=repo_note
        self.__validator_note=validator_note

   def comb_sort_key(self, arr, key=lambda x: x,reverse=False,cmp=None):
        n = len(arr)
        gap = n
        shrink = 1.3
        swapped = True
        if reverse==False:
            while gap > 1 or swapped:
                gap = max(1, int(gap / shrink))
                swapped = False

                for i in range(n - gap):
                    if key(arr[i]) > key(arr[i + gap]):
                        if cmp != None:
                            if cmp(arr[i], arr[i + gap]):
                                arr[i], arr[i + gap] = arr[i + gap], arr[i]
                                swapped = True

                        else:
                            arr[i], arr[i + gap] = arr[i + gap], arr[i]
                            swapped = True
        else:
            while gap > 1 or swapped:
                gap = max(1, int(gap / shrink))
                swapped = False

                for i in range(n - gap):
                    if key(arr[i]) < key(arr[i + gap]):
                        if cmp!=None:
                            if cmp(arr[i],arr[i+gap]):
                                arr[i], arr[i + gap] = arr[i + gap], arr[i]
                                swapped = True

                        else:
                            arr[i], arr[i + gap] = arr[i + gap], arr[i]
                            swapped = True

        return arr

   """def comb_sort_key(self,arr, key=lambda x: x, reverse=False, cmp=None):
       n = len(arr)
       gap = n
       shrink = 1.3
       swapped = True

       while gap > 1 or swapped:
           gap = max(1, int(gap / shrink))
           swapped = False

           for i in range(n - gap):
               compare = cmp_to_key(cmp) if cmp else None

               if (not reverse and compare(key(arr[i]), key(arr[i + gap])) > 0) or \
                       (reverse and compare(key(arr[i]), key(arr[i + gap])) < 0):
                   arr[i], arr[i + gap] = arr[i + gap], arr[i]
                   swapped = True

       return arr"""

   def insertion_sort_key(self, arr, key=lambda x: x,reverse=False,cmp=None):
       if reverse==False:
            for i in range(1, len(arr)):
                aux = arr[i]
                j = i - 1
                if cmp is None:
                    while j >= 0 and key(aux) < key(arr[j]):
                        arr[j + 1] = arr[j]
                        j -= 1
                    arr[j + 1] = aux
                else:
                    while j >= 0 and key(aux) < key(arr[j]) and cmp(aux,arr[j]):
                        arr[j + 1] = arr[j]
                        j -= 1
                    arr[j + 1] = aux

            return arr
       else:
           for i in range(1, len(arr)):
               aux = arr[i]
               j = i - 1
               if cmp is None:
                   while j >= 0 and key(aux) > key(arr[j]):
                       arr[j + 1] = arr[j]
                       j -= 1
                   arr[j + 1] = aux
               else:
                   while j >= 0 and key(aux) > key(arr[j]) and cmp(aux, arr[j]):
                       arr[j + 1] = arr[j]
                       j -= 1
                   arr[j + 1] = aux


   def asignare_laborator(self,id_student,id_laborator):
        """
        asigneaza studentului cautat dupa id-student laboratorul cautat dupa id-laborator
        si noteaza asignarea prin nota 0
        :param id_student: id-ul studentului
        :param id_laborator: id-laborator
        :return:
        """
        #test=Note(id_student,id_laborator,5)
        #lista = self.__repo_note.cauta_nota(id_student)
        lista = self.__repo_note.cautare_dupa_id(id_student,id_laborator)
        if lista is not None:
            raise Exception("nu s-a gasit elementul sau elementul are deja nota")
        student=self.__repo_studenti.cauta_id(id_student)
        laborator=self.__repo_laborator.cauta_numar(id_laborator)
        nota=Note(student,laborator,0)
        self.__repo_note.add_nota(nota)
        return nota

   def notare_laborator(self, id_student, id_laborator, nota):
        """
        cauta elementul de tip nota cu id_student so id_laborator respectiv cu nota 0 si o
        modifica cu nota
        :param id_student: id-ul studentului
        :param id_laborator: id-ul laboratorului
        :param nota: int
        :return:
        """

        lista = self.__repo_note.cautare_dupa_id(id_student, id_laborator)
        if lista is None or lista.get_nota()!=0:
           raise Exception("nu s-a gasit elementul sau elementul are nota")
        #if lista.get_nota()!=0:
        #    raise Exception("nu are nota")
        self.__validator_note.valideaza_int(nota)
        #lista.set_nota(nota)
        self.__repo_note.modifica_nota(lista,nota)
        return lista

   def raport_problema(self,id_laborator):
        """
        cauta in lista de laboratoare, notele cu id laboratorului si creeaza o lista
        si o sorteaza

        :param id_laborator: id-laborator
        :return: lista cu entitati de tip note care au id-laborator
        """
        problema=self.__repo_laborator.cauta_numar(id_laborator)
        if problema is None:
            raise Exception("Laboratorul nu a fost gasit")
        notele=self.__repo_note.get_all()
        stud_note=[]
        for lab in notele:
            laborator=lab.get_laborator().get_numar()
            #print('id_lab:',laborator)
            if laborator==id_laborator and lab.get_nota()!=0:
                x1=lab.get_student().get_id_student()
                x2=lab.get_student().get_nume()
                x3=lab.get_nota()
                student=RaportStudenti(x1,x2,x3)
                stud_note.append(student)

        #stud_note = sorted(stud_note, key=lambda x: (x.get_nume(), x.get_nota()), reverse=False)
        lista_sortata = self.comb_sort_key(stud_note, key=lambda x: (x.get_nume(),x.get_nota()),reverse=False,cmp=comparare)
        return lista_sortata

   def raport_corigenti(self):
        """
        creaza o lista a studentilor si formeaza media tuturor notelor primite la laboratoare
        :return: lista cu studentii cu media notelor sub 5
        """
        #COMPLEXITY Theta(n) Cazurile Mediu/Favorabil,Defavorabil identice
        #Theta(n+m)-> Theta(n)
        lista_stud = self.__repo_note.get_all()
        stud = {}

        for lab in lista_stud:
            student_id = lab.get_student().get_id_student()
            if lab.get_nota()!=0:
                if student_id not in stud:
                    dto = Stud(lab.get_student().get_nume(), lab.get_nota())
                    stud[student_id] = dto
                else:
                    stud[student_id].inc_nr_stud()
                    stud[student_id].add_to_nota(lab.get_nota())

        for student_id, student in stud.items():
            student.medie()

        lista_corigenti = [student for student in stud.values() if student.get_medie_nota() < 5]

        return lista_corigenti

   def get_all(self):
        """ returneaza toate notele"""
        return self.__repo_note.get_all()

def comparare(a,b):
    if a.get_nume()>b.get_nume():
        return True
    elif a.get_nume()==b.get_nume() and a.get_nota()>b.get_nota():
        return True
    return False
