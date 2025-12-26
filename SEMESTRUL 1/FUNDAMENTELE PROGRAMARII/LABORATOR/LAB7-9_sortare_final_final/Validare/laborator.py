import Domeniu
from Exceptii.valid_error import ValidError
class ValidatorLaborator:

    def valideaza_laborator(self,laborator):
        """
        valideaza entitatea laborator
        verifica numar ,descriere si data sa fie un format valid
        :param laborator: entitate de tip laborator
        :return: raise exception daca este cazul
        """
        erori=""
        numar=laborator.get_numar()
        descriere = laborator.get_descriere()
        data=laborator.get_deadline()
        parti = numar.split('_')
        if len(parti)!=2:
            raise ValidError("format invalid")
        try:
            p1 = int(parti[0])
            p2 = int(parti[1])
        except Exception:
            raise ValidError("format invalid")
        if p1<0 or p1>10:
            erori += "nr1 invalid!\n"
        if p2<0 or p2>10:
            erori += "nr2 invalid!\n"
        if descriere=="":
            erori+="descriere invalida\n"
        e=1
        an=0
        luna=0
        zi=0
        d1=str(data).split("/")
        if(len(d1))==3:
            try:
                zi=int(d1[0])
                luna=int(d1[1])
                an=int(d1[2])
                e=0
            except ValueError:
                e=1
                erori += "data calendaristica invalida, introduceti in formatul zi/luna/an\n"
        else:
            erori+="data invalida\n"
        if e==0:
            if an<2023:
                erori+="deadline incheiat, an incorect\n"
            if an>2028:
                erori+="deadline depasit, an incorect\n"
            if luna in [1,3,5,7,8,10,12]:
                if zi<1 or zi>31:
                    erori+=" zi invalida\n"
            elif luna in [4,6,9,11]:
                if zi<1 or zi>30:
                    erori += " zi invalida\n"
            elif luna==2:
                if an%4==0:
                    if zi<1 or zi>29:
                        erori+=" zi invalida\n"
                else:
                    if zi<1 or zi>28:
                        erori += " zi invalida\n"
            else:
                erori+="luna invalida\n"
        if len(erori)>0:
            raise ValidError(erori)



    def valideaza_numar(self,numar):
        """
        valideaza numar
        :param numar: stribut al clasei laborator
        :return: raise exception daca este cazul
        """
        erori=""
        parti = numar.split('_')
        if len(parti) != 2:
            raise ValidError("format invalid")
        try:
            p1 = int(parti[0])
            p2 = int(parti[1])
        except Exception:
            raise ValidError("format invalid")
        if p1 < 0 or p1 > 10:
            erori += "nr1 invalid!\n"
        if p2 < 0 or p2 > 10:
            erori += "nr2 invalid!\n"
        if len(erori)>0:
            raise ValidError(erori)