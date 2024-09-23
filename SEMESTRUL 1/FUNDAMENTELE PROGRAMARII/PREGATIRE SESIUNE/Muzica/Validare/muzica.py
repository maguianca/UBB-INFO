class Validare:
    def valideaza_melodie(self,melodie):
        erori=""
        if melodie.get_durata()<=0:
            erori+="durata trb sa fie pozitiva\n"
        if melodie.get_gen() not in ["Rock","Pop","Jazz","Altele"]:
            erori+="genul nu e acceptat"
        if len(erori)>0:
            raise Exception(erori)