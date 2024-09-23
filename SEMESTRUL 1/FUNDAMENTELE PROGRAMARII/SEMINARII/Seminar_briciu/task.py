from colorama import Fore, Style


def create_task(descriere, zi, luna, status) -> dict:
    """
    Creeaza un task
    :param task_str: string-ul care reprezinta task-ul
    :type task_str: str
    :return: task-ul creat
    :rtype: dict
    """

    task = {'descriere':descriere,
            'zi_deadline':zi,
            'luna_deadline':luna,
            'status':status}
    return task


def get_description(task):
    return task['descriere']


def get_deadline_day(task):
    return task['zi_deadline']


def get_deadline_month(task):
    return task['luna_deadline']


def get_status(task):
    return task['status']


def get_date(task):
    return str(task['zi_deadline']) + '-' + str(task['luna_deadline'])


def set_description(task, new_description):
    task['descriere'] = new_description


def set_zi_deadline(task, new_day):
    task['zi_deadline'] = new_day


def set_luna_deadline(task, new_month):
    task['luna_deadline'] = new_month


def set_status(task, new_status):
    task['status'] = new_status


def to_str(task) -> str:
    return Fore.CYAN + task['descriere'] + Fore.BLUE + ' | ' + str(task['zi_deadline']) + '/' + str(
        task['luna_deadline']) + Fore.MAGENTA + ' | ' + task[
        'status'] + Style.RESET_ALL



def validate_task(task):
    """
    Valideaza un task dat
    :param task: task-ul care se valideaza
    :return: -
    :raises: ValueError daca task-ul nu e valid
    """
    errors = []
    if len(get_description(task)) < 2:
        errors.append("Descrierea nu este corecta. Trebuie sa fie mai lunga de 2 caractere.")

    if get_deadline_day(task) > 31 or get_deadline_day(task) < 1:
        errors.append("Ziua deadline nu poate fi decat intre 1-31.")

    if get_deadline_month(task) > 12 or get_deadline_month(task) < 1:
        errors.append("Luna deadline nu poate fi decat intre 1-12.")

    if get_status(task) not in ['pending', 'in-progress', 'done']:
        errors.append('Status incorect.')

    if len(errors) > 0:
        error_string = '\n'.join(errors)
        raise ValueError(error_string)


