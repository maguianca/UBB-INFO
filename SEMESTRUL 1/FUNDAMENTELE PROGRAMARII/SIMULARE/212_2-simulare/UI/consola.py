class Consola:
    def __init__(self,service):
        self.__service=service
        self.__comenzi={
            "media":self.__ui_media,
            "tranzactie":self.__ui_tranzactie
        }
    def __ui_media(self,params):
        if len(params)!=1:
            print("nr parametri invalid")
        try:
            tip=params[0]
        except Exception as ex:
            print("tip invalid")
        media=self.__service.media(tip)
        print(media)
    def __ui_tranzactie(self,params):
        if len(params)!=2:
            print("nr parametri invalid")
        try:
            id=int(params[0])
            pret=int(params[1])
        except Exception as ex:
            print("tipuri invalide")
        dto=self.__service.inchiriere(id,pret)
        print("adresa:",str(dto.get_adresa()),"comision:",str(dto.get_comision()))
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
                    print(f"UIerror as {ex}")
            else:
                print("comanda invalida")