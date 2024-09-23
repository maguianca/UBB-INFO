from Domeniu.animale import DTO,Animale
from Infrastructura.animale import FileRepoAnimale
class BusinessAnimale:
    def __init__(self,repo):
        self.__repo=repo

    def comparare(self,data1,data2):
        """returneaza 1 data data1<data2 altfel 2 egale 0"""
        params1 = data1.split("/")
        params2 = data2.split("/")
        an1 = int(params1[0])
        an2 = int(params2[0])
        luna1 = int(params1[1])
        luna2 = int(params2[1])
        zi1 =int(params1[2])
        zi2 =int(params2[2])
        if an1<an2:
            return 1
        elif an1==an2 and luna1<luna2:
            return 1
        elif an1==an2 and luna1==luna2 and zi1<zi2:
            return 1
        elif an1==an2 and luna1==luna2 and zi1==zi2:
            return 0
        else:
            return 2

    def filtrare(self,data):
        """
        filtreaza datele din clasa Animale care au data mai mica <data
        valideaza data
        :param data: string (an/luna/zi)
        :return: lista
        """
        params=data.split("/")
        erori=""
        if len(params)!=3:
            raise Exception("format invalid")
        try:
            an=int(params[0])
            luna=int(params[1])
            zi=int(params[2])
        except Exception as ex:
            raise Exception("format invalid")
        if an<1900 or an>2024:
            erori+="an invalid"
        if luna<0 or luna>12:
            erori+="luna invalida"
        if zi<1 or zi>31:
            erori+="zi invalida"
        if len(erori)>0:
            raise Exception(erori)
        lista=self.__repo.get_all()
        final=[]
        for x in lista:
            ok=0
            d=x.get_data()
            pars=d.split("/")
            a=int(pars[0])
            l=int(pars[1])
            z=int(pars[2])
            if a<an:
                ok=1
            elif l<luna:
                ok=1
            elif z<zi:
                ok=1
            else:
                ok=0
            if ok==1:
                final.append(x)
        if final==[]:
            raise Exception("lista goala")
        else:
            return final
    def statistica(self):
        """
        creaza statistica dupa tipuri
        :return: dictionar cu cheie tip de dto care contine nume, media de viata si tipul
        """
        lista=self.__repo.get_all()
        stat={}
        for x in lista:
            if x.get_tip() not in stat:
                nume=x.get_nume()
                durata=x.get_life()
                data=x.get_data()
                tip=x.get_tip()
                ob=DTO(tip,nume,data,durata)
                stat[tip]=ob
                stat[tip].ani()
            else:
                data1 = x.get_data()
                data2 = stat[x.get_tip()].get_data()
                if self.comparare(data2,data1)==1:
                    stat[x.get_tip()].set_nume(x.get_nume())
                    stat[x.get_tip()].set_data(x.get_data())
                    stat[x.get_tip()].set_durata(x.get_life())
                    stat[x.get_tip()].ani()
                    stat[x.get_tip()].inc()
        for tip,s in stat.items():
            s.medie()
        if stat=={}:
            raise Exception("dict vid")
        else:
            return stat
def test_comparare():
    repo=FileRepoAnimale("C:\\211_2-simulare\\Teste\\t.txt")
    service=BusinessAnimale(repo)
    assert(service.comparare("2023/1/1","2024/1/1")==1)
    assert (service.comparare( "2024/1/1","2023/1/1") == 2)
    assert(service.comparare("2020/2/2","2020/2/2")==0)
test_comparare()
def test_filtrare():
    repo = FileRepoAnimale("C:\\211_2-simulare\\Teste\\t.txt")
    service = BusinessAnimale(repo)
    lista=service.filtrare("2020/1/1")
    assert(len(lista))==2
    assert lista[0].get_id()==2
test_filtrare()
def test_statistica():
    repo = FileRepoAnimale("C:\\211_2-simulare\\Teste\\t.txt")
    service = BusinessAnimale(repo)
    lista = service.statistica()
    assert len(lista)==2
    assert lista["reptila"].get_nume()=="OBB"
test_statistica()