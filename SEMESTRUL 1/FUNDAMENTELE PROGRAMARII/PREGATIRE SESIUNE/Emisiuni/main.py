from Infrastructura.emisiune import FileRepoEmisiune
from Business.emisiune import BusinessEmisiune
from Domeniu.emisiune import Emisiune
from UI.consola import Consola
from Validare.emisiune import Validator

def run():
    validator=Validator()
    fisier="C:\Proiecte\Pregatire Sesiune\Emisiuni\Infrastructura\\fisier.txt"
    repo=FileRepoEmisiune(fisier)
    service=BusinessEmisiune(repo,validator)
    consola=Consola(service)
    consola.run()

if __name__=="__main__":
    run()