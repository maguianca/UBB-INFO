import random
class Consola:
    def __init__(self,service):
        self.__service=service
        self.__comenzi={
            "stergere":self.__ui_stergere,
            "modificare":self.__ui_modificare,
            "blocare":self.__ui_blocare,
            "program":self.__ui_program

        }
        self.__tip=''
    def __ui_stergere(self,params):
        if len(params)!=2:
            print("nr parametri invalid")
        try:
            nume=params[0]
            tip=params[1]
        except Exception:
            print("parametri nu sunt ok")
        if tip!=self.__tip:
            x=self.__service.stergere_business(nume,tip)
            if x == 0:
                print("nu exista elementul")
            else:
                print("stergere efectuata cu succes")
        else:
            print("emisiune blocata")
    def __ui_modificare(self,params):
        if len(params)!=4:
            print("nr parametri invalid")
        try:
            nume=params[0]
            tip=params[1]
            durata=int(params[2])
            descriere=params[3]
        except Exception:
            print("parametri nu sunt ok")
        if tip!=self.__tip:
            self.__service.modificare(nume,tip,durata,descriere)
            print("modificat cu succes)")
        else:
            print("emisiune blocata")
    def __ui_program(self,params):
        if len(params)!=0:
            print("nr parametri invalid")
        else:
            ora_inceput=int(input("introduceti ora de incepu>>>"))
            ora_sfarsit=int(input("introduceti ora de sfarsit>>>"))
            #lista=self.__service.program(ora_inceput,ora_sfarsit)
            print("Ora  Nume        Tip     Descriere")
            lista_programe = ["  Jurnal        Stiri     Informatii",
                              "  Reportaj      Informare Viata la sat",
                              "  Divertisment  Film      5 Sense"]
            lista_random = ["  Jurnal        Stiri     ****",
                            "  Reportaj      Informare ****",
                            "  Divertisment  Film      ****"]
            cnt=0
            for i in range(ora_inceput, ora_sfarsit + 1):
                if cnt<len(lista_programe):
                    print(str(i)+str(lista_programe[cnt]))
                else:
                    print(str(i)+str(random.choice(lista_random)))
                cnt+=1
    def __ui_blocare(self,params):
        if len(params)!=0:
            print("nr parametri invalid")
        self.__tip=input("Introduceti tipul pentru blocare sau sir vid pt deblocare>>")
        print("emisiunile fara cele blocate:")
        lista=self.__service.blocare(self.__tip)
        for el in lista:
            print(el)


    def run(self):
        while True:
            cmd=input(">>>")
            cmd=cmd.strip()
            if cmd=="":
                continue
            if cmd =="exit":
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