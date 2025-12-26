from list_manager.task_manager import *


def test_add():
    task_manager = create_task_manager()
    add_task(task_manager, 'HostMovieMarathon', 10, 8, 'pending')
    test_task_list = get_current_list(task_manager)
    assert (len(test_task_list) == 1)
    assert (get_description(test_task_list[0]) == 'HostMovieMarathon')


def test_search_by_date():
    task_manager = create_task_manager()
    test_task_list = get_current_list(task_manager)

    assert (search_for_task(test_task_list, 5, 5, 10, 8) == [])

    add_task(task_manager, 'HostMovieMarathon', 10, 8, 'pending')
    add_task(task_manager, 'Read Book', 5, 3, 'pending')
    add_task(task_manager, 'Build Treehouse', 1, 10, 'pending')

    # E ok sa testam astfel, stim sigur ca se pastreaza ordinea task-urilor?
    assert (len(search_for_task(test_task_list, 5, 5, 6, 11)) == 2)

    add_task(task_manager, 'HostMovieMarathon', 5, 8, 'pending')

    assert (len(search_for_task(test_task_list, 5, 5, 6, 11)) == 3)

    add_task(task_manager, 'HostMovieMarathon', 1, 11, 'pending')

    assert (len(search_for_task(test_task_list, 5, 5, 6, 11)) == 4)
    assert (len(search_for_task(test_task_list, 5, 5, 1, 11)) == 4)


def test_delete_task_by_description():
    task_manager = create_task_manager()
    test_task_list = get_current_list(task_manager)

    try:
        delete_task_by_description(task_manager, "Read Book")
        assert False
    except IndexError:
        assert True
    assert (test_task_list == [])

    add_task(task_manager, 'HostMovieMarathon', 10, 8, 'pending')
    add_task(task_manager, 'Read Book', 5, 3, 'pending')
    add_task(task_manager, 'Build Treehouse', 1, 10, 'pending')

    delete_task_by_description(task_manager, "Read Book")
    assert (len(test_task_list) == 2)
    try:
        delete_task_by_description(task_manager, "Travel")
        assert False
    except IndexError:
        assert True
    assert (len(test_task_list) == 2)


def test_filter_by_description():
    task1 = create_task("Travel to see Grand Canyon", 11, 9, 'pending')
    task2 = create_task("Travel abroad", 10, 5, 'pending')
    task3 = create_task("Try new banana bread recipe", 11, 2, "done")
    task4 = create_task("Host a Halloween party", 31, 10, 'in-progress')
    task5 = create_task("Buy stuff for New Year party", 28, 12, "pending")

    test_list = [task1, task2, task3, task4, task5]
    filtered_by_travel = filter_by_description(test_list, 'travel')
    assert (len(filtered_by_travel) == 2)
    assert (len(test_list) == 5)

    filtered_by_recipe = filter_by_description(test_list, 'recipe')
    assert (len(filtered_by_recipe) == 1)
    assert (len(test_list) == 5)

    filtered_by_cook = filter_by_description(test_list, 'cook')
    assert (len(filtered_by_cook) == 0)
    assert (len(test_list) == 5)


def test_delete_by_status():
    task_manager = create_task_manager()
    test_list = get_current_list(task_manager)
    delete_by_status(task_manager, 'pending')
    assert (test_list == [])

    add_default_tasks(test_list)
    # Initial: pending - 3, in-progress - 2, done - 4

    delete_by_status(task_manager, 'pending')
    assert (len(test_list) == 6)

    delete_by_status(task_manager, 'in-progress')
    assert (len(test_list) == 4)

    delete_by_status(task_manager, 'done')
    assert (len(test_list) == 0)


def undo(task_manager_data):
    """
    Anuleaza ultima operatie
    :return: -
    :raises ValueError daca nu se mai poate face undo
    """
    undo_list = get_undo_list(task_manager_data)
    if len(undo_list) > 0:
        # print('Se poate face undo')
        previous_list = undo_list.pop()
        set_current_list(task_manager_data, previous_list)
    else:
        raise ValueError("Nu se mai poate face undo.")


def test_undo():
    task_manager = create_task_manager()

    add_task(task_manager, "Join a book club", 11, 5, 'in-progress')
    assert (len(get_current_list(task_manager)) == 1)

    undo(task_manager)
    assert (len(get_current_list(task_manager)) == 0)

    add_task(task_manager, "Join a book club", 11, 5, 'in-progress')
    add_task(task_manager, "Host Game Night", 12, 10, 'pending')
    add_task(task_manager, "Try something new", 19, 10, 'in-progress')

    delete_by_status(task_manager, 'in-progress')
    assert (len(get_current_list(task_manager)) == 1)
    undo(task_manager)
    assert (len(get_current_list(task_manager)) == 3)

    delete_by_status(task_manager, 'in-progress')
    delete_by_status(task_manager, 'pending')

    undo(task_manager)
    assert (len(get_current_list(task_manager)) == 1)
    undo(task_manager)
    assert (len(get_current_list(task_manager)) == 3)

    delete_task_by_description(task_manager, 'Join a book club')
    assert (len(get_current_list(task_manager)) == 2)
    undo(task_manager)
    assert (len(get_current_list(task_manager)) == 3)
    try:
        undo(task_manager)
        assert False
    except:
        assert True


def test_get_report_by_day():
    test_list = []

    report_dict = get_report_by_day(test_list)
    assert (len(report_dict.keys()) == 0)
    # also works with assert (not report_dict)
    add_default_tasks(test_list)

    report_dict = get_report_by_day(test_list)
    assert (len(report_dict['4-4']) == 1)

    assert (len(report_dict['5-8']) == 2)

    assert (len(report_dict['12-9']) == 3)

    try:
        number_of_tasks = len(report_dict['1-1'])
        assert False
    except KeyError:
        assert True
