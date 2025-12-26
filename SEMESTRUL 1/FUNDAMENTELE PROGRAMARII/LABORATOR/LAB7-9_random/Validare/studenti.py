import Domeniu

class ValidatorStudent:

    def valideaza_student(self,student):
        """
                valideaza entitatea laborator
                verifica id,nume si grup sa fie un format valid
                :param student: entitate de tip student
                :return: raise exception daca este cazul
                """
        erori = ""
        if student.get_id_student()<0:
            erori += "id invalid!\n"
        if student.get_nume()=="":
            erori += "nume invalid!\n"
        if student.get_grup()<0:
            erori += "valoare invalida!\n"
        if len(erori)>0:
            raise Exception(erori)
    def valideaza_id(self,id_student):
        """
        valideaza id
        verifica id,nume si grup sa fie un format valid
        :param id_student: atribut de tip student
        :return: raise exception daca este cazul
                       """
        erori=""
        if id_student<0:
            erori+="id invalid!\n"
        if len(erori)>0:
            raise Exception(erori)