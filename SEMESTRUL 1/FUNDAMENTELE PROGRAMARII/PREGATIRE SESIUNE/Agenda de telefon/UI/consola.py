class Consola:
    def __init__(self,service):
        self.__service=service
        self.__comenzi={
            "adaugare":self.__ui_adaugare,
            "cautare":self.__ui_cautare,
            "filtrare":self.__ui_filtrare,
            "exporta":self.__ui_exporta

        }
    def __ui_exporta(self,params):
        if len(params)!=1:
            print("nr parametri invalid")
        try:
            grup=params[0]
        except Exception:
            print("nu e ok parametrul")
        self.__service.exporta(grup)
        print("export cu succes")
    def __ui_filtrare(self,params):
        if len(params)!=1:
            print("nr parametri invalid")
        try:
            tip=params[0]
        except Exception :
            print("parametru invalid")
        lista=self.__service.filtrare(tip)
        if lista!=[]:
            for el in lista:
                print(el)
        else:
            print(f"nu exista numere cu {tip}")
    def __ui_adaugare(self,params):
        if len(params)!=4:
            print("nr parametri invalid")
        try:
            id=params[0]
            nume=params[1]
            nrtel=params[2]
            grup=params[3]
        except Exception :
            print("nr parametri invalid")
        self.__service.adaugare(id,nume,nrtel,grup)
        print("adaugat cu succes")
    def __ui_cautare(self,params):
        if len(params)!=1:
            print("nr parametri invalid")
        try:
            nume=params[0]
        except Exception:
            print("parametru invalid")
        try:
            x=self.__service.cautare(nume)
            print(x)
        except Exception:
            print("Nu exista nume asociat unui nr tel")
    def run(self):
        while True:
            cmd=input(">>>")
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
                    print(f"UIerror as {ex}")
            else:
                print("comanda invalida")