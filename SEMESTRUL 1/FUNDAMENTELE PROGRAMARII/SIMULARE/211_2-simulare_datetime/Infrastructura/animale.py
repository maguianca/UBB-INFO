from Domeniu.animale import Animale
class RepoAnimale:
    def __init__(self):
        self._animale = {}

    def get_all(self):
        """
        :return: lista dupa id
        """
        return[self._animale[id] for id in self._animale.keys()]


class FileRepoAnimale(RepoAnimale):
    def __init__(self, cale_fisier):
        self.__cale_fisier = cale_fisier
        RepoAnimale.__init__(self)

    def __read_all_from_file(self):
        """citeste elementele din fisier si le introduce intr-un dictionar dupa id unic"""
        with open(self.__cale_fisier,"r") as f:
            self._animale.clear()
            lines=f.readlines()
            for line in lines:
                if line!="":
                    parts=line.split(",")
                    if len(parts)==6:
                        id=int(parts[0])
                        nume=parts[1]
                        data=parts[2]
                        locatie=parts[3]
                        tip=parts[4]
                        life=int(parts[5])
                        x=Animale(id,nume,data,locatie,tip,life)
                        self._animale[id]=x
    def __write_all_in_files(self):
        """scrie in fisier pe randuri diferite elementele emtitati clasei animale"""
        with open(self.__cale_fisier,"w") as f:
            for id in self._animale:
                f.write(str(self._animale[id])+"\n")
    def golire(self):
        """goleste fisierul"""
        with open(self.__cale_fisier,"w") as f:
                f.write("")
    def get_all(self):
        """suprascrie functia din RepoAnimale si citeste din fisier"""
        self.__read_all_from_file()
        return RepoAnimale.get_all(self)
