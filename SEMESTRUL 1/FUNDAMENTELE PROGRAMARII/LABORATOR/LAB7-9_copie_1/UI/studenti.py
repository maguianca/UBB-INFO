from Business.studenti import StudentiBusiness

class UIS:

    def __init__(self,service_studenti):
        self.__service_studenti = service_studenti
        self.commandz = {
            "adauga_studenti":self.__ui_add_student,
            "afiseaza_studenti":self.__ui_print_student,
            "modifica_studenti":self.__ui_modifica_student,
            "stergere_studenti":self.__ui_stergere_student
        }
    def __ui_modifica_student(self,params):
        if(len(params)!=2):
            print("nr parametri invalid!")
            return
        try:
            id_student = int(params[0])
            nume = params[1]
            #grup = int(params[2])
        except ValueError:
            raise Exception("valoare numerica invalida!")
        self.__service_studenti.modifica_student(id_student, nume)

    def __ui_print_student(self,params):
        if len(params)!=0:
            print("nr parametri invalid!")
            return
        studenti = self.__service_studenti.get_all_studenti()
        for student in studenti:
            print(student)
    def __ui_add_student(self,params):
        if len(params)!=2:
            print("nr parametri invalid!")
            return
        try:
            id_student = int(params[0])
            nume = params[1]
            #grup = int(params[2])
        except ValueError:
            raise Exception("valoare numerica invalida!")
        self.__service_studenti.add_student(id_student,nume)
        print("student adaugat cu succes!")

    def __ui_stergere_student(self,params):
        if len(params)!=1:
            print("nr parametrii invalid!")
            return
        try:
            id_student=int(params[0])
        except ValueError:
            raise Exception("valoare numerica invalida!")
        self.__service_studenti.stergere_student(id_student)
        print("comanda executata cu succes")

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
