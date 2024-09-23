from Business.studenti import StudentiBusiness
from Domeniu.studenti import Student
from Infrastructura.studenti import FileRepoStudenti
from Teste.studenti import TesteS
from Validare.studenti import ValidatorStudent
from Business.laborator import LaboratoareBusiness
from Domeniu.laborator import Laborator
from Infrastructura.laborator import *
from Teste.laborator import TesteL
from Validare.laborator import ValidatorLaborator
from Teste.note import TesteN
from UI.consola import Consola
from Infrastructura.note import FileRepoNote
from Infrastructura.note import NoteRepository
from Infrastructura.studenti import StudentRepository
from Business.note import NoteBusiness
from Domeniu.note import Note
from Validare.note import ValidatorNote
import random

def main():
    #repo = StudentRepository()
    repo = FileRepoStudenti("C:\\Python\\LAB7-9_sortare_final_final\\Infrastructura\\studenti.txt")
    a=TesteN()
    a.run_all_tests()
    s = TesteS()
    s.run_all_tests()
    validator = ValidatorStudent()
    validatorn=ValidatorNote()
    service = StudentiBusiness(repo,validator)
    #console = UIS(service)
    l = TesteL()
    l.run_all_tests()
    repos = FileRepoLaborator("C:\\Python\\LAB7-9_sortare_final_final\\Infrastructura\\laboratoare.txt")
    #repos=LaboratorRepository()
    repon=FileRepoNote("C:\\Python\\LAB7-9_sortare_final_final\\Infrastructura\\note.txt")
    #repon=NoteRepository()
    validators = ValidatorLaborator()
    servicel = LaboratoareBusiness(repos,validators)
    servicen=NoteBusiness(repos,repo,repon,validatorn)
    #consoles = UIL(servicel)
    consola=Consola(service,servicel,servicen)
    consola.run()

if __name__=='__main__':
    main()