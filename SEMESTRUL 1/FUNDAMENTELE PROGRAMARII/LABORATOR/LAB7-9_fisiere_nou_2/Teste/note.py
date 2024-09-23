from Domeniu.note import Note
from Domeniu.studenti import Student
from Domeniu.laborator import Laborator
from Infrastructura.note import NoteRepository
from Validare.note import ValidatorNote
from Infrastructura.studenti import StudentRepository
from Infrastructura.laborator import LaboratorRepository
from Business.note import NoteBusiness
class TesteN:

    def __test_create_nota(self):
        student= Student(1, 'Anca', 20)
        laborator = Laborator('1_4', 'aplicatie', '12/12/2023')

        nota=Note(student,laborator,10)

        assert (nota.get_student() == student)
        assert (nota.get_laborator() == laborator)
        assert (nota.get_nota() == 10)

    def __test_equal_note(self):
        student = Student(1, 'Anca', 12)
        laborator = Laborator('1_5', 'app', 12/12/2025)

        nota1 = Note(student,laborator,9.5)
        nota2 = Note(student,laborator,8)
        assert (nota1==nota2)

        student2 = Student(6, 'Elena', 12)
        nota3 = Note(student2, laborator, 7.5)
        assert (nota3 != nota2)

    def __test_add_nota(self):
        student = Student(1, 'Anca', 12)
        laborator = Laborator('1_5', 'app', 12/12/2025)

        nota = Note(student, laborator, 9.5)

        repo = NoteRepository()
        repo.add_nota(nota)

        assert (len(repo.get_all()) == 1)
    def __test_adaugare_nota(self):
        student = Student(1, 'Anca', 12)
        laborator = Laborator('1_5', 'app', '12/12/2025')
        nota = Note(student, laborator, 0)
        test=Note(student,laborator,10)
        repo = NoteRepository()
        repo.add_nota(nota)
        assert nota.get_nota()==0
        repo.adaugare_nota(nota,10)
        assert nota.get_nota()==10
        assert (len(repo.get_all()) == 1)
        lista=repo.get_all()
        assert(type(lista)==list)
        #assert lista[0]==test and lista[0]==nota
        #assert nota.get_nota()==10
        assert lista[0].get_nota()==10

    def __test_valideaza_nota(self):
        student = Student(1, 'Anca', 12)
        laborator = Laborator('1_5', 'app', 12 / 12 / 2025)
        nota_buna=Note(student,laborator,8.5)
        nota_rea=Note(student,laborator,0.75)
        validator = ValidatorNote()
        validator.valideaza_note(nota_buna)
        try:
            validator.valideaza_note(nota_rea)
            assert False
        except Exception as ex:
            assert (str(ex) == "nota invalida <nota trb sa fie intre 1 si 10>!\n")
    def __test_asignare_laborator(self):
        student = Student(1, 'Anca', 12)
        laborator = Laborator('1_5', 'app', '12/12/2025')
        repo_studenti=StudentRepository()
        repo_laborator=LaboratorRepository()
        repo_studenti.add_student(student)
        repo_laborator.add_laborator(laborator)
        repo_note=NoteRepository()
        validator_note=ValidatorNote()
        business_note=NoteBusiness(repo_laborator,repo_studenti,repo_note,validator_note)
        nota=business_note.asignare_laborator(1,'1_5')
        assert nota.get_nota()==0
        assert nota.get_student()==student
        assert nota.get_laborator()==laborator
    def __test_asignare_nota_2(self):
        student = Student(1, 'Anca', 12)
        laborator = Laborator('1_5', 'app', '12/12/2025')
        nota=Note(student,laborator,5)
        repo_studenti = StudentRepository()
        repo_laborator = LaboratorRepository()
        repo_studenti.add_student(student)
        repo_laborator.add_laborator(laborator)
        repo_note = NoteRepository()
        validator_note = ValidatorNote()
        business_note = NoteBusiness(repo_laborator, repo_studenti, repo_note, validator_note)
        repo_note.add_nota(nota)
        try:
            ex = business_note.asignare_laborator(1, '1_5')
        except Exception as ex:
            print()
    def __test_notare_laborator(self):
        student = Student(1, 'Anca', 12)
        laborator = Laborator('1_5', 'app', '12/12/2025')
        nota = Note(student, laborator, 0)
        repo_studenti = StudentRepository()
        repo_laborator = LaboratorRepository()
        repo_studenti.add_student(student)
        repo_laborator.add_laborator(laborator)
        repo_note = NoteRepository()
        validator_note = ValidatorNote()
        business_note = NoteBusiness(repo_laborator, repo_studenti, repo_note, validator_note)
        repo_note.add_nota(nota)
        test=business_note.notare_laborator(1,'1_5',5)
        assert test.get_nota()==5
    def __test_cautare_dupa_id(self):
        student = Student(1, 'Anca', 12)
        laborator = Laborator('1_5', 'app', '12/12/2025')
        student1 = Student(2, 'ELena', 12)
        laborator1 = Laborator('1_6', 'app', '12/12/2025')
        repo_nota=NoteRepository()
        nota=Note(student,laborator,9)
        nota1=Note(student1,laborator1, 8)
        repo_nota.add_nota(nota)
        repo_nota.add_nota(nota1)
        i=repo_nota.cautare_dupa_id(1,'1_5')
        assert i.get_student().get_id_student()==1
        assert i.get_laborator().get_descriere()=='app'
    def __test_raport_problema(self):
        student = Student(1, 'Anca', 12)
        student1 = Student(2, 'Elena', 12)
        student2=Student(3,'Ema',10)
        student3=Student(4,'Ema',11)
        laborator = Laborator('1_5', 'app', '12/12/2025')
        laborator1 = Laborator('1_6', 'app', '12/12/2025')
        repo_studenti = StudentRepository()
        repo_laborator = LaboratorRepository()
        repo_studenti.add_student(student)
        repo_studenti.add_student(student1)
        repo_studenti.add_student(student2)
        repo_studenti.add_student(student3)
        repo_laborator.add_laborator(laborator)
        repo_laborator.add_laborator(laborator1)
        repo_note = NoteRepository()
        validator_note = ValidatorNote()
        business_note = NoteBusiness(repo_laborator, repo_studenti, repo_note, validator_note)
        nota5=business_note.asignare_laborator(4,'1_5')
        nota1=business_note.asignare_laborator(1,'1_5')
        nota2=business_note.asignare_laborator(1,'1_6')
        nota3=business_note.asignare_laborator(2,'1_5')
        nota4=business_note.asignare_laborator(3,'1_5')
        test4=business_note.notare_laborator(4,'1_5',8)
        test = business_note.notare_laborator(1, '1_5', 5)
        test1= business_note.notare_laborator(2,'1_5',10)
        test3=business_note.notare_laborator(3,'1_5',7)
        x=business_note.raport_problema('1_5')
        assert x[0].get_nume()=='Anca'
        assert x[1].get_nume()=='Elena'
        assert x[2].get_nume()=='Ema'
        assert x[3].get_nume()=='Ema'
        assert x[2].get_nota()==7
        assert x[3].get_nota()==8
    def __test_raport_corigenti(self):
        student = Student(1, 'Anca', 12)
        student1 = Student(2, 'Elena', 12)
        student2 = Student(3, 'Ema', 10)
        student3 = Student(4, 'Ema', 11)
        laborator = Laborator('1_5', 'app', '12/12/2025')
        laborator1 = Laborator('1_6', 'app', '12/12/2025')
        repo_studenti = StudentRepository()
        repo_laborator = LaboratorRepository()
        repo_studenti.add_student(student)
        repo_studenti.add_student(student1)
        repo_studenti.add_student(student2)
        repo_studenti.add_student(student3)
        repo_laborator.add_laborator(laborator)
        repo_laborator.add_laborator(laborator1)
        repo_note = NoteRepository()
        validator_note = ValidatorNote()
        business_note = NoteBusiness(repo_laborator, repo_studenti, repo_note, validator_note)
        nota5 = business_note.asignare_laborator(4, '1_5')
        nota1 = business_note.asignare_laborator(1, '1_5')
        nota2 = business_note.asignare_laborator(1, '1_6')
        nota3 = business_note.asignare_laborator(2, '1_5')
        nota4 = business_note.asignare_laborator(3, '1_5')
        test4 = business_note.notare_laborator(4, '1_5', 2)
        test = business_note.notare_laborator(1, '1_5', 7)
        test5=business_note.notare_laborator(1,'1_6',2)
        test1 = business_note.notare_laborator(2, '1_5', 10)
        test3 = business_note.notare_laborator(3, '1_5', 7)
        #Anca-4.5 Ema-2
        x=business_note.raport_corigenti()
        assert x[1].get_nume()=='Anca'
        assert x[1].get_medie_nota()==4.5
        assert x[0].get_nume()=='Ema'
        assert x[0].get_medie_nota()==2
    def run_all_tests(self):
        self.__test_create_nota()
        self.__test_equal_note()
        self.__test_add_nota()
        self.__test_valideaza_nota()
        self.__test_adaugare_nota()
        self.__test_asignare_laborator()
        self.__test_asignare_nota_2()
        self.__test_cautare_dupa_id()
        self.__test_notare_laborator()
        self.__test_raport_problema()
        self.__test_raport_corigenti()