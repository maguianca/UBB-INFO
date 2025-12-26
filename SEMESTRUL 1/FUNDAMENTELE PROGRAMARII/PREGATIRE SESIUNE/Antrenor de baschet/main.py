from Domeniu.validare import Validator
from Domeniu.baschet import Jucator
from Business.baschet import BusinessBaschet
from Infrastructura.baschet import FileRepoBaschet
from UI.consola import Consola

def run():
    file=("C:\Proiecte\Pregatire Sesiune\Antrenor de baschet\Data\\fisier.txt")
    repo=FileRepoBaschet(file)
    val=Validator()
    service=BusinessBaschet(repo,val)
    consola=Consola(service)
    consola.run()
if __name__=="__main__":
    run()
