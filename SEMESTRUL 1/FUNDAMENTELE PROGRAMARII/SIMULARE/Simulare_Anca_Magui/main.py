from Domeniu.spital import Pacienti,Internari
from Infrastructura.spital import FileRepoSpital
from Business.spital import BusinessSpital
from UI.consola import Consola

def run():
    file_1="C:\\Simulare_Anca_Magui\\Data\\internari.txt"
    file_2="C:\\Simulare_Anca_Magui\\Data\\pacienti.txt"
    repo=FileRepoSpital(file_1,file_2)
    service=BusinessSpital(repo)
    consola=Consola(service)
    consola.run()


if __name__ == '__main__':
    run()
