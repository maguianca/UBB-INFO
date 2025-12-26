from Domeniu.laborator import Laborator
from Validare.laborator import ValidatorLaborator
from Repository.laborator import LaboratorRepository
#from Domeniu import Student
#from Validare import ValidatorStudent


class TesteL:
    def __test_create_laborator(self):
        numar = 5
        descriere = "aplicatie cu interfata"
        deadline="12/10/2023"
        epsilon = 0.0001
        laborator = Laborator(numar, descriere, deadline)
        other_numar = 5
        other_descriere = "aplicatie cu interfata"
        other_deadline ="12/10/2023"
        other_laborator = Laborator(other_numar, other_descriere, other_deadline)
        assert laborator.get_numar() == numar
        assert laborator.get_descriere() == descriere
        assert abs(laborator.get_numar() - numar) < epsilon
        assert laborator == other_laborator
    def __test_validate_laborator(self):
        numar = 1001
        descriere = "aplicatie"
        deadline ="12/10/2023"
        epsilon = 0.0001
        laborator = Laborator(numar,descriere,deadline)
        bad_numar = -1001
        bad_descriere = ""
        bad_deadline ="12345"
        epsilon = 0.0001
        bad_laborator = Laborator(bad_numar,bad_descriere, bad_deadline)
        validator = ValidatorLaborator()
        validator.valideaza_laborator(laborator)
        try:
            validator.valideaza_laborator(bad_laborator)
            assert False
        except Exception as ex:
            assert (str(ex) == "numar invalid\ndescriere invalida\ndata invalida\n")

    def __test_adauga_laborator(self):
        numar = 1
        descriere = "aplicatie"
        deadline ="12/10/2023"
        laborator = Laborator(numar,descriere,deadline)

        other_numar = 2
        other_descriere = "consola"
        other_deadline ="12/10/2023"
        other_laborator = Laborator(other_numar, other_descriere, other_deadline)
        repo = LaboratorRepository()
        # repo.stergere_student(id_student)
        repo.add_laborator(laborator)
        repo.add_laborator(other_laborator)
        assert laborator in repo.get_all()
        assert other_laborator in repo.get_all()
        assert len(repo.get_all()) == 2

    def __test_stergere_laborator(self):
        numar = 1
        descriere = "aplicatie"
        deadline ="12/10/2023"
        laborator = Laborator(numar, descriere, deadline)

        other_numar = 2
        other_descriere = "consola"
        other_deadline ="15/10/2025"
        other_laborator = Laborator(other_numar, other_descriere, other_deadline)
        repo = LaboratorRepository()
        # repo.stergere_student(id_student)
        repo.add_laborator(laborator)
        repo.add_laborator(other_laborator)
        assert laborator in repo.get_all()
        assert other_laborator in repo.get_all()
        assert len(repo.get_all()) == 2
        repo.stergere_laborator(numar)
        assert other_laborator in repo.get_all()
        assert len(repo.get_all()) == 1

    def __test_modifica_laborator(self):
        numar = 1
        descriere = "aplicatie"
        deadline ="12/10/2023"
        laborator = Laborator(numar, descriere, deadline)

        other_numar = 1
        other_descriere = "consola"
        other_deadline ="15/10/2025"
        other_laborator = Laborator(other_numar, other_descriere, other_deadline)

        repo = LaboratorRepository()
        repo.add_laborator(laborator)
        repo.modifica(other_laborator)
        assert other_laborator in repo.get_all()
        assert len(repo.get_all()) == 1
        lista = repo.get_all()
        assert lista[0] == other_laborator
        assert lista[0].get_descriere() == other_descriere
        assert lista[0].get_deadline() == other_deadline
        assert lista[0].get_numar() == other_numar

    def run_all_tests(self):
        self.__test_create_laborator()
        self.__test_validate_laborator()
        self.__test_modifica_laborator()
        self.__test_adauga_laborator()
        self.__test_stergere_laborator()
