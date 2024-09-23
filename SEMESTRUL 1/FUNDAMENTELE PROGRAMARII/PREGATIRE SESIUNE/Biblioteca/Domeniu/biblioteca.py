class Carte:
    def __init__(self,id,titlu,autor,an):
        self.__id=id
        self.__titlu=titlu
        self.__autor=autor
        self.__an=an
    def get_id(self):
        return self.__id
    def get_titlu(self):
        return self.__titlu
    def get_autor(self):
        return self.__autor
    def get_an(self):
        return self.__an
    def set_id(self,n):
        self.__id=n
    def set_titlu(self,n):
        self.__titlu=n
    def set_autor(self,n):
        self.__autor=n
    def set_an(self,n):
        self.__an=n
    def __str__(self):
        return f"{self.__id},{self.__titlu},{self.__autor},{self.__an}"