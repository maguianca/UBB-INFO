class Consola:
    def __init__(self,service):
        self.__service=service
        self.__sir=''
        self.__cifra=-1
        self.__undo=[]
        self.__comenzi={
            "adaugare":self.__ui_adaugare_produs,
            "stergere":self.__ui_stergere_produs,
            "filtrare":self.__ui_filtrare_produs,
            "undo":self.__ui_undo
        }
    def __ui_adaugare_produs(self,params):
        if len(params)!=3:
            print("nr parametri invalid")
        try:
            id=params[0]
            denumire=params[1]
            pret=float(params[2])
        except ValueError:
            print("parametri nu sunt ok")
        self.__service.add_produs(id,denumire,pret)
        print("produs adaugat cu succes")
    def __ui_stergere_produs(self,params):
        if len(params)!=1:
            print("nr parametri invalid")
        try:
            cifra=params[0]
        except ValueError:
            print("parametri nu sunt ok")
        self.__undo = self.__service.update_undo(self.__undo,cifra)
        x=self.__service.stergere_produs(cifra)
        print(f"s-au sters {x} produse")
    def __ui_filtrare_produs(self,params):
        if len(params)!=0:
            print("nr parametri invalid")
        self.__sir=input("introduceti un sir dupa care se va filtra sau enter>>>")
        self.__cifra=float(input("introduceti un suma dupa care se filtreaza sau -1>>>"))
        self.printeaza_filtrare()

    def printeaza_filtrare(self):

        lista = self.__service.filtrare(self.__sir,self.__cifra)
        if self.__sir != '' and self.__cifra > -1:
            print('Lista filtrata dupa subsirul '+self.__sir+' si pretul '+str(self.__cifra)+':')
        elif self.__sir == '' and self.__cifra >-1:
            print('Lista filtrata dupa pretul '+str(self.__cifra)+':')
        elif self.__sir != '' and self.__cifra == -1:
            print('Lista filtrata dupa subsirul '+self.__sir+':')
        else:
            print('Lista fara filtre aplicate:')

        for el in lista:
            print(el)

    def __ui_undo(self,params):
        if len(params)!=0:
            print("nr parametri invalid")
        try:
            self.__undo=self.__service.undo(self.__undo)
            print("s-a refacut ultima operatie")
        except ValueError as ve:
            print(str(ve))
        self.printeaza_filtrare()

    def run(self):
        while True:
            print("Optiunile dumneavoastra sunt: adaugare, stergere,filtrare,exit,undo")
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
