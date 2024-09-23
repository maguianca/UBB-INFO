#inverseaza o lista de numere
def inverseaza(lista):
    if len(lista) == 1:
        return lista
    mid = len(lista) // 2
    dr = inverseaza(lista[mid:])
    st = inverseaza(lista[:mid])
    return dr + st
def divide(lista):
    if len(lista)==0:
        return 0
    if len(lista) == 1:
        return [lista[0]]
    mid = len(lista) // 2
    dr = inverseaza(lista[mid:])
    st = inverseaza(lista[:mid])
    return dr + st


lista = [1,2,3,4,5,6,7]
print(divide(lista))