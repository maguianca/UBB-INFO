class Consola:
    def __init__(self,service):
        self.__service=service
        self.__data=0
        self.__comenzi={
            "adaugare":self.__ui_adaugare,
            "afisare":self.__ui_afisare,
            "exporta":self.__ui_exporta
        }
    def __ui_afisare(self,params):
        if len(params)!=1:
            print("nr parametri invalid")
        data=params[0]
        self.__data=data
        self.default_afisare()
    def __ui_exporta(self,params):
        if len(params)!=0:
            print("nr parametri invalid")
        fisier=input("introduceti numele unui fisier>>>")
        caractere=input("introduceti descriere>>>")
        try:
            self.__service.exporta(fisier,caractere)
            print("exportate cu succes")
        except Exception as e:
            print(f"{e}")
    def default_afisare(self):
        if self.__data!=0:
            lista=self.__service.tabel(self.__data)
            for x in lista:
                print(x)

    def default(self):
        lista=self.__service.evenimente()
        print("Evenimentele de astazi:")
        for x in lista:
            print(x)
    def __ui_adaugare(self,params):
        if len(params)!=3:
            print("nr parametri invalid")
        try:
            data=params[0]
            ora=params[1]
            descriere=params[2]
        except Exception:
            print("parametri invalizi")
        try:
            self.__service.adaugare(data,ora,descriere)
            print("eveniment adaugat cu succes")
        except Exception as ex:
            print(f"{ex}")
        self.default_afisare()
    def run(self):
        self.default()
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