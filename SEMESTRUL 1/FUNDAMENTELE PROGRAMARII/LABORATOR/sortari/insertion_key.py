from entitati import Product


def insertion_sort_key(arr, key=lambda x: x):
    for i in range(1, len(arr)):
        aux = arr[i]
        j = i - 1
        while j >= 0 and key(aux) < key(arr[j]):
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = aux
    return arr


def test():
    p1 = Product('SWEETS029', 'ciocolata Milka', 7.23)
    p2 = Product('SWEETS437', 'ferrero Rocher', 13.98)
    p3 = Product('SWEETS430', 'turta dulce', 3.88)
    p4 = Product('FRUITS274', 'portocale', 5.99)
    p5 = Product('FRUITS98', 'mandarine', 6.23)

    products = [p1, p2, p3, p4, p5]
    sorted_products = insertion_sort_key(products, lambda x: x.getName())

    assert (sorted_products[0] == p1)
    assert (sorted_products[1] == p2)
    assert (sorted_products[2] == p5)
    assert (sorted_products[3] == p4)
    assert (sorted_products[4] == p3)

    sorted_products = insertion_sort_key(products, lambda x: x.getPrice())

    assert (sorted_products[0] == p3)
    assert (sorted_products[1] == p4)
    assert (sorted_products[2] == p5)
    assert (sorted_products[3] == p1)
    assert (sorted_products[4] == p2)
test()
