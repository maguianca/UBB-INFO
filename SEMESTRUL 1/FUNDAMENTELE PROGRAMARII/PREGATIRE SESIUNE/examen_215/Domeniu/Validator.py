from Domeniu.eveniment import Eveniment
class Validator:
    def valideaza_eveniment(self,eveniment):
        erori=""
        data=eveniment.get_data().split(".")
        if len(data)!=3:
            erori+="data invalida"
        else:
            try:
                ziua=int(data[0])
                luna=int(data[1])
                an=int(data[2])
            except ValueError:
                erori+="date invalide\n"
            if luna in [4,6,9,11]:
                if ziua<1 or ziua>30:
                    erori+="ziua invalida\n"
            elif luna in [1,3,5,7,8,10,12]:
                if ziua<1 or ziua>31:
                    erori+="ziua invalida\n"
            elif luna==2:
                if ziua<1 or ziua>28:
                    erori+="ziua invalida\n"
            else:
                erori+="luna invalida\n"
            if an<2000 or an>2080:
                erori+="an invalid\n"
        data_ora=eveniment.get_ora().split(":")
        try:
            ora=int(data_ora[0])
            minut=int(data_ora[1])
        except ValueError:
            erori+="ora invalida\n"
        if ora<0 or ora>24 or minut<0 or minut>60:
            erori+="ora invalida\n"
        if len(erori)>0:
            raise Exception(erori)
def test_validator():
    ev=Eveniment("20.02.2021","08:00","Exam Fp")
    validator=Validator()
    try:
        validator.valideaza_eveniment(ev)
        assert True
    except Exception as ex:
        pass
    ev1=Eveniment("20.02.20","08:00","Exam Fp")
    try:
        validator.valideaza_eveniment(ev1)
        assert False
    except Exception as ex:
        assert (str(ex)=="an invalid\n")
    ev2 = Eveniment("20.02.2020", "80:00", "Exam Fp")
    try:
        validator.valideaza_eveniment(ev2)
        assert False
    except Exception as ex:
        assert (str(ex) == "ora invalida\n")
test_validator()