from task import create_task, get_description, get_deadline_day, get_deadline_month, get_status, validate_task, \
    get_date
from lists_utils import make_list_copy


def create_task_manager() -> dict:
    """
    Creeaza o structura prin care gestionam datele din aplicatie
    :return: dictionar cu 2 chei:
            current_task_list: lista curenta de task-uri (lista de lucru)
            undo_list: lista de undo
    """
    return {'current_task_list': [], 'undo_list': []}


# Functii care ne ajuta sa ascundem reprezentarea acestui "manager"
# de restul aplicatiei
# Ca si get_... de la task, nu fac altceva decat sa imi returneze informatia
# aferenta entitatii pe care o trimit ca parametru
# dar avantajul accesarii informatiei astfel si nu direct,
# utilizand sintaxa specifica de dictionar sau lista peste tot
# unde trebuie sa accesez aceasta informatie
# este cand apare o schimbare: daca folosesc get, set
# nu depind de reprezentare - poate sa fie orice structura pe care o consider potrivita
# in "spate", in care imi tin informatia, si pot sa schimb rapid daca ma razgandesc
# ex. daca peste tot in aplicatie folosesc get_descriere, depind doar
# de specificatia lui get_descriere(task) (returneaza descrierea task-ului dat),
# pentru restul aplicatiei nu conteaza daca informatia a fost luata din dictionar, lista
# sau orice alta structura

# Analog - Daca ulterior imi tin astfel datele de task manager in : [current_task_list, undo_list]
# sa nu fie nevoie sa schimb in aplicatie decat aici

def get_undo_list(task_manager_data):
    return task_manager_data['undo_list']


def get_current_list(task_manager_data):
    return task_manager_data['current_task_list']


def set_current_list(task_manager_data, new_list):
    """
    Seteaza lista curenta de task-uri la noua lista data ca parametru
    """
    task_manager_data['current_task_list'] = new_list


def add_state_to_undo(task_manager):
    """
    Adds the current state of the list to the undo list (stack)
    :param task_manager: dictionar care contine lista de undo si lista curenta
    :return: -; lista de undo se modifica prin adaugarea starii curente a listei la sfarsit
    """
    task_list = get_current_list(task_manager)
    undo_list = get_undo_list(task_manager)
    undo_list.append(make_list_copy(task_list))


def add_task(task_manager_data: dict, descriere: str, zi: int, luna: int, status: str) -> None:
    """
    Adauga un task in lista de task-uri
    :param task_list: lista de task-uri
    :type task_list: list
    :param task: task-ul de adaugat
    :type task: dict
    :return: -; modifica lista prin adaugarea la sfarsit a task-ului
    :rtype:
    :raises: ValueError daca task-ul de adaugat nu este valid
    """

    task = create_task(descriere, zi, luna, status)
    validate_task(task)

    add_state_to_undo(task_manager_data)
    task_list = get_current_list(task_manager_data)
    task_list.append(task)


def add_default_tasks(task_list):
    task1 = create_task('Read book', 11, 10, 'pending')
    task2 = create_task('Host movie marathon', 5, 8, 'done')
    task3 = create_task('Travel to uncharted island', 10, 1, 'in-progress')
    task4 = create_task('Build treehouse', 12, 9, 'pending')
    task5 = create_task('Book Skydiving Adventure', 4, 4, 'done')
    task6 = create_task('Learn to ski', 21, 11, 'done')
    task7 = create_task('Master Art of Origami', 5, 8, 'in-progress')
    task8 = create_task('Dance to 80\'s music', 12, 9, 'pending')
    task9 = create_task('Learn to play guitar', 12, 9, 'done')

    task_list.extend([task1, task2, task3, task4, task5, task6, task7, task8, task9])


