class Consola:
    def __init__(self,service):
        self.__service=service
        self.__comenzi={
            "afisare":self.__ui_afisare,
            "statistici":self.__ui_statistici
        }
    def __ui_afisare(self,params):
        """
        apeleaza business-filtrare
        :param params: data string
        :return:
        """
        if len(params)!=1:
            print("nr parametri invalid")
        try:
            data=params[0]
        except Exception as ex:
            print("data invalida")
        lista=self.__service.filtrare(data)
        for l in lista:
            print("id:",str(l.get_id()),"nume:",str(l.get_nume()),"data:",str(l.get_data()),"locatie:",
                  str(l.get_locatie()),"ani:",str(l.get_life()))

    def __ui_statistici(self,params):
        """
        creaza statistica, apeleaza business cu functia statistica
        :param params: none
        """
        if len(params)!=0:
            print("nr parametri invalid")
        lista=self.__service.statistica()
        for l in lista:
            print("tip",str(lista[l].get_tip()),   "nume:", str(lista[l].get_nume()),"medie:", str(lista[l].get_medie()))
    def run(self):
        """metoda necesara pentru pornirea programului"""
        while True:
            cmd=input(">>>")
            cmd=cmd.strip()
            if cmd=="exit":
                return
            if cmd=="":
                continue
            parts=cmd.split()
            cmd_name=parts[0]
            params=parts[1:]
            if cmd_name in self.__comenzi:
                try:
                    self.__comenzi[cmd_name](params)
                except Exception as ex:
                    print(f"Uierror as {ex}")
            else:
                print("comanda necunoscuta")