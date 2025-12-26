from Business.studenti import StudentiBusiness
from Domeniu.studenti import Student
from Repository.studenti import StudentRepository
from Teste.studenti import TesteS
from Validare.studenti import ValidatorStudent
from UI.studenti import UIS
from Business.laborator import LaboratoareBusiness
from Domeniu.laborator import Laborator
from Repository.laborator import LaboratorRepository
from Teste.laborator import TesteL
from Validare.laborator import ValidatorLaborator
from UI.laborator import UIL
from UI import *


def main():
    repo = StudentRepository()
    s = TesteS()
    s.run_all_tests()
    validator = ValidatorStudent()
    service = StudentiBusiness(repo,validator)
    console = UIS(service)
    l = TesteL()
    l.run_all_tests()
    repos = LaboratorRepository()
    validators = ValidatorLaborator()
    servicel = LaboratoareBusiness(repos,validators)
    consoles = UIL(servicel)
    consola=Consola(consoles,console)
    consola.run()

if __name__=='__main__':
    main()