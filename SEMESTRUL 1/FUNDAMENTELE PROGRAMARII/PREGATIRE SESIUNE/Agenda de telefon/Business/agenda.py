from Domeniu.validare import Validator
from Domeniu.agenda import Contact,DTO
from Infrastructura.agenda import FileRepoContact
class BusinessContact:
    def __init__(self,repo,validator):
        self.__repo=repo
        self.__validator=validator
    def adaugare(self,id,nume,nrtel,grup):
        con=Contact(id,nume,nrtel,grup)
        self.__validator.valideaza_contact(con)
        self.__repo.adauga(con)
    def cautare(self,nume):
        return self.__repo.cautare(nume)
    def filtrare(self,tip):
        lista=self.__repo.get_all()
        lista_final=[]
        for el in lista:
            if el.get_grup().strip()==tip:
                lista_final.append(el)
        lista_final=sorted(lista_final,key=lambda x:x.get_nume())
        return lista_final
    def exporta(self,grup):
        lista = self.__repo.get_all()
        lista_final = []
        for el in lista:
            if el.get_grup().strip() == grup:
                dto=DTO(el.get_nume(),el.get_nrtel())
                lista_final.append(dto)
        with open("C:\Proiecte\Pregatire Sesiune\Agenda de telefon\data\\export.txt","w") as f:
            for el in lista_final:
                f.write(str(el)+"\n")

def test_business():
    repo = FileRepoContact("C:\Proiecte\Pregatire Sesiune\Agenda de telefon\data\\test_business.txt")
    validator=Validator()
    service=BusinessContact(repo,validator)
    lista=service.filtrare("Familie")
    assert len(lista)==3
    assert lista[0].get_nume()=="Elena"
    try:
        service.adaugare("7","i","45363fs","Altele")
        assert False
    except Exception as ex:
        assert str(ex)=="nr incorect\n"
    assert service.cautare("Elena").get_id()=="5"
test_business()
