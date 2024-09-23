from Domeniu.teatru import Piesa
class Validator:
    def validator_piesa(self,piesa):
        erori=""
        if piesa.get_durata()<=0:
            erori+="durata invalida\n"
        if piesa.get_gen() not in ["Comedie","Satira","Altele","Drama"]:
            erori+="gen invalid\n"
        if piesa.get_titlu()=="":
            erori+="titlu invalid\n"
        if piesa.get_regizor()=="":
            erori+="regizor invalid\n"
        if len(erori)>0:
            raise Exception(erori)
def test_validator():
    piesa=Piesa("Ema","","Com",2)
    val=Validator()
    try:
        val.validator_piesa(piesa)
        assert False
    except Exception as ex:
        assert str(ex)=="gen invalid\nregizor invalid\n"
    buna = Piesa("Ema", "Pop", "Comedie", 2)
    try:
        val.validator_piesa(buna)
        assert True
    except Exception as ex:
        pass
test_validator()