from Exceptii.ui_error import UIError
from Business import *
class Consola:
        def __init__(self,service_studenti,service_laborator,service_note):
            self.__service_studenti=service_studenti
            self.__service_laboratoare=service_laborator
            self.__service_note=service_note
            self.__commandz = {
                "adauga_laborator": self.__ui_add_laborator,
                "afiseaza_laborator": self.__ui_print_laborator,
                "stergere_laborator": self.__ui_stergere_laborator,
                "modifica_laborator": self.__ui_modifica_laborator,
                "cautare_laborator": self.__ui__cautare_laborator,
                "adauga_studenti": self.__ui_add_student,
                "afiseaza_studenti": self.__ui_print_student,
                "modifica_studenti": self.__ui_modifica_student,
                "stergere_studenti": self.__ui_stergere_student,
                "cautare_studenti": self.__ui__cautare_student,
                "generare_studenti": self.__ui__generare_student,
                "asignare_laborator":self.__ui__asignare_laborator,
                "afisare_note":self.__ui__afisare_note,
                "notare_laborator":self.__ui__notare_laborator,
                "statistica_problema":self.__ui__statistica_problema,
                "statistica_corigenti":self.__ui__statistica_corigenti
            }

        def printeaza_recursiv_fara_nota(self, lista_stud, index=0):
            """
            printeaza recursiv o lista de studenti fara nota doar cu problema asignata
            :param lista_stud: Lista de obiecte de tip nota
            :param index: indexul listei de studenti
            :return: None
            """
            if index < len(lista_stud):
                lab = lista_stud[index]

                if lab.get_nota() == 0:
                    print('Student: [', str(lab.get_student().get_id_student()), '; ',
                          str(lab.get_student().get_nume()), ']',
                          'Laborator: [', str(lab.get_laborator().get_numar()), ';',
                          str(lab.get_laborator().get_descriere()), ']')

                self.printeaza_recursiv_fara_nota(lista_stud,index + 1)

        def printeaza_recursiv(self, lista_stud, index=0):
            """
            printeaza recursiv o lista de studenti cu nota la o problema asignata
            :param lista_stud: Lista de obiecte de tip nota
            :param index: indexul listei de studenti
            :return: None
            """
            if index < len(lista_stud):
                lab = lista_stud[index]

                if lab.get_nota() != 0:
                    print('Student: [', str(lab.get_student().get_id_student()), '; ',
                          str(lab.get_student().get_nume()), ']',
                          'Laborator: [', str(lab.get_laborator().get_numar()), ';',
                          str(lab.get_laborator().get_descriere()), ']')

                self.printeaza_recursiv(lista_stud, index + 1)

        def __ui__statistica_corigenti(self,params):
            """
                apeleaza service raport corigenti
                afiseaza studentii cu media notelor de la laborator sub 5
                :param params: string
                :return: value error daca nu sunt de tipul precizat si mesaj sugestiv
            """
            ok=0
            if len(params)!=0:
                print("nr parametri invalid!")
                return
            try:
                lista = self.__service_note.raport_corigenti()
            except ValueError:
                raise UIError("nr parametri invalid!")
            print(f'Lista cu studentii care au media problemelor de laborator sub 5 este:\n')
            for lab in lista:
                print('Student:',str(lab.get_nume()), 'Nota: ', str(
                        lab.get_medie_nota()))
                ok=1
            if ok==0:
                print('nu sunt studenti\n')

        def __ui__statistica_problema(self,params):
            """
                imparte parametrul params in id_laborator si afiseaza notele studentilor
                apeleaza service rapor
                :param params: string
                :return: value error daca nu sunt de tipul precizat si mesaj sugestiv
            """
            if len(params)!=1:
                print("nr parametri invalid\n")
                return
            try:
                id_laborator=params[0]
                lista=self.__service_note.raport_problema(id_laborator)
            except ValueError:
                raise UIError("nr parametri invalid!\n")
            print(f'Lista cu studentii care au avut de rezolvat problema {id_laborator} este:\n')
            for lab in lista:
                print('Student: [', str(lab.get_id()), '; ',
                      str(lab.get_nume()), ']', 'Nota: ', str(
                        lab.get_nota()))
        def __ui__notare_laborator(self,params):
            """
                imparte parametrul params in id_student,id_laborator,nota
                apeleaza service notare
                :param params: string
                :return: value error daca nu sunt de tipul precizat si mesaj sugestiv
            """
            if(len(params)!=3):
                print("nr parametri invalid!\n")
                return
            try:
                id_student = int(params[0])
                id_laborator = params[1]
                nota=float(params[2])
                final = self.__service_note.notare_laborator(id_student, id_laborator,nota)
            except ValueError:
                raise UIError("parametri invalizi!\n")
            print(f'studentul {id_student} a primit nota la laboratorul{id_laborator}\n')
        def __ui__afisare_note(self,params):
            """
                afiseaza note
                :param params: string
                :return: value error daca nu sunt de tipul precizat si mesaj sugestiv
            """
            ok=0
            if len(params)!=0:
                    print("nr parametri invalid!\n")
                    return

            lista=self.__service_note.get_all()
            if len(lista) == 0:
                print('Lista de teme este goala.\n')
            else:
                print('Catalogul cu note este:\n')
                """for lab in lista:
                    if lab.get_nota()!=0:
                        print('Student: [', str(lab.get_student().get_id_student()), '; ',
                              str(lab.get_student().get_nume()), ']',
                              'Laborator: [', str(lab.get_laborator().get_numar()), ';',
                              str(lab.get_laborator().get_descriere()), ']', 'Nota: ', str(
                                lab.get_nota()))"""
                self.printeaza_recursiv(lista)
                print('Studentii fara nota:(in curs de notare..)')
                """for lab in lista:
                    if lab.get_nota()==0:
                        print('Student: [', str(lab.get_student().get_id_student()), '; ',
                              str(lab.get_student().get_nume()), ']',
                              'Laborator: [', str(lab.get_laborator().get_numar()), ';',
                              str(lab.get_laborator().get_descriere()), ']')
                        ok=1"""
                self.printeaza_recursiv_fara_nota(lista)
                if ok==0:
                    print('toti studentii au note la problemele asignate\n')

        def __ui__asignare_laborator(self,params):
            """
                imparte parametrul params in id_student,id_laborator
                apeleaza service asignare
                :param params: string
                :return: value error daca nu sunt de tipul precizat si mesaj sugestiv
            """
            if len(params)!=2:
                print("nr parametri invalid!\n")
                return
            try:
                id_student=int(params[0])
                id_laborator=params[1]
                final=self.__service_note.asignare_laborator(id_student,id_laborator)
            except ValueError:
                raise UIError("parametri invalizi!")
            print(f'laboratorul {id_laborator} a fost asignat cu succes la studentul cu nr{id_student}')

        def __ui__cautare_laborator(self, params):
            """
            cauta un lab duoa numar
            apeleaza service
            :param params: string
            :return: value error daca atributele nu sunt de tipul precizat
            """
            if len(params) != 1:
                print("nr parametri invalid!")
                return
            try:
                numar = params[0]
                lab = self.__service_laboratoare.cauta_laborator(numar)
                print(lab)
            except ValueError:
                raise UIError("valoare numerica invalida!")

        def __ui_print_laborator(self, params):
            """
            verifica daca params e vid
            :param params: string
            :return:value error daca atributele nu sunt de tipul precizat  altfel printeaza elementele din laborator
            si mesaj sugestiv
            """
            if len(params) != 0:
                print("nr parametri invalid!")
                return
            laboratoare = self.__service_laboratoare.get_all_laboratoare()
            for lab in laboratoare:
                print(lab)

        def __ui_add_laborator(self, params):
            """
            imparte parametrul params in numar,descriere,deadline
            apeleaza service adaugare
            :param params: string
            :return: value error daca nu sunt de tipul precizat si mesaj sugestiv
            """
            if len(params) != 3:
                print("nr parametri invalid!")
                return
            try:
                numar = params[0]
                descriere = params[1]
                deadline = params[2]
            except ValueError:
                raise UIError("date invalide!")
            self.__service_laboratoare.add_laborator(numar, descriere, deadline)
            print("laborator adaugat cu succes!")

        def __ui_stergere_laborator(self, params):
            """
            imparte parametrul params in numar
            apeleaza service adaugare
            :param params: string
            :return: value error daca nu sunt de tipul precizat si mesaj sugestiv
            """
            if len(params) != 1:
                print("nr parametrii invalid!")
                return
            try:
                numar = params[0]
            except ValueError:
                raise UIError("date invalide!")
            self.__service_laboratoare.stergere_laborator(numar)
            print("comanda executata cu succes")

        def __ui_modifica_laborator(self, params):
            """
                    imparte parametrul params in numar,descriere,deadline
                    apeleaza service
                    :param params: string
                    :return:value error daca atributele nu sunt de tipul precizat  si mesaj sugestiv
            """
            if (len(params) != 3):
                print("nr parametri invalid!")
                return
            try:
                numar = params[0]
                descriere = params[1]
                deadline = params[2]
            except ValueError:
                raise UIError("date invalide!")
            self.__service_laboratoare.modifica_laborator(numar, descriere, deadline)
            print("comanda executata cu succes!")

        def __ui__generare_student(self, params):
            """
                imparte parametrul params in numar
                apeleaza service generare
                :param params: string
                :return: value error daca nu sunt de tipul precizat si mesaj sugestiv
            """
            if len(params) != 1:
                print("nr parametri invalid!")
                return
            try:
                numar = int(params[0])
            except ValueError:
                raise UIError("valoare numerica invalida!")
            self.__service_studenti.generare_studenti(numar)
            print("generare facuta cu succes")

        def __ui__cautare_student(self, params):
            """
            cauta un student duoa id
            apeleaza service
            :param params: string
            :return: value error daca atributele nu sunt de tipul precizat
            """
            if len(params) != 1:
                print("nr parametri invalid!")
                return
            try:
                id_student = int(params[0])
                stud = self.__service_studenti.cauta_student(id_student)
                print(stud)
            except ValueError:
                raise UIError("valoare numerica invalida!")

        def __ui_modifica_student(self, params):
            """
            imparte parametrul params in id,nume,grup
            apeleaza service
            :param params: string
            :return:value error daca atributele nu sunt de tipul precizat si mesaj sugestiv
            """
            if (len(params) != 3):
                print("nr parametri invalid!")
                return
            try:
                id_student = int(params[0])
                nume = params[1]
                grup = int(params[2])
            except ValueError:
                raise UIError("valoare numerica invalida!")
            self.__service_studenti.modifica_student(id_student, nume, grup)

        def __ui_print_student(self, params):
            """
             verifica daca params e vid
            :param params: string
            :return:value error daca atributele nu sunt de tipul precizat  altfel printeaza elementele din laborator
            si mesaj sugestiv
            """
            if len(params) != 0:
                print("nr parametri invalid!")
                return
            studenti = self.__service_studenti.get_all_studenti()
            for student in studenti:
                print(student)

        def __ui_add_student(self, params):
            """
                   imparte parametrul params in id,nume,grup
                   apeleaza service adaugare
                   :param params: string
                   :return: value error daca nu sunt de tipul precizat si mesaj sugestiv
                """
            if len(params) != 3:
                print("nr parametri invalid!")
                return
            try:
                id_student = int(params[0])
                nume = params[1]
                grup = int(params[2])
            except ValueError:
                raise UIError("valoare numerica invalida!")
            self.__service_studenti.add_student(id_student, nume, grup)
            print("student adaugat cu succes!")

        def __ui_stergere_student(self, params):
            """
                   imparte parametrul params in id
                   apeleaza service adaugare
                   :param params: string
                   :return: value error daca nu sunt de tipul precizat si mesaj sugestiv
                   """
            if len(params) != 1:
                print("nr parametrii invalid!")
                return
            try:
                id_student = int(params[0])
            except ValueError:
                raise UIError("valoare numerica invalida!")
            self.__service_studenti.stergere_student(id_student)
            print("comanda executata cu succes")

        def run(self):
            while True:
                cmd = input(">>>")
                cmd = cmd.strip()
                if cmd == "":
                    continue
                if cmd == "exit":
                    return
                parts = cmd.split()
                cmd_name = parts[0]
                params = parts[1:]
                if cmd_name in self.__commandz:
                    try:
                        self.__commandz[cmd_name](params)
                    except Exception as ex:
                        print(f"UIError:{ex}")
                else:
                    print("comanda invalida!")
