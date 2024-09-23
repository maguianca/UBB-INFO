from Domeniu.validator import Validator
from Infrastructura.biblioteca import FileRepoBiblioteca
from Business.biblioteca import BusinessBiblioteca
from UI.consola import Consola

def run():
    repo=FileRepoBiblioteca("C:\Proiecte\Pregatire Sesiune\Biblioteca\data\\fisier.txt")
    val=Validator()
    service=BusinessBiblioteca(repo,val)
    consola=Consola(service)
    consola.run()
if __name__=="__main__":
    run()