def delete_by_status(task_manager: dict, status: str) -> None:
    """
    Sterge task-urile din list care au statusul dat
    :param task_manager: task manager data, contine lista de undo si lista curenta
    :param status: statusul dupa care se sterge
    :return: -; lista se modifica prin eliminarea task-urilor cu statusul dat
    """

    # daca returnez o lista noua doar cu task-urile care respecta conditia
    # return [task for task in lst if get_status(task)!=status]

    # daca modific lista
    #Diferenta intre cele 2 functii de delete: pun starea anterioara a listei in lista de undo
    #doar daca chiar sterg ceva
    #Avanataje/dezavantaje la cele 2 abordari?
    add_state_to_undo(task_manager)
    task_list = get_current_list(task_manager)

    current_list_length = len(task_list)
    i = 0
    while i < current_list_length:
        task = task_list[i]
        if get_status(task) == status:
            task_list.pop(i)
            current_list_length -= 1
        else:
            i += 1




def delete_task_by_description(task_manager: dict, description: str):
    """
    Sterge task-ul dupa descriere
    :param task_manager: task manager data - lista de undo, lista de task-uri curenta
    :param description: descrierea dupa care se sterge
    :return: -; lista curenta se modifica prin stergerea elementelor
    """
    # Presupunem ca exista doar 1 task cu descrierea data



    index_to_remove = -1
    for i, task in enumerate(get_current_list(task_manager)):
        if get_description(task) == description:
            index_to_remove = i
            break
    if index_to_remove != -1:
        add_state_to_undo(task_manager)
        task_list = get_current_list(task_manager)
        task_list.pop(index_to_remove)
    else:
        raise IndexError("Nu exista task cu descrierea data.")

    # daca returnam lista noua cu task-ul cu descriere data sters
    # return [task for task in task_list if get_descriere_task(task) != description]
    # daca modificam lista, nu returnam nimic

def undo(task_manager_data):
    """
    Anuleaza ultima operatie
    :return: -
    :raises ValueError daca nu se mai poate face undo
    """
    undo_list = get_undo_list(task_manager_data)
    if len(undo_list) > 0:
        previous_list = undo_list.pop()
        set_current_list(task_manager_data, previous_list)
    else:
        raise ValueError("Nu se mai poate face undo.")



def search_for_task(task_list: list, zi_start: int, luna_start: int, zi_end: int, luna_end: int) -> list:
    """
    Cauta un task cu data intre 2 date date
    :param task_list: lista de task-uri
    :param zi_start: ziua datei de inceput
    :param luna_start: luna datei de inceput
    :param zi_end: ziua datei de sfarsit
    :param luna_end: luna datei de sfarsit
    :return: o noua lista cu task-urile care sunt intre datele date
    """
    # TO-DO: refactor for cleaner version
    # See here some options: https://stackoverflow.com/questions/5464410/how-to-tell-if-a-date-is-between-two-other-dates)

    task_with_date_list = []
    for task in task_list:
        if luna_start < get_deadline_month(task) < luna_end:
            task_with_date_list.append(task)
        elif get_deadline_month(task) == luna_start:
            if luna_start == luna_end:
                if zi_start <= get_deadline_day(task) <= zi_end:
                    task_with_date_list.append(task)
            else:
                if zi_start <= get_deadline_day(task):
                    task_with_date_list.append(task)
        elif get_deadline_month(task) == luna_end:
            if luna_start == luna_end:
                if zi_start <= get_deadline_day(task) <= zi_end:
                    task_with_date_list.append(task)
            else:
                if zi_end >= get_deadline_day(task):
                    task_with_date_list.append(task)

    return task_with_date_list



def filter_by_description(task_list: list, description: str) -> list:
    """
    Returneaza lista cu task-urile care contin in descriere un string dat
    :param task_list: lista de task-uri
    :param description: substring-ul dupa care se cauta
    :return: o lista in care se regasesc doar task-urile care au in descriere string-ul dat
    """
    return [task for task in task_list if description.lower() in get_description(task).lower()]

def get_report_by_day(task_list: list) -> dict:
    """
    Face un raport de activitati pe data
    :param task_list: lista de task-uri
    :return: dictionar cu cheie data (str format din zi si luna) si valoare lista
            aferenta de task-uri care au deadline in ziua respectiva
    """
    day_dictionary = {}
    for task in task_list:
        if get_date(task) in day_dictionary:
            day_dictionary[get_date(task)].append(task)
        else:
            day_dictionary[get_date(task)] = [task]
    return day_dictionary


