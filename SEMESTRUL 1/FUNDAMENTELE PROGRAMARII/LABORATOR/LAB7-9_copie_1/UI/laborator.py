from Business.laborator import LaboratoareBusiness


class UIL:

    def __init__(self,service_laboratoare):
        self.__service_laboratoare = service_laboratoare
        self.commandz = {
            "adauga_laborator":self.__ui_add_laborator,
            "afiseaza_laborator":self.__ui_print_laborator,
            "stergere_laborator":self.__ui_stergere_laborator,
            "modifica_laborator":self.__ui_modifica_laborator
        }

    def __ui_print_laborator(self,params):
        if len(params)!=0:
            print("nr parametri invalid!")
            return
        laboratoare = self.__service_laboratoare.get_all_laboratoare()
        for lab in laboratoare:
            print(lab)
    def __ui_add_laborator(self,params):
        if len(params)!=3:
            print("nr parametri invalid!")
            return
        try:
            numar = int(params[0])
            descriere = params[1]
            deadline = params[2]
        except ValueError:
            raise Exception("date invalide!")
        self.__service_laboratoare.add_laborator(numar,descriere,deadline)
        print("laborator adaugat cu succes!")

    def __ui_stergere_laborator(self, params):
        if len(params) != 1:
            print("nr parametrii invalid!")
            return
        try:
            numar = int(params[0])
        except ValueError:
            raise Exception("date invalide!")
        self.__service_laboratoare.stergere_laborator(numar)
        print("comanda executata cu succes")

    def __ui_modifica_laborator(self, params):
        if (len(params) != 3):
            print("nr parametri invalid!")
            return
        try:
            numar = int(params[0])
            descriere = params[1]
            deadline = params[2]
        except ValueError:
            raise Exception("date invalide!")
        self.__service_laboratoare.modifica_laborator(numar,descriere,deadline)
        print("comanda executata cu succes!")

    """def run(self):
        while True:
            cmd = input(">>>")
            cmd = cmd.strip()
            if cmd == "exit":
                return
            parts = cmd.split(" ")
            cmd_name = parts[0]
            params = parts[1:]
            if cmd_name in self.__commandz:
                try:
                    self.__commandz[cmd_name](params)
                except Exception as ex:
                    print(ex)
            else:
                print("comanda invalida!")"""
