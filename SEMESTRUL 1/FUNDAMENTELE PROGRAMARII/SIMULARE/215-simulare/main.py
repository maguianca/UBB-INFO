from Business.mobilier import MobilierBusiness
from Domeniu.mobilier import Mobilier
from Infrastructura.mobilier import MobilierRepository, FileMobilierRepository
from Validare.mobilier import ValidatorMobilier
from UI.consola import Consola
from Teste.mobilier import Testemobilier

def run():
    teste=Testemobilier()
    #repo=MobilierRepository()
    repo=FileMobilierRepository("C:\\215-simulare\\Infrastructura\\mob.txt")
    #validator=ValidatorMobilier()
    service=MobilierBusiness(repo)
    consola=Consola(service)
    consola.run()
    teste.run_all_tests()


if __name__ == '__main__':
    run()