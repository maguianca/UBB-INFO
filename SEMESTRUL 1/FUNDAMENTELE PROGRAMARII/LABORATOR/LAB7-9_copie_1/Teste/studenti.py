from Domeniu.studenti import Student
from Validare.studenti import ValidatorStudent
from Repository.studenti import StudentRepository


class TesteS:
    def __test_create_student(self):
        id_student = 2301
        nume = "Anca"
        #grup =9
        epsilon = 0.0001
        student = Student(id_student, nume)
        other_id_student = 2301
        other_nume = "Anca"
        #other_grup = 9
        other_student = Student(other_id_student, other_nume)
        assert student.get_id_student() == id_student
        assert student.get_nume() == nume
        #assert abs(student.get_grup() - grup) < epsilon
        assert student == other_student
    def __test_validate_student(self):
        id_student = 1001
        nume = "Andreea"
        #grup = 10
        epsilon = 0.0001
        student = Student(id_student, nume)
        bad_id_student = -1001
        bad_nume = ""
        #bad_grup = -9
        epsilon = 0.0001
        bad_student = Student(bad_id_student, bad_nume)
        validator = ValidatorStudent()
        validator.valideaza_student(student)
        try:
            validator.valideaza_student(bad_student)
            assert False
        except Exception as ex:
            assert (str(ex) == "id invalid!\nnume invalid!\n")
    def __test_adauga_student(self):
        id_student = 2301
        nume = "Anca"
        #grup =9
        student = Student(id_student, nume)

        other_id_student = 2302
        other_nume = "Ancutza"
        #other_grup = 10
        other_student = Student(other_id_student, other_nume)
        repo=StudentRepository()
        #repo.stergere_student(id_student)
        repo.add_student(student)
        repo.add_student(other_student)
        assert student in repo.get_all()
        assert other_student in repo.get_all()
        assert len(repo.get_all())==2
    def __test_stergere_student(self):
        id_student = 2301
        nume = "Anca"
        #grup =9
        student = Student(id_student, nume)

        other_id_student = 2302
        other_nume = "Ancutza"
        #other_grup = 10
        other_student = Student(other_id_student, other_nume)
        repo=StudentRepository()
        #repo.stergere_student(id_student)
        repo.add_student(student)
        repo.add_student(other_student)
        assert student in repo.get_all()
        assert other_student in repo.get_all()
        assert len(repo.get_all())==2
        repo.stergere_student(id_student)
        assert other_student in repo.get_all()
        assert len(repo.get_all())==1
    def __test_modifica_student(self):
        id_student = 2301
        nume = "Anca"
        #grup =9
        student = Student(id_student, nume)
        other_id_student = 2301
        other_nume = "Ancutza"
        #other_grup = 10
        other_student = Student(other_id_student, other_nume)
        repo=StudentRepository()
        repo.add_student(student)
        repo.modifica(other_student)
        assert other_student in repo.get_all()
        assert len(repo.get_all()) == 1
        lista=repo.get_all()
        assert lista[0]==other_student
        assert lista[0].get_id_student()==other_id_student
        assert lista[0].get_nume()==other_nume
        #assert lista[0].get_grup()==other_grup



    def run_all_tests(self):
        self.__test_create_student()
        self.__test_validate_student()
        self.__test_adauga_student()
        self.__test_stergere_student()
        self.__test_modifica_student()