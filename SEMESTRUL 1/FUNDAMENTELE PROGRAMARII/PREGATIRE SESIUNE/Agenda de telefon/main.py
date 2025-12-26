from Business.agenda import BusinessContact
from Domeniu.agenda import Contact
from Infrastructura.agenda import FileRepoContact
from UI.consola import Consola
from Domeniu.validare import Validator

def run():
    file="C:\Proiecte\Pregatire Sesiune\Agenda de telefon\data\\telefon.txt"
    repo=FileRepoContact(file)
    validator=Validator()
    service=BusinessContact(repo,validator)
    consola=Consola(service)
    consola.run()
if __name__=="__main__":
    run()
