from Domeniu.validare import Validator
from Domeniu.teatru import Piesa
import random
from Infrastructura.teatru import FileRepoTeatru
class BusinessTeatru:
    def __init__(self,repo,validator):
        self.__repo=repo
        self.__validator=validator
    def adaugare(self,titlu,regizor,gen,durata):
        piesa=Piesa(titlu,regizor,gen,durata)
        self.__validator.validator_piesa(piesa)
        self.__repo.adaugare(piesa)
    def modificare(self,titlu,regizor,gen,durata):
        piesa=Piesa(titlu,regizor,gen,durata)
        self.__validator.validator_piesa(piesa)
        self.__repo.modificare(piesa)
    def random(self,nr):
        cnt=0
        genuri=["Comedie","Satira","Altele","Drama"]
        consoane=['b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','z']
        vocale=['a','e','i','o','u']
        ok=0
        for j in range(int(nr)):
            titlu=[]
            regizor=[]
            x=random.randint(8,12)
            index_spatiu=int(random.randint(1,int(x)-1))
            for i in range(int(x)):
                if ok==0:
                    titlu.append(random.choice(vocale))
                    regizor.append(random.choice(vocale))
                    ok=1
                else:
                    titlu.append(random.choice(consoane))
                    regizor.append(random.choice(consoane))
                    ok=0
            titlu[index_spatiu]=" "
            regizor[index_spatiu]=" "
            titlu_final=""
            regizor_final=""
            for el in titlu:
                titlu_final+=el
            for el in regizor:
                regizor_final+=el
            gen=random.choice(genuri)
            durata=int(random.randint(1,10))
            piesa=Piesa(titlu_final,regizor_final,gen,durata)
            self.__repo.adaugare(piesa)
    def exporta(self,fisier):
        lista=self.__repo.get_all()
        lista=sorted(lista,key=lambda x:(x.get_regizor(),x.get_titlu()))
        with open(fisier,"w")as f:
            for el in lista:
                f.write(str(el)+"\n")

def test_business():
    repo=FileRepoTeatru("C:\Proiecte\Pregatire Sesiune\Teatru\data\\business.txt")
    val=Validator()
    service=BusinessTeatru(repo,val)
    repo.seteaza()
    repo.write_all_files()
    service.adaugare("Manole","Eminescu","Drama",5)
    assert repo.len()==1
    service.modificare("Manole","Eminescu","Drama",6)
    lista=repo.get_all()
    assert lista[0].get_durata()==6
    service.random(1)
    assert repo.len()==2
    lista1=repo.get_all()
    assert len(lista1[1].get_titlu())>=8
    assert len(lista1[1].get_titlu())<=12
    assert lista1[1].get_durata()<=10 and lista1[1].get_durata()>=1
    assert lista1[1].get_gen() in ["Satira","Comedie","Altele","Drama"]
    repo2=FileRepoTeatru("C:\Proiecte\Pregatire Sesiune\Teatru\data\\export_test.txt")
    repo2.seteaza()
    repo2.write_all_files()
    assert repo2.len()==0
    service.exporta("C:\Proiecte\Pregatire Sesiune\Teatru\data\\export_test.txt")
    repo2.read_all_files()
    assert repo2.len()==2
test_business()




