
class Laborator:
    def __init__(self,numar,descriere,deadline):
        self.__numar = numar
        self.__descriere = descriere
        self.__deadline = deadline

    def get_numar(self):
        """
        :return: atributul numar al laboratorului
        """
        return self.__numar

    def get_descriere(self):
        """
               :return: atributul descriere al laboratorului
               """
        return self.__descriere

    def get_deadline(self):
        """
               :return: atributul descriere al laboratorului
               """
        return self.__deadline

    def set_numar(self,new_numar):
        """
        seteaza atributul numar al entitatii laborator
        :param new_numar: int
        """
        self.__numar=new_numar
    def set_deadline(self,new_deadline):
        """
                seteaza atributul deadline al entitatii laborator
                :param new_numar: string
                """
        self.__deadline=new_deadline

    def set_descriere(self,new_descriere):
        """
                seteaza atributul descriere al entitatii laborator
                :param new_numar: string
                """
        self.__descriere=new_descriere

    def __eq__(self,gigi):
        """
                verifica daca atributele a doua entitati sunt egale
                :param gigi:student
                """
        return self.__numar == gigi.__numar

    def __str__(self):
        """
                :return: afiseaza lista sub forma de nr,descriere,deadline
                """
        return f"NR:{self.__numar}  DESCRIERE:{self.__descriere}  DEADLINE:{self.__deadline}"