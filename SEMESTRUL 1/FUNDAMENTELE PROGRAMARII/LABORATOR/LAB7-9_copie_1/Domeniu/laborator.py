
class Laborator:
    def __init__(self,numar,descriere,deadline):
        self.__numar = numar
        self.__descriere = descriere
        self.__deadline = deadline

    def get_numar(self):
        return self.__numar

    def get_descriere(self):
        return self.__descriere

    def get_deadline(self):
        return self.__deadline

    def set_numar(self,new_numar):
        self.__numar=new_numar
    def set_deadline(self,new_deadline):
        self.__deadline=new_deadline

    def set_descriere(self,new_descriere):
        self.__descriere=new_descriere

    def __eq__(self,gigi):
        return self.__numar == gigi.__numar

    def __str__(self):
        return f"NR:{self.__numar}  DESCRIERE:{self.__descriere}  DEADLINE:{self.__deadline}"