def comb_sort(arr):
    n = len(arr)
    gap = n
    shrink = 1.3
    swapped = True

    while gap > 1 or swapped:
        gap = max(1, int(gap / shrink))
        swapped = False

        for i in range(n - gap):
            if arr[i] > arr[i + gap]:
                arr[i], arr[i + gap] = arr[i + gap], arr[i]
                swapped = True
    return arr



def test():
    a3 = [1]
    sorted_list = comb_sort(a3)
    assert (sorted_list == [1])

    a2 = [1, 4, 5, 3, 2]
    result2 = comb_sort(a2)
    assert (result2 == [1, 2, 3, 4, 5])

    assert (comb_sort([]) == [])

    a4 = [1, 1, 1, 1]
    assert (comb_sort(a4) == [1, 1, 1, 1])

    a1 = [1, 4, 3, 2, 5, 1, 5, 33, 2, 11]
    assert (comb_sort(a1) == [1, 1, 2, 2, 3, 4, 5, 5, 11, 33])

test()