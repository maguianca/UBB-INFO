class Consola:
    def __init__(self, service):
        self.__service = service
        self.__comenzi = {
            "adaugare":self.__ui_adaugare,
            "modificare":self.__ui_modificare,
            "random":self.__ui_random

        }
    def __ui_adaugare(self,params):
        if len(params)!=4:
            print("nr parametri invalid")
        else:
            try:
                titlu=params[0]
                artist=params[1]
                gen=params[2]
                durata=int(params[3])
            except Exception:
                print("paranetri nu sunt ok")
        self.__service.adaugare(titlu,artist,gen,durata)
        print("Adaugat cu succes")
    def __ui_modificare(self,params):
        if len(params)!=4:
            print("nr parametri invalid")
        else:
            try:
                titlu=params[0]
                artist=params[1]
                gen=params[2]
                durata=int(params[3])
            except Exception:
                print("paranetri nu sunt ok")
            try:
                self.__service.modificare(titlu,artist,gen,durata)
                print("Modificat cu succes")
            except Exception as ex:
                print(f"{ex}")
    def __ui_random(self,params):
        if len(params)!=1:
            print("nr parametri invalid")
        try:
            cifra=int(params[0])
        except Exception:
            print("nu e ok parametru")
        self.__service.random(cifra)
        print(f"adaugat cu succes {cifra} elemente")
    def run(self):
        while True:
            cmd=input(">>>")
            cmd.strip()
            if cmd=="exit":
                return
            if cmd=="":
                continue
            parts=cmd.split(" ")
            cmd_name =parts[0]
            params=parts[1:]
            if cmd_name in self.__comenzi:
                try:
                    self.__comenzi[cmd_name](params)
                except Exception as ex:
                    print(f"Uierror as {ex}")
            else:
                print("comanda invalida")