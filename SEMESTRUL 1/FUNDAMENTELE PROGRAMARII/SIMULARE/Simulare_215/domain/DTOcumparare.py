class DTOcumparare:
    def __init__(self, nume, pretTotal, stocRamas, errorOccurred):
        self.__nume = nume
        self.__pretTotal = pretTotal
        self.__stocRamas = stocRamas
        self.__errorOc = errorOccurred

    def __str__(self):
        """
        Defining the str method for the DTOcumparare class
        :return: string
        """
        if self.__errorOc == True:
            return "An error has occurred, please try again"

        stringDTO = f'nume: {self.__nume}, pret: {self.__pretTotal}, stoc ramas: {self.__stocRamas}'
        return stringDTO

def testDTOcumparare():
    dto = DTOcumparare("lampa", 12, 30, False)
    dtoStr = str(dto)
    assert dtoStr == "nume: lampa, pret: 12, stoc ramas: 30"

testDTOcumparare()