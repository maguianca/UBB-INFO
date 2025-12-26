from Domeniu.spectacole import Spectacol
import random
class BusinessSpectacole:
    def __init__(self,repo,validator):
        self.__repo=repo
        self.__validator=validator
    def adaugare(self,titlu,artist,gen,durata):
        spectacol=Spectacol(titlu,artist,gen,durata)
        self.__validator.valideaza_spectacol(spectacol)
        self.__repo.adaugare(spectacol)
    def modificare(self,titlu,artist,gen,durata):
        spectacol=Spectacol(titlu,artist,gen,durata)
        self.__validator.valideaza_spectacol(spectacol)
        self.__repo.modificare(spectacol)
    def random(self,cifra):
        consoane=['b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','z']
        vocale=['a','e','i','o','u']
        genuri=["Comedie","Concert","Balet","Altele"]
        cnt=0
        while cnt!=int(cifra):
            titlu=[]
            regizor=[]
            ok=0
            lungime=random.randint(9,12)
            index_spatiu=int(random.randint(1,int(lungime)-1))
            for i in range(int(lungime)):
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
                regizor_final += el
            gen=random.choice(genuri)
            durata=random.randint(1,900)
            self.adaugare(titlu_final,regizor_final,gen,durata)
            cnt+=1

