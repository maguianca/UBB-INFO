class Consola:
    def __init__(self,service):
        self.__service=service
        self.__comenzi={
            "afisare_pacienti":self.__ui_afisare_pacienti,
            "afisare_internari": self.__ui_afisare_internari
        }

    def __ui_afisare_pacienti(self,params):
        """
        functie care apeleaza functia din service afisare_pacienti
        :param params: nume-string
        :return: printeaza persoanele (id,adresa,data nasterii)
        """
        if len(params)!=1:
            print("nr parametri invalid")
        try:
            nume=params[0]
        except Exception as ex:
            print("nume invalid")
        lista=self.__service.afisare_pacienti(nume)
        for l in lista:
            print("id:",str(l.get_id()),"adresa:",str(l.get_adresa()),"data nasterii:",str(l.get_data()))
    def __ui_afisare_internari(self,params):
        """
        functie care apeleaza din service afisare_internari
        :param params: none
        :return: printeaza numele,data_nasterii si nr internari
        """
        if len(params)!=0:
            print("nr parametri invalid")
        lista=self.__service.afisare_internari()
        for l in lista:
            print("nume:",str(l.get_nume()),"data:",l.get_data_nasterii(),"internari:",l.get_internari())
    def run(self):
        """functie care reprezinta meniul programului, ruleaza pana cand utilizatorul da comanda exit"""
        while True:
            cmd=input(">>>")
            cmd=cmd.strip()
            if cmd=="":
                continue
            if cmd=="exit":
                return
            parts=cmd.split()
            cmd_name=parts[0]
            params=parts[1:]
            if cmd_name in self.__comenzi:
                try:
                    self.__comenzi[cmd_name](params)
                except Exception as ex:
                    print(f"UIerror as {ex}")
            else:
                print("comanda invalida")
