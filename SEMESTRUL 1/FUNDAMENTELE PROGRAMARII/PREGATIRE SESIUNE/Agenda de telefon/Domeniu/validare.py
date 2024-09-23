from Domeniu.agenda import Contact
class Validator:
    def valideaza_contact(self,contact):
        erori=""
        if contact.get_nume()=="":
            erori+="nume invalid\n"
        if contact.get_grup() not in ["Prieteni","Familie","Job","Altele"]:
            erori+="grup invalid\n"
        if contact.get_nrtel()=="":
            erori+="nrtel invalid\n"
        if contact.get_nrtel().isdigit()==False:
            erori+="nr incorect\n"
        if len(erori)>0:
            raise Exception(erori)

def test_validare():
    con=Contact("1","","087","Prieteni")
    validator=Validator()
    try:
        validator.valideaza_contact(con)
        assert False
    except Exception as ex:
        assert (str(ex)=="nume invalid\n")
    cont=Contact("1","Ion","089748","Prieteni")
    try:
        validator.valideaza_contact(cont)
        assert True
    except Exception:
        pass


test_validare()