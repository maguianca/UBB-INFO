from Domeniu.mobilier import Mobilier
class ValidatorMobilier:
    def valideaza(self,mobilier):

        erori=""
        cod=mobilier.get_cod()
        tip=mobilier.get_tip()
        nume=mobilier.get_nume()
        stock=mobilier.get_stock()
        pret=mobilier.get_pret()
        if cod=="":
            erori+="cod invalid\n"
        #if tip=="":
            #erori+="tip invalid\n"
        if tip not in ["corp iluminat","spatiu depozitare","canapea","scaun"]:
            erori+="format invalid\n"
        if nume=="":
            erori+="nume invalid\n"
        if type(stock)!=int or stock<0:
            erori+="stock invalid\n"
        if pret<1:
            erori+="pret invalid\n"
        if len(erori)>0:
            raise Exception(erori)
    def valideaza_tip(self,tip):
        erori=""
        if tip not in ["corp_iluminat","spatiu_depozitare","canapea","scaun"]:
            erori+="format invalid\n"
        if len(erori)>0:
            raise Exception(erori)