class UI:
    def __init__(self, srv):
        self.__srv = srv

    def handleUserInput(self):
        """
        A method for reading the desired menu of the user
        :return:
        """
        listaValida = ["Cautare", "Cumparare"]
        while True:
            usrInput = input("Cautare/Cumparare: ")
            if usrInput in listaValida:
                return usrInput
            else:
                print("Enter a valid prompt")

    def redirectToQuery(self, usrInput):
        """
        A method that controls the application flow according to the user input
        :param usrInput: string
        :return: None
        """
        if usrInput == "Cautare":
            self.cautare()
        else:
            self.cumparare()

    def cautare(self):
        """
        A method that handles the UI of the search feature
        :return:
        """
        tip = input("tip: ")
        listaDorita = self.__srv.searchByTip(tip)
        for obj in listaDorita:
            print(obj)

    def cumparare(self):
        """
        A method that handles the UI of the buying
        :return:
        """
        while True:
            try:
                cod = input("Cod: ")
                nrOfObj = int(input("Nr de obj: "))
                if nrOfObj < 0:
                    raise Exception
                print(self.__srv.cumpara(cod, nrOfObj))
                return
            except:
                print("Nr de obj trebuie sa fie un intreg pozitiv")

    def startUI(self):
        """
        The method that needs to be called in order for the app to start
        :return:
        """
        while True:
            usrInput = self.handleUserInput()
            self.redirectToQuery(usrInput)
