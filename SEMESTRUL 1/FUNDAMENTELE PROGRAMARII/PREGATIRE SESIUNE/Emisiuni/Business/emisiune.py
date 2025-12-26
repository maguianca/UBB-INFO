from Domeniu.emisiune import Emisiune
class BusinessEmisiune:
    def __init__(self,repo,validator):
        self.__repo=repo
        self.__validator=validator
    def stergere_business(self,nume,tip):
        lista=self.__repo.get_all()
        ok=0
        for el in lista:
            if el.get_nume()==nume and el.get_tip()==tip:
                self.__repo.stergere(el.get_id())
                ok=1
        return ok
    def modificare(self,nume,tip,durata,descriere):
        em = Emisiune(nume, tip, durata, descriere)
        self.__validator.valideaza_emisiune(em)
        lista=self.__repo.get_all()
        for el in lista:
            if el.get_nume() == nume and el.get_tip() == tip:
                em.set_id(el.get_id())
        self.__repo.modificare(em)
    def blocare(self,tip):
        lista=self.__repo.get_all()
        return [x for x in lista if tip not in x.get_tip()]



