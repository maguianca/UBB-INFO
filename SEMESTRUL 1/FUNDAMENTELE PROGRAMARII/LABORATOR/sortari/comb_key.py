from entitati import Product
def comb_sort_key(arr, key=lambda x:x):
    n = len(arr)
    gap = n
    shrink = 1.3
    swapped = True

    while gap > 1 or swapped:
        gap = max(1, int(gap / shrink))
        swapped = False

        for i in range(n - gap):
            if key(arr[i]) > key(arr[i + gap]):
                arr[i], arr[i + gap] = arr[i + gap], arr[i]
                swapped = True
    return arr

def test():
    p1 = Product('SWEETS029', 'ciocolata Milka', 7.23)
    p2 = Product('SWEETS437', 'ferrero Rocher', 13.98)
    p3 = Product('SWEETS430', 'turta dulce', 3.88)
    p4 = Product('FRUITS274', 'portocale', 5.99)
    p5 = Product('FRUITS98', 'mandarine', 6.23)

    products = [p1, p2, p3, p4, p5]
    sorted_products = comb_sort_key(products, lambda x: x.getName())

    assert (sorted_products[0] == p1)
    assert (sorted_products[1] == p2)
    assert (sorted_products[2] == p5)
    assert (sorted_products[3] == p4)
    assert (sorted_products[4] == p3)

    sorted_products = comb_sort_key(products, lambda x: x.getPrice())

    assert (sorted_products[0] == p3)
    assert (sorted_products[1] == p4)
    assert (sorted_products[2] == p5)
    assert (sorted_products[3] == p1)
    assert (sorted_products[4] == p2)
test()