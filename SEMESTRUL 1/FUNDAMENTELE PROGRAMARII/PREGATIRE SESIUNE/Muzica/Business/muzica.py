from Domeniu.muzica import Melodie
import random
class BusinessMuzica:
    def __init__(self,repo,validator):
        self.__repo=repo
        self.__validator=validator
    def modificare(self,titlu,artist,gen,durata):
        mel=Melodie(titlu,artist,gen,durata)
        self.__validator.valideaza_melodie(mel)
        lista=self.__repo.get_all()
        ok=0
        for x in lista:
            if x.get_titlu()==titlu and x.get_artist()==artist:
                ok=1
                mel.set_id(x.get_id())
        if ok==1:
            self.__repo.modificare(mel)
        else:
            raise Exception("nu exista melodie")
    def adauga(self,titlu,artist,gen,durata):
        mel = Melodie(titlu, artist, gen, durata)
        self.__validator.valideaza_melodie(mel)
        self.__repo.adauga(mel)
    def random(self,nr,titluri,artisti):
        cnt=0
        titluri=titluri.strip().split(",")
        artisti=artisti.strip().split(",")
        lista_gen=["Rock","Pop","Jazz","Altele"]
        random.seed(4)
        while cnt!=nr:
            titlu=random.choice(titluri)
            artist=random.choice(artisti)
            gen=random.choice(lista_gen)
            durata=random.randint(1,500)
            melodie=Melodie(titlu,artist,gen,durata)
            cnt=cnt+1
            self.__repo.adauga(melodie)
    def export(self,fisier):
        lista=self.__repo.get_all()
        lista = sorted(lista, key=lambda x: (x.get_titlu(), x.get_artist()))

        with open(fisier, 'w') as f:
            for el in lista:
                string = el.get_titlu() + ',' + el.get_artist() + ',' + el.get_gen() + ',' + str(el.get_durata()) + '\n'
                f.write(string)

