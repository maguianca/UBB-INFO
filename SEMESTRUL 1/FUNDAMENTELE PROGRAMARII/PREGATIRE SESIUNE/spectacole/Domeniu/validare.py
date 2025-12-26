class Validator:
    def valideaza_spectacol(self,spectacol):
        erori=""
        if spectacol.get_gen() not in ["Comedie","Concert","Balet","Altele"]:
            erori+="gen invalid\n"
        if spectacol.get_titlu()=="":
            erori+="titlu invalid\n"
        if spectacol.get_artist()=="":
            erori+="artist invalid\n"
        if spectacol.get_durata()<=0:
            erori+="durata invalid\n"
        if len(erori)>0:
            raise Exception(erori)
