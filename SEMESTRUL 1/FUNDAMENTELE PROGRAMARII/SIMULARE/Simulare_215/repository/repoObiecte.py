from domain.obiect import Obiect
from exceptions.exceptions import RepoError
class RepoObiecte:
    def __init__(self, fileName):
        self.__fileName = fileName
        self.__listaObiecte = {}
        self.__loadFromFile()


    def addObject(self, object):
        """
        A method that stores an object object
        :param object: am object object
        :return: None
        """
        if object.getCod() not in self.__listaObiecte:
            self.__listaObiecte[object.getCod()] = object
            self.__loadToFile(self.__listaObiecte)
        else:
            return RepoError("Id mut ber unique")

    def __loadFromFile(self):
        """
        A method that loads all the object from file
        :return: None
        """
        with open(self.__fileName, 'r') as file:
            objectLines = file.readlines()
        for line in objectLines:
            object = self.__parseLineIntoObject(line)
            self.addObject(object)

    def __parseLineIntoObject(self, line):
        """
        Parses a file line into an object object
        :param line: A file line
        :return:An object object
        """
        line = line[:-1]
        line = line.split(',')
        codObiect = line[0]
        tip = line[1]
        nume = line[2]
        stoc = int(line[3])
        pret = float(line[4])
        obiect = Obiect(codObiect, tip, nume, stoc, pret)
        return obiect

    def __loadToFile(self, listaObiecte):
        """
        Loads to the file specified in the object attribute fileName the list of objects
        :param listaObiecte: a list of object objects
        :return: None
        """
        with open(self.__fileName, 'w') as file:
            for obiectId in listaObiecte:
                objectLine = self.__parseObjectIntoLine(self.__listaObiecte[obiectId])
                file.write(objectLine)

    def __parseObjectIntoLine(self, obiect):
        """
        A method that pases an object object into a string
        :param obiect: an object object
        :return:
        """
        objectString = ''
        objectString += obiect.getCod()
        objectString += ','
        objectString += obiect.getTip()
        objectString += ','
        objectString += obiect.getNume()
        objectString += ','
        objectString += str(obiect.getStoc())
        objectString += ','
        objectString += str(obiect.getPret())
        objectString += '\n'
        return objectString

    def getAllObjects(self):
        """
        Returns a list containing all the objects in the repo
        :return:
        """
        listaObiecte = []
        for objectId in self.__listaObiecte:
            listaObiecte.append(self.__listaObiecte[objectId])
        return listaObiecte

    def find(self, codObj):
        """
        A method that returns the object with the specified codObj or None if an object with that codObj does not exist in the repo
        :param codObj: String
        """
        if codObj in self.__listaObiecte:
            return self.__listaObiecte[codObj]
        return None

    def __len__(self):
        """
        Returns the number of elements in the repo
        :return:
        """
        return len(self.__listaObiecte)

    def modifyObjectStock(self, codObj, nrOfPieces):
        """
        A function that modifies the stock for the object with codObj to nrOfPieces
        :param codObj: string
        :param nrOfPieces: int
        :return: None
        """
        if codObj in self.__listaObiecte:
                self.__listaObiecte[codObj].setStoc(nrOfPieces)
                self.__loadToFile(self.__listaObiecte)
        else:
            return RepoError()



def testRepoObj():
    fileName = "/Users/danpetri/Documents/IT/personal_projects/PYTHON/Simulare/data/obiecteTest.txt"
    rep = RepoObiecte(fileName)
    assert len(rep) == 1
    assert rep.find("1") is not None
    assert rep.find("1").getStoc() == 12
    rep.modifyObjectStock("1", 3)
    assert rep.find("1").getStoc() == 3
    rep.modifyObjectStock("1", 12)
    assert rep.find("1").getStoc() == 12


testRepoObj()