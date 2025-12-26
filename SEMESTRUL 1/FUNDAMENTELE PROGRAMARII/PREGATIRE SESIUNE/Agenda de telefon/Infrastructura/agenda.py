from Domeniu.agenda import Contact
class RepoContact:
    def __init__(self):
        self._contacte={}
    def adauga(self,contact):
        if contact.get_nume() not in self._contacte.keys():
            self._contacte[contact.get_nume()]=contact
        else:
            raise Exception("nume existent")
    def get_all(self):
        return [self._contacte[nume] for nume in self._contacte.keys()]
    def cautare(self,nume):
        if nume in self._contacte.keys():
            return self._contacte[nume]
        else:
            raise Exception("nume existent")


class FileRepoContact:
    def __init__(self,cale_fisier):
        self.__cale_fisier=cale_fisier
        RepoContact.__init__(self)
    def read_all_files(self):
        with open(self.__cale_fisier,"r")as f:
            self._contacte.clear()
            lines=f.readlines()
            for line in lines:
                if line!="":
                    parts=line.split(",")
                    if len(parts)==4:
                        id=parts[0]
                        nume=parts[1]
                        nrtel=parts[2]
                        grup=parts[3]
                        contact=Contact(id,nume,nrtel,grup)
                        self._contacte[nume]=contact
    def write_all_files(self):
        with open(self.__cale_fisier,"w")as f:
            for nume in self._contacte.keys():
                f.write(str(self._contacte[nume])+"\n")
    def adauga(self,contact):
        self.read_all_files()
        RepoContact.adauga(self,contact)
        self.write_all_files()
    def get_all(self):
        self.read_all_files()
        return RepoContact.get_all(self)
    def seteaza(self):
        self._contacte={}
    def len(self):
        return len(self._contacte)
    def cautare(self,nume):
        self.read_all_files()
        return RepoContact.cautare(self,nume)

def test_repo():
    repo=FileRepoContact("C:\Proiecte\Pregatire Sesiune\Agenda de telefon\data\\test.txt")
    repo.seteaza()
    repo.write_all_files()
    contact=Contact("2","Ioana","93758593","Familie")
    repo.adauga(contact)
    assert repo.cautare("Ioana") is not None
    assert repo.len()==1
    try:
        repo.adauga(contact)
        assert False
    except Exception:
        assert True
test_repo()