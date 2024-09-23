class Validator:
    def valideaza_carte(self,carte):
        erori=""
        if carte.get_id()<=0:
            erori+="id invalid\n"
        if carte.get_titlu()=="":
            erori+="titlu invalid\n"
        if carte.get_autor()=="":
            erori+="autor invalid\n"
        if carte.get_an()<=1500 and carte.get_an()>=2025:
            erori+="an invalid\n"
        if len(erori)>0:
            raise Exception(erori)
