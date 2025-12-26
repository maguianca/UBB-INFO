class Consola:
    def __init__(self,service):
        self.__service=service
        self.__comenzi={
            "modificare":self.__ui_modificare,
            "adaugare_random":self.__ui_random,
            "export":self.__ui_export

        }
    def __ui_modificare(self,params):
        if len(params)!=4:
            print("nr parametri invalid")
        try:
            titlu=params[0]
            artist=params[1]
            gen=params[2]
            durata=int(params[3])
        except Exception:
            print("parametri nu sunt ok")
        try:
            self.__service.modificare(titlu,artist,gen,durata)
            print("modificare succes")
        except Exception as ex:
            print(f"{ex}")
    def __ui_random(self,params):
        if len(params)!=0:
            print("nr parametri invalid")
        nr=int(input("introduceti nr>>"))
        titluri=input("introduceti titlurile cu virgula intre ele>>>")
        artisti=input("introduceti artistii cu virgula intre ei>>>")
        self.__service.random(nr,titluri,artisti)
        print(f"{nr} melodii adaugate cu succes")
    def __ui_export(self,params):
        if len(params)!=0:
            print("nr parametri invalid")
        fisier=input("introduceti numele fisierului>>>")
        self.__service.export(fisier)
        print("melodiile au fost exportate")

    def run(self):
        while True:
            print("Optiunile dumneavoastra sunt: modificare,adaugare_random,export")
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