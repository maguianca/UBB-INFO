from Infrastructura.muzica import FileRepoMuzica
from Business.muzica import BusinessMuzica
from UI.consola import Consola
from Validare.muzica import Validare

def run():
    fisier="C:\Proiecte\Pregatire Sesiune\Muzica\Infrastructura\muzica.txt"
    repo=FileRepoMuzica(fisier)
    validator = Validare()
    service=BusinessMuzica(repo,validator)
    consola=Consola(service)
    consola.run()

if __name__=="__main__":
    run()