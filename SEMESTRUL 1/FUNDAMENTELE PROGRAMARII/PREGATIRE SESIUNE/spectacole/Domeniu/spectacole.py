class Spectacol:
    def __init__(self, titlu, artist, gen, durata):
        self.__titlu = titlu
        self.__artist = artist
        self.__gen = gen
        self.__durata = durata
    def get_titlu(self):
        return self.__titlu
    def get_artist(self):
        return self.__artist
    def get_gen(self):
        return self.__gen
    def get_durata(self):
        return self.__durata
    def set_titlu(self,n):
        self.__titlu=n
    def set_artist(self,n):
        self.__artist=n
    def set_gen(self,n):
        self.__gen=n
    def set_durata(self,n):
        self.__durata=n
    def __str__(self):
        return f"{self.__titlu},{self.__artist},{self.__gen},{self.__durata}"