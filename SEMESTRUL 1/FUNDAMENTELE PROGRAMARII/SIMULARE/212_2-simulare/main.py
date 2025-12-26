from Domeniu.imobil import Imobil
from Infrastructura.imobil import RepoImobil,FileRepoImobil
from Business.imobil import BusinessImobil
from UI.consola import Consola


def run():
    file="C:\\212_2-simulare\\Data\\imobiliare.txt"
    repo=FileRepoImobil(file)
    service=BusinessImobil(repo)
    consola=Consola(service)
    consola.run()


if __name__ == '__main__':
    run()
