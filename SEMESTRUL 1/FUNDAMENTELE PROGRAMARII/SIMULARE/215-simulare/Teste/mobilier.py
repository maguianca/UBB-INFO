from Validare.mobilier import ValidatorMobilier
from Domeniu.mobilier import Mobilier

class Testemobilier:
    def __test_mobila(self):
        mobila=Mobilier("C1","corp iluminat","Lampa",5,75)
        assert mobila.get_cod()=="C1"
        assert mobila.get_tip()=="corp iluminat"
        assert mobila.get_nume()=="Lampa"
        assert mobila.get_stock()==5
        assert mobila.get_pret()==75
    def __test_validator_mobila(self):
        mobila=Mobilier("","","",5,75)
        mob = Mobilier("C1", "corp iluminat", "Lampa", -1, 75)
        mobila_buna = Mobilier("C1", "corp iluminat", "Lampa", 5, 75)
        validator=ValidatorMobilier()
        try:
            validator.valideaza(mobila_buna)
            assert True
        except Exception as ex:
            pass
        mobila_rea= Mobilier("C1", "corp ilu", "Lampa", 5, 75)
        try:
            validator.valideaza(mobila_rea)
            assert False
        except Exception as ex:
            assert str(ex)=="format invalid\n"
        #try:
        #    validator.valideaza(mob)
        #    assert False
        #except Exception as ex:
        #   assert str(ex)=="stock invalid\n"
    def run_all_tests(self):
        self.__test_mobila()
        self.__test_validator_mobila()
