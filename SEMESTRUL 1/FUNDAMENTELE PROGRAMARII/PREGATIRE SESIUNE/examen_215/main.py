from Business.eveniment import BusinessTime
from Infrastructura.eveniment import FileRepoTime
from Domeniu.Validator import Validator
from Domeniu.eveniment import Eveniment
from UI.consola import Consola

def run():
    repo=FileRepoTime("C:\Proiecte\Pregatire Sesiune\examen_215\data\\fisier.txt")
    validator = Validator()
    service=BusinessTime(repo,validator)
    consola=Consola(service)
    consola.run()
if __name__=="__main__":
    run()