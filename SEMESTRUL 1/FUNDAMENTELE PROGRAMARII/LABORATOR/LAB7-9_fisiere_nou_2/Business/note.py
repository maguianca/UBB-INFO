from Infrastructura.studenti import StudentRepository
from Infrastructura.note import NoteRepository
from Infrastructura.laborator import LaboratorRepository
from Validare.note import ValidatorNote
from Domeniu.note import Note,RaportStudenti,Stud
#from Domeniu.dtos import RaportStudenti
#from Domeniu.dtos import Stud
from Domeniu.studenti import Student
from Domeniu.laborator import Laborator

class NoteBusiness:
    def __init__(self,repo_laborator,repo_studenti,repo_note,validator_note):
        self.__repo_laborator=repo_laborator
        self.__repo_studenti=repo_studenti
        self.__repo_note=repo_note
        self.__validator_note=validator_note

    def asignare_laborator(self,id_student,id_laborator):
        #test=Note(id_student,id_laborator,5)
        #lista = self.__repo_note.cauta_nota(id_student)
        lista = self.__repo_note.cautare_dupa_id(id_student,id_laborator)
        if lista is not None:
            raise Exception()
        student=self.__repo_studenti.cauta_id(id_student)
        laborator=self.__repo_laborator.cauta_numar(id_laborator)
        nota=Note(student,laborator,0)
        self.__repo_note.add_nota(nota)
        return nota
    def notare_laborator(self,id_student,id_laborator,nota):
        lista = self.__repo_note.cautare_dupa_id(id_student,id_laborator)
        if lista is None or lista.get_nota()!=0:
            raise Exception()
        self.__validator_note.valideaza_int(nota)
        lista.set_nota(nota)
        return lista
    def raport_problema(self,id_laborator):
        problema=self.__repo_laborator.cauta_numar(id_laborator)
        if problema is None:
            raise Exception("Laboratorul nu a fost gasit")
        notele=self.__repo_note.get_all()
        stud_note=[]
        for lab in notele:
            if lab.get_laborator().get_numar()==id_laborator and lab.get_nota()!=0:
                x1=lab.get_student().get_id_student()
                x2=lab.get_student().get_nume()
                x3=lab.get_nota()
                student=RaportStudenti(x1,x2,x3)
                stud_note.append(student)

        stud_note = sorted(stud_note, key=lambda x: (x.get_nume(),x.get_nota()), reverse=False)
        return stud_note

    def raport_corigenti(self):
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
        return self.__repo_note.get_all()
