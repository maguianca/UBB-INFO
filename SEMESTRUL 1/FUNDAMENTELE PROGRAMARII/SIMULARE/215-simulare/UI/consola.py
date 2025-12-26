
class Consola:
    def __init__(self,service_mobila):
        self.__service_mobila=service_mobila
        self.__comenzi={
            "adauga_mobilier":self.__ui_adauga_mobilier,
            "cautare_mobilier":self.__ui_cautare_mobilier,
            "cumparare_mobilier":self.__ui_cumparare_mobilier
        }
    def __ui_adauga_mobilier(self,params):
        pass
    def __ui_cautare_mobilier(self,params):
        if len(params)!=1:
            print("nr parametri invalid")
            return
        try:
            tip=params[0]
            #lista=self.__service_mobila.cautare(tip)
        except Exception as ex:
            raise Exception("parametri invalid")
        lista = self.__service_mobila.cautare(tip)
        for l in lista:
            print("cod:",str(l.get_cod()),"nume:",str(l.get_nume()),"stock:",str(l.get_stock()),"pret:",str(l.get_pret()))
    def __ui_cumparare_mobilier(self,params):
        if len(params)!=2:
            print("nr parametri invalid")
            return
        try:
            cod=params[0]
            numar=int(params[1])
        except Exception as ex:
            raise Exception("parametri invalid")
        l=self.__service_mobila.cumpara(cod,numar)
        print("nume:",str(l.get_nume()),"pret:",str(l.get_pret()),"stock:",str(l.get_stock()))
        #lista=self.__service_mobila.get_all()
        #print(str(lista[cod]),"pret:",l)
        #print("nume",str(lista.get_nume()),"pret:",str(lista.get_pret_total()),"stock:",str(lista.get_stock_total()))
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