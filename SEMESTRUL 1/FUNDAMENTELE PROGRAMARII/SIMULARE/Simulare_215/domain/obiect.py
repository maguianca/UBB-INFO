class Obiect:
    def __init__(self,cod,tip,nume,stoc,pret):
        self.__cod  = cod
        self.__tip = tip
        self.__nume = nume
        self.__stoc = stoc
        self.__pret = pret

    def getCod(self):
        """
        O metoda care returneaza codul obiectului
        :return:
        """
        return self.__cod

    def getTip(self):
        """
        O metoda care returneaza tipul obiectului
        :return:
        """
        return self.__tip

    def getNume(self):
        """
        O metoda care returneaza numele obiectului
        :return:
        """
        return self.__nume

    def getStoc(self):
        """
        O metoda care returneaza stocul obiectului
        :return:
        """
        return self.__stoc

    def getPret(self):
        """
        O metoda care returneaza pretul obiectului
        :return:
        """
        return self.__pret

    def setStoc(self, newStoc):
        """
        A method that modifies the stock to newStoc
        :param newStoc: Int
        :return: None
        """
        self.__stoc = newStoc

    def __str__(self):
        objectString = f'cod:{self.__cod}, tip:{self.__tip}, nume:{self.__nume}, stoc:{self.__stoc}, pret:{self.__pret}'
        return objectString


def testObiect():
    obiect = Obiect(1,"lampa","lampa venetia", 20, 300.6)
    epsilon = 0.0001
    assert (obiect.getPret() > 300.6 - epsilon) and (obiect.getPret() < 300.6 + epsilon)
    assert obiect.getNume() == "lampa venetia"
    assert obiect.getTip() == "lampa"
    assert obiect.getStoc() == 20
    assert obiect.getCod() == 1

