from Domeniu.material import Material
from Infrastructura.material import FileRepoMaterial
from Business.material import BusinessMaterial
from UI.consola import Consola



def run():
    file="C:\\214-1-simulare\\Data\\material.txt"
    salvare = "C:\\214-1-simulare\\Data\\salvare.txt"
    repo=FileRepoMaterial(file,salvare)
    service=BusinessMaterial(repo)
    consola=Consola(service)
    consola.run()

if __name__ == '__main__':
   run()
