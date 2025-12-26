class Consola:
    def __init__(self,service):
        self.__service=service
        self.__undo=[]
        self.__sir=""
        self.__numar=-1
        self.__comenzi={
            "adaugare":self.__ui_adaugare,
            "stergere":self.__ui_stergere,
            "filtrare":self.__ui_filtrare,
            "undo":self.__ui_undo
        }
    def __ui_undo(self,params):
        if len(params)!=0:
            print("nr parametri invalid")
        else:
            try:
                self.__undo=self.__service.undo(self.__undo)
                print("operatia de undo s-a facut cu succes")
            except Exception as ex:
                print(f"{ex}")
    def __ui_filtrare(self,params):
        if len(params)!=0:
            print("nr parametri invalid")
        else:
            text=input("introduceti un text>>>")
            an=int(input("introduceti anul>>> "))
            self.__sir=text
            self.__numar=an
            self.printeaza_filtrare()
    def printeaza_filtrare(self):
        if self.__sir == "" and self.__numar == -1:
            print("lista fara filtre aplicate:")
        elif self.__sir != "" and self.__numar != -1:
            print(f"lista filtatrata cu text {self.__sir} si an mai mic {self.__numar}")
        elif self.__sir != "" and self.__numar == -1:
            print(f"lista filtatrata cu text {self.__sir}")
        elif self.__sir == "" and self.__numar != -1:
            print(f"lista filtatrata cu an mai mic {self.__numar}")
        lista=self.__service.filtrare(self.__sir,self.__numar)
        for el in lista:
            print(el)
    def __ui_stergere(self,params):
        if len(params)!=1:
            print("nr parametri invalid")
        else:
            try:
                cifra=int(params[0])
            except Exception:
                print("nu e ok")
            self.__undo = self.__service.update_undo(self.__undo, cifra)
            self.__service.stergere(cifra)
            print("stergere cu succes")
    def __ui_adaugare(self,params):
        if len(params)!=4:
            print("nr parametri invalid")
        else:
            try:
                id=int(params[0])
                titlu=params[1]
                autor=params[2]
                an=int(params[3])
            except Exception as ex:
                print("nu sunt ok")
            self.__service.adaugare(id,titlu,autor,an)
            print("carte adaugata cu succes")
    def run(self):
        self.printeaza_filtrare()
        while True:
            cmd=input("Optiunile dvs sunt:adaugare,stergere,undo,filtrare>>>")
            cmd=cmd.strip()
            if cmd=="exit":
                return
            if cmd=="":
                continue
            parts=cmd.split(" ")
            cmd_name=parts[0]
            params=parts[1:]
            if cmd_name in self.__comenzi:
                try:
                    self.__comenzi[cmd_name](params)
                except Exception as ex:
                    print(f"Uierror as {ex}")
            else:
                 print("comanda invalida")