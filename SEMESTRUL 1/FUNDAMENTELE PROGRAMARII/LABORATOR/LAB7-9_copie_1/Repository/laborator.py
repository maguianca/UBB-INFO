class LaboratorRepository:

    def __init__(self):
        self.__toatelaboratoarele = {}

    def stergere_laborator(self, numar):
        for key in list(self.__toatelaboratoarele.keys()):
            if self.__toatelaboratoarele[key].get_numar() == numar:
                del self.__toatelaboratoarele[key]
                return

    def cauta_elem(self,numar):
        for key in list(self.__toatelaboratoarele.keys()):
            if self.__toatelaboratoarele[key].get_numar()==numar:
                return 1
        return 0

    def modifica(self,student):
        numar=student.get_numar()
        descriere=student.get_descriere()
        deadline=student.get_deadline()
        if self.cauta_elem(numar)==1:
            for key in list(self.__toatelaboratoarele.keys()):
                if self.__toatelaboratoarele[key].get_numar() == numar:
                    self.__toatelaboratoarele[key].set_descriere(descriere)
                    self.__toatelaboratoarele[key].set_deadline(deadline)
        else:
            raise Exception("nu exista id!\n")


    def add_laborator(self, laborator):
        numar = laborator.get_numar()
        if numar in self.__toatelaboratoarele:
            raise Exception("numar problema existent!\n")
        self.__toatelaboratoarele[numar] = laborator

    def get_all(self):
        return [self.__toatelaboratoarele[x] for x in self.__toatelaboratoarele.keys()]