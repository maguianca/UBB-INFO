class Eveniment:
    def __init__(self,data,ora,descriere):
        self.__data=data
        self.__ora=ora
        self.__descriere=descriere
    def get_data(self):
        return self.__data
    def get_ora(self):
        return self.__ora
    def get_descriere(self):
        return self.__descriere
    def set_data(self,n):
        self.__data=n
    def set_ora(self,n):
        self.__ora=n
    def set_descriere(self,n):
        self.__descriere=n
    def __str__(self):
        return f"{self.__data},{self.__ora},{self.__descriere}"
