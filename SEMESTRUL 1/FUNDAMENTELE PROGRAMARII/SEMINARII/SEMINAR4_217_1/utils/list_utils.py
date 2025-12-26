def make_list_copy(lst_dicts):
    """
    Face o copie "deep" a listei date
    :param lst: lista de dictionare
    :return: copia listei
    """
    lst_copy = []
    for current_dictionary in lst_dicts:
        new_dictionary = {}
        for key, value in current_dictionary.items():
            new_dictionary[key] = value

        lst_copy.append(new_dictionary)

    return lst_copy

