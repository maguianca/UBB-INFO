from Domeniu.material import Material,DTO
from Infrastructura.material import FileRepoMaterial1,FileRepoMaterial2
class BusinessMaterial:
    def __init__(self,repo1,repo2):
        self.__repo1=repo1
        self.__repo2=repo2


    def salvare(self,valoare):
        if valoare<0:
            raise Exception("cant invalida")
        list=self.__repo.get_all()
        self.__repo.golire()
        for elem in list:
            quantity = int(elem.get_cantitate())
            price = int(elem.get_pret())
            valoare_obiect = quantity * price
            if valoare_obiect>valoare:
                self.__repo.adaugare(elem)
    def vanzare(self,cod,cantitate):
        if cod<0 or cantitate<0:
            raise Exception("cod or cant invalida")
        material=self.__repo.cautare(cod)
        self.__repo.golire()
        if int(material.get_cantitate())>=cantitate:
            x=int(material.get_cantitate())-cantitate
            material_nou=Material(material.get_cod(),material.get_denumire(),x,material.get_pret())
            self.__repo.modificare(material_nou)
            valoare=cantitate*int(material.get_pret())
            dto=DTO(material.get_denumire(),cantitate,valoare)
            self.__repo.adaugare(dto)
            return 1
        return 0

def test():
    #file = "C:\\214-1-simulare\\Data\\test1.txt"
    #salvare = "C:\\214-1-simulare\\Data\\test_salvare.txt"
    file = "C:\Python\\214-1-simulare-repo\Data\test1.txt"
    salvare = "C:\Python\\214-1-simulare-repo\Data\salvare.txt"
    repo = FileRepoMaterial(file, salvare)
    service=BusinessMaterial(repo)
    service.salvare(100)

test()
