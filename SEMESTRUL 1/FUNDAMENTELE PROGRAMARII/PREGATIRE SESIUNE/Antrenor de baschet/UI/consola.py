class Consola:
    def __init__(self,service):
        self.__service=service
        self.__comenzi={
            "adaugare":self.__ui_adaugare,
            "modificare":self.__ui_modificare,
            "filtrare":self.__ui_filtrare,
            "importa":self.__ui_importa
        }
    def __ui_importa(self,params):
        if len(params)!=0:
            print("nr parametri invalid")
        fisier=input("Introduceti numele fisierului din care se vor importa nume>>>")
        fisier=fisier.strip()
        x=self.__service.importa(fisier)
        print(f"{x} persoane importate cu succes")
    def __ui_filtrare(self,params):
        if len(params)!=0:
            print("nr parametri invalid")
        lista=self.__service.filtrare()
        print("Prenume,Nume,Post,Inaltime")
        for x in lista:
            print(str(x.get_prenume())+","+str(x.get_nume())+","+str(x.get_post())+","+str(x.get_inaltime()))
    def __ui_modificare(self,params):
        if len(params)!=3:
            print("nr parametri invalid")
        try:
            nume=params[0]
            prenume=params[1]
            inaltime=int(params[2])
        except Exception:
            print("datele nu sunt ok")
        try:
            self.__service.modificare(nume,prenume,inaltime)
            print("jucator modificat cu succes")
        except Exception:
            print("nu exista jucatorul introdus")

    def __ui_adaugare(self,params):
        if len(params)!=4:
            print("nr parametri invalid")
        try:
            nume=params[0]
            prenume=params[1]
            inaltime=int(params[2])
            post=params[3]
        except Exception:
            print("datele nu sunt ok")
        self.__service.adaugare(nume,prenume,inaltime,post)
        print("jucator adaugat cu succes")
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
