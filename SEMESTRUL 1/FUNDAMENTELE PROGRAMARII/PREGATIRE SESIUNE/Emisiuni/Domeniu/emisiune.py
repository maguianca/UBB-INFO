class Emisiune:
    def __init__(self,nume,tip,durata,descriere):
        self.__nume=nume
        self.__tip=tip
        self.__durata=durata
        self.__descriere=descriere
        self.__id=0
    def get_nume(self):
        return self.__nume
    def get_tip(self):
        return self.__tip
    def get_durata(self):
        return self.__durata
    def get_descriere(self):
        return self.__descriere
    def set_nume(self,nume_nou):
        self.__nume=nume_nou
    def set_tip(self,tip_nou):
        self.__tip=tip_nou
    def set_durata(self,durata_nou):
         self.__durata=durata_nou
    def set_descriere(self,descriere_nou):
         self.__descriere=descriere_nou
    def set_id(self,id_nou):
         self.__id=id_nou
    def get_id(self):
        return self.__id
    def __str__(self):
        return f"{self.__nume},{self.__tip},{self.__durata},{self.__descriere}"