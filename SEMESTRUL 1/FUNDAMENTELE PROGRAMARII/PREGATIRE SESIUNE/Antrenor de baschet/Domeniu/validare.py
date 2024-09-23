from Domeniu.baschet  import Jucator
class Validator:
    def valideaza_jucator(self,jucator):
        erori=""
        if jucator.get_nume()=="":
            erori+="nume invalid\n"
        if jucator.get_prenume()=="":
            erori+="prenume invalid\n"
        if jucator.get_inaltime()<=0:
            erori+="inaltime invalida\n"
        if jucator.get_post() not in ["Fundas","Pivot","Extrema"]:
            erori+="post invalid\n"
        if len(erori)>0:
            raise Exception(erori)
def test_validator():
    juc=Jucator("Michael","",-2,"Fund")
    val=Validator()
    try:
        val.valideaza_jucator(juc)
        assert False
    except Exception as ex:
        assert str(ex)=="prenume invalid\ninaltime invalida\npost invalid\n"
    juc1 = Jucator("Michael", "Jordan", 210, "Fundas")
    try:
        val.valideaza_jucator(juc1)
        assert True
    except Exception as ex:
        pass
test_validator()
