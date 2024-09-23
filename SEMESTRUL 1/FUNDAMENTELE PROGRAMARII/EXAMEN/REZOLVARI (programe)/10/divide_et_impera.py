#produsul nr de pe poz pare din lista

def prod_pare(lista,st,dr):
    if st == dr:
        if st%2 == 0:
            return lista[st]
        else:
            return 1
    mid = (st+dr)//2
    return prod_pare(lista,st,mid) * prod_pare(lista,mid+1,dr)

def prod_pare(lista, st, dr):
    # Cazul de bază: lista are un singur element sau este goală
    if st == dr:
        return lista[st] if st % 2 == 0 else 1

    # Impart lista in doua parti egale
    mid = (st + dr) // 2

    # Apel recursiv pentru cele două părți ale listei
    produs_stanga = prod_pare(lista, st, mid)
    produs_dreapta = prod_pare(lista, mid + 1, dr)

    # Returnează produsul celor două rezultate
    return produs_stanga * produs_dreapta

# Exemplu de utilizare
lista_exemplu = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
#rezultat = prod_pare(lista_exemplu, 0, len(lista_exemplu) - 1)
#print("Produsul numerelor de pe pozițiile pare este:", rezultat)


# Exemplu de utilizare
lista_exemplu = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
#rezultat = produs_numere_pozitii_pare(lista_exemplu)
#print("Produsul numerelor de pe pozițiile pare este:", rezultat)


lista = [1,2,3,4,5,6]
print(prod_pare(lista,0,len(lista)-1))