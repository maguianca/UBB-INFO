class Consola:
    def __init__(self,service):
        self.__service=service
        self.__comenzi={
            "salvare":self.__ui_salvare,
            "vanzare":self.__ui_vanzare
        }
    def __ui_salvare(self,params):
        if len(params)!=1:
            print("nr parametri invalid")
        try:
            valoare=int(params[0])
        except Exception as ex:
            print("tip invalid")
        self.__service.salvare(valoare)
        print(f"salvare in fisier salvare.txt executate cu succes!")
    def __ui_vanzare(self,params):
        if len(params)!=2:
            print("nr parametri invalid")
        try:
            cod=int(params[0])
            cantitate=int(params[1])
        except Exception as ex:
            print("date invalide")
        x=self.__service.vanzare(cod,cantitate)
        if x==0:
            print("operatia nu s-a putut executa")
        else:
            print("salvare in fisier salvare.txt executata cu succes!")
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