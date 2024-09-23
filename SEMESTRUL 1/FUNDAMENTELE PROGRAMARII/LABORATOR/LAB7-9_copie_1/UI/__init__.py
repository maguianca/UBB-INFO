from UI.laborator import UIL
from UI.studenti import UIS

class Consola:
    def __init__(self,consola_laborator,consola_studenti):
        self.__consola_studenti= consola_studenti
        self.__consola_laborator=consola_laborator

    def run(self):
        while True:
            cmd = input(">>>")
            cmd = cmd.strip()
            if cmd == "exit":
                return
            parts = cmd.split(" ")
            cmd_name = parts[0]
            params = parts[1:]
            """if len(parts)>1:
                params = parts[1]
            else:
                params=[]"""
            if cmd_name in self.__consola_studenti.commandz:
                try:
                    self.__consola_studenti.commandz[cmd_name](params)
                except Exception as ex:
                    print(ex)
            elif cmd_name in self.__consola_laborator.commandz:
                try:
                    self.__consola_laborator.commandz[cmd_name](params)
                except Exception as ex:
                    print(ex)
            else:
                print("Comanda nu este cunoscuta. Va rugam sa reincercati!")
