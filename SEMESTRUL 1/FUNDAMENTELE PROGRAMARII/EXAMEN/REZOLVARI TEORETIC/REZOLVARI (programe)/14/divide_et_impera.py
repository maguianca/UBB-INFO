#inverseaza o lista de numere
def inverseaza(lista):
    if len(lista)==0:
        return 0
    if len(lista) == 1:
        lista[0]= lista[0] *2
        return lista

    else:
        mid = len(lista)//2
        st = inverseaza(lista[:mid])
        dr = inverseaza(lista[mid:])
        return dr + st


lista = []
print(inverseaza(lista))

