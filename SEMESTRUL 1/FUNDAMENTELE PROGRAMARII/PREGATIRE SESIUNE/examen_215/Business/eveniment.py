from datetime import date,timedelta,datetime
from Domeniu.eveniment import Eveniment
class BusinessTime:
    def __init__(self,repo,validator):
        self.__repo=repo
        self.__validator=validator

    def evenimente(self):
        lista=self.__repo.get_all()
        today=date.today()
        tod=today.strftime("%d.%m.%Y")
        lista=[x for x in lista if x.get_data()==tod]
        return lista
    def adaugare(self,data,ora,descriere):
        ev=Eveniment(data,ora,descriere)
        self.__validator.valideaza_eveniment(ev)
        self.__repo.adaugare(ev)
    def tabel(self,data):
        lista=self.__repo.get_all()
        """datetime.strptime(data,"%d.%m.%Y")
        result=[x for x in lista if x.get_data()>=data and x.get_data()<=datetime.strptime(data,"%d.%m.%Y")+timedelta(days=3)]
        return result"""
        """data_formatata = datetime.strptime(data, "%d.%m.%Y")

        # Modificare a intervalului pentru a verifica evenimente în intervalul [data, data + 3 zile]
        interval_final = data_formatata + timedelta(days=3)

        result = [x for x in lista if data_formatata <= x.get_data() <= interval_final]
        return result"""
        parts=data.split(".")
        zi=int(parts[0])
        luna=parts[1]
        an=parts[2]
        prima=str(zi)
        ultima=str(zi+3)
        result=[x for x in lista if
                an==x.get_data().split(".")[2] and luna==x.get_data().split(".")[1]and
                prima<=x.get_data().split(".")[0] and ultima>=x.get_data().split(".")[0]]
        return result
    def exporta(self,fisier,caractere):
        lista=self.__repo.get_all()
        lista=[x for x in lista if str(caractere)in x.get_descriere()]
        if lista==[]:
            raise Exception("nu exista")
        lista=sorted(lista,key=lambda x: (x.get_data(),x.get_ora()))
        with open(fisier,"w")as f:
            for el in lista:
                f.write(str(el)+"\n")


