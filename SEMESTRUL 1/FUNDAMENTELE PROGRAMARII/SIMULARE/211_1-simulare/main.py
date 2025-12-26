from Domeniu.locuinta import Locuinta
from Infrastructura.locuinta import FileRepoLocuinta
from Business.locuinta import BusinessLocuinta
from UI.consola import Consola


def run():
    file="C:\\211_1-simulare\\Infrastructura\\loc.txt"
    repo=FileRepoLocuinta(file)
    service=BusinessLocuinta(repo)
    consola=Consola(service)
    consola.run()


if __name__ == '__main__':
    run()

