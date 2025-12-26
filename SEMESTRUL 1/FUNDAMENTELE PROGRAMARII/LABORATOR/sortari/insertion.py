from entitati import Product

def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
    return arr

def test():
    a3 = [1]
    sorted_list = insertion_sort(a3)
    assert (sorted_list == [1])

    a2 = [1, 4, 5, 3, 2]
    result2 = insertion_sort(a2)
    assert (result2 == [1, 2, 3, 4, 5])

    assert (insertion_sort([]) == [])

    a4 = [1, 1, 1, 1]
    assert (insertion_sort(a4) == [1, 1, 1, 1])

    a1 = [1, 4, 3, 2, 5, 1, 5, 33, 2, 11]
    assert (insertion_sort(a1) == [1, 1, 2, 2, 3, 4, 5, 5, 11, 33])

test()