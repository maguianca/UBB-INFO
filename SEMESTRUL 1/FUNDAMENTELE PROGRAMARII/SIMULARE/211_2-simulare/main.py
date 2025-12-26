from Domeniu.animale import Animale
from Business.animale import BusinessAnimale
from Infrastructura.animale import RepoAnimale,FileRepoAnimale
from UI.consola import Consola


def run():
    file="C:\\211_2-simulare\\Teste\\animale.txt"
    repo=FileRepoAnimale(file)
    service=BusinessAnimale(repo)
    consola=Consola(service)
    consola.run()
if __name__ == '__main__':
    run()

