class Validator:
    def valideaza_produs(self,produs):

        erori = ""
        if produs.get_id()<0:
            erori += "id invalid!\n"
        if produs.get_denumire()=="":
            erori += "denumire invalid!\n"
        if produs.get_pret()<0:
            erori += "valoare invalida!\n"
        if len(erori)>0:
            raise Exception(erori)