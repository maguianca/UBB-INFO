from Domeniu.spital import Pacienti, Internari


class RepoSpital:
    def __init__(self):
        self._pacienti={}
        self._internari={}

    def get_all_pacienti(self):
        """metoda care returneaza lista de pacienti"""
        return [self._pacienti[id]for id in self._pacienti.keys()]

    def get_all_internari(self):
        """metoda care returneaza lista de internari"""
        return [self._internari[id] for id in self._internari.keys()]
    def cautare_pacienti(self,id):
        """metoda care cauta in lista de pacient un pacient dupa id
        return Exception daca nu exista id
        altfel, return element din clasa de pacienti cu id respectiv"""
        if id not in self._pacienti.keys():
            raise Exception("id negasit")
        return self._pacienti[id]

class FileRepoSpital(RepoSpital):
    def __init__(self,cale_fisier_1,cale_fisier_2):
        self.__cale_fisier_1=cale_fisier_1
        self.__cale_fisier_2=cale_fisier_2
        RepoSpital.__init__(self)

    def __read_all_pacienti(self):
        """citeste elementele din fisierul de pacienti"""
        with open(self.__cale_fisier_2) as f:
            self._pacienti.clear()
            lines=f.readlines()
            for line in lines:
                if line!="":
                    parts=line.strip().split(",")
                    if len(parts)==4:
                        id=int(parts[0])
                        nume=parts[1]
                        adresa=parts[2]
                        data=parts[3]
                        pacient=Pacienti(id,nume,adresa,data)
                        self._pacienti[id]=pacient

    def __read_all_internari(self):
        """citeste elementele din fisierul de pacienti"""
        with open(self.__cale_fisier_1) as f:
            self._internari.clear()
            lines = f.readlines()
            for line in lines:
                if line != "":
                    parts = line.strip().split(",")
                    if len(parts) == 5:
                        cod=parts[0]
                        id = int(parts[1])
                        diagnostic = parts[2]
                        data_intrare = parts[3]
                        data_iesire= parts[4]
                        internare=Internari(cod,id,diagnostic,data_intrare,data_iesire)
                        self._internari[cod] = internare
    def get_all_pacienti(self):
        """returneaza lista de pacienti"""
        self.__read_all_pacienti()
        return RepoSpital.get_all_pacienti(self)

    def get_all_internari(self):
        """returneaza lista de internari"""
        self.__read_all_internari()
        return RepoSpital.get_all_internari(self)
    def cautare_pacienti(self,id):
        """citeste din fisier si cauta un pacient dupa id
            id -atribut al clasei Pacienti- int
            return pacient ,element al clasei Pacienti
            """
        self.__read_all_pacienti()
        return RepoSpital.cautare_pacienti(self,id)

    def len1(self):
        """verifica lungimea lista de pacienti"""
        return len(self._pacienti)
    def len2(self):
        """verifica lungimea listei de internari"""
        return len(self._internari)

def test():
    file1="C:\\Simulare_Anca_Magui\\Data\\test_1.txt"
    file2="C:\\Simulare_Anca_Magui\\Data\\test_2.txt"
    repo=FileRepoSpital(file1,file2)
    pacienti=repo.get_all_pacienti()
    internari=repo.get_all_internari()
    assert repo.len1()==3
    assert repo.len2()==2
    assert repo.cautare_pacienti(2) is not None
test()



