class Consola:
    def __init__(self,service):
        self.__service=service
        self.__comenzi={
            "adaugare":self.__ui_adaugare,
            "modificare":self.__ui_modificare,
            "random":self.__ui_random,
            "exporta":self.__ui_exporta
        }
    def __ui_exporta(self,params):
        if len(params)!=0:
            print("nr parametri invalid")
        fisier=input("introduceti numele fisier>>>")
        self.__service.exporta(fisier)
        print("exportat cu succes")
    def __ui_random(self,params):
        if len(params)!=0:
            print("nr parametri invalid")
        nr=input("introduceti nr de piese>>>")
        self.__service.random(nr)
        print("adaugat cu succes in fisier")
    def __ui_modificare(self,params):
        if len(params)!=4:
            print("nr parametri invalid")
        try:
            titlu=params[0]
            regizor=params[1]
            gen=params[2]
            durata=int(params[3])
        except Exception:
            print("parametri nu sunt ok")
        try:
            self.__service.modificare(titlu,regizor,gen,durata)
            print("modificat cu succes")
        except Exception as ex:
            print(f"{ex}")
    def __ui_adaugare(self,params):
        if len(params)!=4:
            print("nr parametri invalid")
        try:
            titlu=params[0]
            regizor=params[1]
            gen=params[2]
            durata=int(params[3])
        except Exception:
            print("parametri nu sunt ok")
        self.__service.adaugare(titlu,regizor,gen,durata)
        print("adaugat cu succes")
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
                    print(f"Uierror as {ex}")
            else:
                print("comanda invalida")

