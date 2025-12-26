from domain.DTOcumparare import DTOcumparare
class ObjectService:
    def __init__(self, rep):
        self.__rep = rep

    def searchByTip(self, tip):
        """
        A method that returns all the objects that are in stock and have the specified type
        :param tip: string
        :return: A list of object objects
        """
        listaObj = self.__rep.getAllObjects()
        listaObjTip = []
        for object in listaObj:
            if object.getTip() == tip and object.getStoc() > 0:
                listaObjTip.append(object)
        if len(listaObjTip) > 0:
            return listaObjTip
        else:
            return ["Nu exista obiecte de tipul dorit"]

    def cumpara(self, cod, nrObjDorite):
        """
        A method that enables the purchase of nrObjDorite objects with codObj = cod
        :param cod: string
        :param nrObjDorite: int
        :return: DTOcumparare object
        """
        if type(nrObjDorite) == int and self.__rep.find(cod) != None:
            objectToBuy = self.__rep.find(cod)
            if objectToBuy.getStoc() < nrObjDorite:
                dto = DTOcumparare('', 0, 0, True)
            else:
                pret = objectToBuy.getPret()*nrObjDorite
                stocRamas = objectToBuy.getStoc()-nrObjDorite
                nume = objectToBuy.getNume()
                dto = DTOcumparare(nume, pret, stocRamas, False)
                self.__rep.modifyObjectStock(cod, stocRamas)

        else:
            dto = DTOcumparare('', 0, 0, True)
        return dto

def testService():
    from repository.repoObiecte import RepoObiecte
    fileName = "/Users/danpetri/Documents/IT/personal_projects/PYTHON/Simulare/data/obiecteTest.txt"
    rep = RepoObiecte(fileName)
    srv = ObjectService(rep)
    assert srv.searchByTip("Corp iluminat")[0].getCod() == '1'
    assert srv.searchByTip("Corp iluminat")[0].getStoc() == 12
    assert str(srv.cumpara('1', 13)) == "An error has occurred, please try again"

testService()
