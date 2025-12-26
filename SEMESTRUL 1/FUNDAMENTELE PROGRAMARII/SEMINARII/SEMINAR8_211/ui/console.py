
#from termcolor import colored

from exceptions.exceptions import ValidationException, DuplicateIDException, ClientNotFoundException, \
    ShowNotFoundException, RatingAlreadyAssignedException, NotEnoughRatingsException


class Console:
    def __init__(self, srv_shows, srv_clients, srv_ratings):
        """
        Initializeaza consola
        :type srv: ShowService
        """
        self.__srv_shows = srv_shows
        self.__srv_clients = srv_clients
        self.__srv_ratings = srv_ratings

    def __print_menu(self):
        print('Comenzi disponibile pentru show, client. Adaugati sufixul',
              '_show sau _client', ' pentru a accesa optiunea dorita.')
        print('ENTITY COMMANDS:','add, delete, update, show_all')
        print('Comenzi disponibile pentru rating-uri. Se folosesc fara adaugare string.')
        print('RATING COMMANDS:',
              'assign_rating, top3_shows_by_client, show_all_ratings, rating_report, exit', )

    def __print_shows(self, show_list):
        """
        Afiseaza o lista de seriale

        """

        if len(show_list) == 0:
            print('Nu exista seriale in lista.')
        else:
            print('Lista de seriale este:')
            for show in show_list:
                # print(show)
                print('ID: ',show.getId(),
                      ' - Titlu serial: ', show.getTitle(), ' - An aparitie: ',
                      str(show.getAnAparitie()),
                        ' - Nr. episoade: ', str(
                        show.getEpisoade()))

    def __add_show(self):
        """
        Adauga un serial cu datele citite de la tastatura
        """
        id = input('Identificator serial:')
        titlu = input("Titlul serialului:")
        try:
            an_aparitie = int(input("Anul aparitiei:"))
            eps = int(input("Numar de episoade difuzate:"))
            added_show = self.__srv_shows.add_show(id, titlu, an_aparitie, eps)
            print('Serialul ' + added_show.getTitle() + ' (' + str(
                added_show.getAnAparitie()) + ') a fost adaugat cu succes.')
        except ValueError:
            print('Anul aparitiei si nr. episoade trebuie sa fie un numar.')
        except ValidationException as ve:
            print(str(ve))
        except DuplicateIDException as e:
            print(str(e))

    def __delete_show(self):
        id = input('Identificatorul serialului de sters:')
        try:
            deleted_show = self.__srv_shows.delete_show(id)
            print('Serialul ' + deleted_show.getTitle() + ' (' + str(
                deleted_show.getAnAparitie()) + ') a fost sters cu succes (ID=' + str(deleted_show.getId()) + ').')
        except ShowNotFoundException as e:
            print(str(e))

    def __update_show(self):
        id = input('Identificator serial:')
        titlu = input("Titlul serialului:")
        try:
            an_aparitie = int(input("Anul aparitiei:"))
            eps = int(input("Numar de episoade difuzate:"))
            modified_show = self.__srv_shows.update_show(id, titlu, an_aparitie, eps)
            print('Serialul ' + modified_show.getTitle() + ' (' + str(
                modified_show.getAnAparitie()) + ') a fost modificat cu succes.')
        except ValueError:
            print('Anul aparitiei si nr. episoade trebuie sa fie un numar.')
        except ValidationException as ve:
            print(str(ve))
        except ShowNotFoundException as e:
            print(str(e))

    def __print_clients(self, client_list):
        """
        Afiseaza o lista de clienti

        """

        if len(client_list) == 0:
            print('Nu exista clienti in lista.')
        else:
            print('Lista de clienti este:')
            for client in client_list:
                # print(client)
                print('ID: ', client.getId(),
                      ' - Nume client: ', client.getNume(), ' - Varsta: ',
                      str(client.getVarsta()))

    def __add_client(self):
        """
        Adauga un client cu datele citite de la tastatura
        """
        id = input('Identificator client:')
        nume = input("Numele clientului:")
        try:
            varsta = int(input("Varsta:"))
            added_client = self.__srv_clients.add_client(id, nume, varsta)
            print('Clientul ' + added_client.getNume() + ' cu varsta ' + str(
                added_client.getVarsta()) + ' a fost adaugat cu succes.')
        except ValueError:
            print('Varsta clientului trebuie sa fie un numar.')
        except ValidationException as ve:
            print(str(ve))
        except DuplicateIDException as e:
            print(str(e))

    def __delete_client(self):
        id = input('Identificatorul clientului de sters:')
        try:
            deleted_client = self.__srv_clients.delete_client(id)
            print('Clientul ', deleted_client, 'a fost sters cu succes (ID=' + str(deleted_client.getId()) + ').')

        except ClientNotFoundException as e:
            print(str(e))

    def __update_client(self):
        id = input('Identificator client:')
        nume = input("Numele clientului:")
        try:
            varsta = int(input("Varsta:"))
            modified_client = self.__srv_clients.update_client(id, nume, varsta)
            print('Clientul ' + modified_client.getNume() + ' cu varsta ' + str(
                modified_client.getVarsta()) + ' a fost modificat cu succes.')
        except ValueError:
            print('Varsta clientului trebuie sa fie un numar.')
        except ValidationException as ve:
            print(str(ve))
        except ClientNotFoundException as e:
            print(str(e))

    def __print_ratings(self, rating_list):
        """
        Afiseaza o lista de rating-uri

        """

        if len(rating_list) == 0:
            print('Nu exista rating-uri in lista.')
        else:
            print('Lista de rating-uri este:')
            for rating in rating_list:
                # print(rating)
                print('Serial: [', str(rating.getSerial().getTitle()), '; ',
                      str(rating.getSerial().getAnAparitie()), ']',
                      'Client: [', str(rating.getClient().getNume()), ';',
                      str(rating.getClient().getVarsta()), ']', 'Rating: ', str(
                        rating.getNoStars()))

    def __assign_rating(self):
        id_show = input('ID serial:')
        id_client = input('ID client')
        try:
            no_stars = float(input('Number of stars:'))
            rating = self.__srv_ratings.create_rating(id_show, id_client, no_stars)
            print('Rating-ul', rating, 'a fost adaugat cu succes.')
        except ValueError:
            print('No. stars trebuie sa fie un numar.')
        except ValidationException as ve:
            print(str(ve))
        except ShowNotFoundException as ve:
            print(str(ve))
        except ClientNotFoundException as ve:
            print(str(ve))
        except RatingAlreadyAssignedException as ve:
            print(str(ve))

    def __get_top_shows_for_client(self):
        """
        Afiseaza primele 3 show-uri pentru un client dat (in functie de rating)
        """
        client_id = input('ID client:')
        try:
            client_shows = self.__srv_ratings.get_top_shows(client_id)
            print('Primele 3 seriale cu cele mai bune rating-uri sunt:')
            for client_show in client_shows:
                print('Nume client:', client_show.getNumeClient(), '; Titlu serial:',
                      client_show.getTitluSerial(), '; Rating:',
                      str(client_show.getNoStars()))

        except ClientNotFoundException as e:
            print(str(e))
        except NotEnoughRatingsException as e:
            print('Nu exista destule seriale evaluate pentru a afisa statistica.')

    def __create_rating_report(self):
        """
        Afiseaza informatiile legate de rating-uri (nr. rating-uri, avg no stars, medie varsta pentru fiecare serial)
        """
        show_rating_infos = self.__srv_ratings.get_ratings_info()
        print('Informatiile despre evaluari:')
        for show_rating in show_rating_infos:
            print('Serial:', show_rating.getTitluSerial(), 'Numar rating-uri:',
                  str(show_rating.getNoRatings()), 'Avg. no. stars:',
                  str(show_rating.getAvgNoStars()), ' Medie varsta:',
                  str(show_rating.getMedieVarsta()))

    def show_ui(self):
        while True:
            self.__print_menu()
            cmd = input('Comanda este:')
            cmd = cmd.lower().strip()
            if cmd == 'add_show':
                self.__add_show()
            elif cmd == 'delete_show':
                self.__delete_show()
            elif cmd == 'update_show':
                self.__update_show()
            elif cmd == 'show_all_shows':
                self.__print_shows(self.__srv_shows.get_all_shows())

            elif cmd == 'add_client':
                self.__add_client()
            elif cmd == 'delete_client':
                self.__delete_client()
            elif cmd == 'update_client':
                self.__update_client()
            elif cmd == 'show_all_clients':
                self.__print_clients(self.__srv_clients.get_all_clients())

            elif cmd == 'assign_rating':
                self.__assign_rating()
            elif cmd == 'show_all_ratings':
                self.__print_ratings(self.__srv_ratings.get_all())
            elif cmd == 'top3_shows_by_client':
                self.__get_top_shows_for_client()
            elif cmd == 'rating_report':
                self.__create_rating_report()
            elif cmd == 'exit':
                return
            else:
                print('Comanda invalida.')
