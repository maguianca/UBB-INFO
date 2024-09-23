from Domeniu.spital import Pacienti,Internari,DTO
from Infrastructura.spital import FileRepoSpital

class BusinessSpital:
    def __init__(self,repo):
        self.__repo=repo

    def afisare_pacienti(self,nume):
        """
        metoda care cauta in lista de pacienti pacientii cu un nume respectiv
        :param nume: string atribut al clasei Pacienti
        :return: lista de pacienti
        """
        if nume=="":
            raise Exception("nume invalid")
        pacienti=self.__repo.get_all_pacienti()
        lista_ceruta=[]
        for pacient in pacienti:
            if pacient.get_nume()==nume:
                lista_ceruta.append(pacient)
        if lista_ceruta==[]:
            raise Exception("lista vida")
        return lista_ceruta
    def afisare_internari(self):
        """
        metoda care parcurge lista de internari si adauga intr-o alta lista elemente dto
        :return: lista cu pacienti care au mai multe de doua internari
        """
        internari=self.__repo.get_all_internari()
        lista={}
        for x in internari:
            id=x.get_id()
            if id not in lista.keys():
                pacient=self.__repo.cautare_pacienti(id)
                nume=pacient.get_nume()
                data_nasterii=pacient.get_data()
                dto=DTO(id,nume,data_nasterii)
                dto.inc()
                lista[id]=dto
            else:
                lista[id].inc()
        return [lista[id] for id in lista.keys() if lista[id].get_internari()>=2]




def test():
    file1 = "C:\\Simulare_Anca_Magui\\Data\\test_1.txt"
    file2 = "C:\\Simulare_Anca_Magui\\Data\\test_2.txt"
    repo = FileRepoSpital(file1, file2)
    service=BusinessSpital(repo)
    lista=service.afisare_pacienti("Dumitru")
    x=Pacienti(2,"Dumitru","Oas","10.02.1992")
    assert len(lista)==2
    assert lista[0].get_id()==x.get_id()
    lista=service.afisare_internari()
    assert len(lista)==1
    assert lista[0].get_id()==4
    assert lista[0].get_nume()=="Dumitru"

test()
