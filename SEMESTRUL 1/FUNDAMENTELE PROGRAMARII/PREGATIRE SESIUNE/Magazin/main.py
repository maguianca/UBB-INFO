from Infrastructura.magazin import RepoMagazin
from Infrastructura.magazin import FileRepoMagazin
from Business.magazin import BusinessMagazin
from Domeniu.magazin import Produs
from UI.consola import Consola
from Validare.magazin import Validator
def run():
    repo=RepoMagazin()
    fisier="C:\Proiecte\Pregatire Sesiune\Magazin\Infrastructura\produs.txt"
    repofile=FileRepoMagazin(fisier)
    validator=Validator()
    service=BusinessMagazin(repofile,validator)
    consola=Consola(service)
    consola.run()

if __name__=="__main__":
    run()