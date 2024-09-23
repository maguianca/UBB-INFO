from Infrastructura.teatru import FileRepoTeatru
from Domeniu.teatru import Piesa
from Domeniu.validare import Validator
from UI.consola import Consola
from Business.teatru import BusinessTeatru

def run():
    repo=FileRepoTeatru("C:\Proiecte\Pregatire Sesiune\Teatru\data\\teatru.txt")
    val=Validator()
    service=BusinessTeatru(repo,val)
    consola=Consola(service)
    consola.run()
if __name__=="__main__":
    run()
