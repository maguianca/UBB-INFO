from Domeniu.note import Note
from Exceptii.valid_error import ValidError
class ValidatorNote:
        def valideaza_note(self, note):
            erori = ""
            if note.get_nota()<1 or note.get_nota()>10:
                erori += "nota invalida <nota trb sa fie intre 1 si 10>!\n"
            if len(erori) > 0:
                raise ValidError(erori)
        def valideaza_int(self,x):
            erori = ""
            if x < 1 or x > 10:
                erori += "nota invalida <nota trb sa fie intre 1 si 10>!\n"
            if len(erori) > 0:
                raise ValidError(erori)