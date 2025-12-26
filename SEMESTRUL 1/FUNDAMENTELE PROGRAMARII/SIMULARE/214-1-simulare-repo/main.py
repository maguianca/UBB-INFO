from Domeniu.material import Material
from Infrastructura.material import FileRepoMaterial
from Business.material import BusinessMaterial
from UI.consola import Consola



def run():
    #file="C:\\214-1-simulare\\Data\\material.txt"
    file="C:\Python\\214-1-simulare-repo\Data\material.txt"
    salvare="C:\Python\\214-1-simulare-repo\Data\salvare.txt"
    #salvare = "C:\\214-1-simulare\\Data\\salvare.txt"
    repo=FileRepoMaterial(file,salvare)
    service=BusinessMaterial(repo)
    consola=Consola(service)
    consola.run()

if __name__ == '__main__':
   run()
