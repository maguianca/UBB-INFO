class Produs:
    def __init__(self,id,denumire,pret):
        self.__id=id
        self.__denumire=denumire
        self.__pret=pret

    def get_id(self):
        return self.__id
    def get_denumire(self):
        return self.__denumire
    def get_pret(self):
        return self.__pret
    def set_id(self,id_nou):
        self.__id=id_nou
    def set_denumire(self,denumire_nou):
        self.__denumire=denumire_nou
    def set_pret(self,pret_nou):
        self.__pret=pret_nou
    def __str__(self):
        return f"{self.__id},{self.__denumire},{self.__pret}"


