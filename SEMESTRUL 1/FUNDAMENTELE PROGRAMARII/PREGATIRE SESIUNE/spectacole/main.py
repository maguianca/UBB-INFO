from Domeniu.validare import Validator
from Domeniu.spectacole import Spectacol
from Business.spectacole import BusinessSpectacole
from Infrastructura.spectacole import FileRepoSpectacole
from UI.consola import Consola

def run():
    repo=FileRepoSpectacole("C:\Proiecte\Pregatire Sesiune\spectacole\Data\\fisier.txt")
    val=Validator()
    service=BusinessSpectacole(repo,val)
    consola=Consola(service)
    consola.run()
if __name__=="__main__":
    run()