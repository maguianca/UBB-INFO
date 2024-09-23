from task import *


def test_create_task():
    task = create_task('BookSkydivingAdventure', 11, 12, 'pending')
    assert (type(task) == dict)
    assert (get_description(task) == "BookSkydivingAdventure")
    assert (get_deadline_day(task) == 11)
    assert (get_deadline_month(task) == 12)
    assert (get_status(task) == 'pending')


def test_validate_task():
    task1 = create_task("Host Movie Marathon", 10, 9, 'pending')
    try:
        validate_task(task1)
        assert True
    except ValueError:
        assert False

    task2 = create_task("H", 10, 9, 'pending')
    try:
        validate_task(task2)
        assert False
    except ValueError:
        assert True

    task3 = create_task("Movie Marathon", 56, 8, 'pending')
    try:
        validate_task(task3)
        assert False
    except ValueError:
        assert True

    task4 = create_task("Host movie marathon", 10, 91, 'pending')
    try:
        validate_task(task4)
        assert False
    except ValueError:
        assert True

    task5 = create_task("Host movie marathon", 10, 9, 'something')
    try:
        validate_task(task5)
        assert False
    except ValueError:
        assert True
