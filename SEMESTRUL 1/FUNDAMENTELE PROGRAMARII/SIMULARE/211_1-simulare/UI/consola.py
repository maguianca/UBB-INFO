class Consola:
    def __init__(self,service):
        self.__service=service
        self.__comenzi={
            "filtrare":self.__ui_filtrare,
            "filtrare_dupa_buget":self.__ui_fil,
            "inchiriere":self.__ui_inchiriere,
            "cautare":self.__ui_cautare
        }

    def __ui_cautare(self,params):
        if len(params)!=1:
            print("nr parametri invalid")
        try:
            id=int(params[0])
        except Exception as ex:
            raise Exception("tipuri invalid")
        l=self.__service.cautare(id)
        print("id:",str(l.get_id()),"adresa:",str(l.get_adresa()),"oras:","pret:",str(l.get_pret()),"garantie:",str(l.get_garantie()))

    def __ui_fil(self,params):
        if len(params) !=0:
            print("nr parametri invalid")
        lista = self.__service.filtrare_dupa_buget()
        for l in lista:
            print("id:", str(l.get_id()), "adresa:", str(l.get_adresa()), "oras:", "pret:", str(l.get_pret()), "garantie:",
                 str(l.get_garantie()))

    def __ui_filtrare(self,params):
        if len(params)!=2:
            print("nr parametri invalid")
        try:
            buget=float(params[0])
            oras=params[1]
        except Exception as ex:
            raise Exception("tipuri invalid")
        lista=self.__service.filtrare(buget,oras)
        for l in lista:
            print("id:",str(l.get_id()),"adresa:",str(l.get_adresa()),"oras:","pret:",str(l.get_pret()),"garantie:",str(l.get_garantie()))

    def __ui_inchiriere(self,params):
        if len(params)!=1:
            raise Exception("nr parametri invalid")
        try:
            id=int(params[0])
        except Exception as ex:
            raise Exception("id invalid")
        l=self.__service.inchiriere(id)
        print(str(l.get_id()),str(l.get_adresa()),str(l.get_oras()),str(l.get_calcul()))

    def run(self):
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
                    print(f"Uierror as {ex}")
            else:
                print("comanda invalida")