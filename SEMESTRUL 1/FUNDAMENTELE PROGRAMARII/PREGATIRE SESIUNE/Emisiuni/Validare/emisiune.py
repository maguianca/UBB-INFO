class Validator:
    def valideaza_emisiune(self,emisiune):
        erori=""
        if emisiune.get_nume()=="":
            erori+="nume invalid\n"
        if emisiune.get_descriere()=="":
            erori+="descriere invalid\n"
        if emisiune.get_durata()<=0:
            erori+="durata invalid\n"
        if emisiune.get_tip()=="":
            erori+="tip invalid\n"
        if len(erori)>0:
            raise Exception(erori)