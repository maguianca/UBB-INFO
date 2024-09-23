#produsul nr de pe poz pare din lista

def prod_pare(lista,st,dr):
    if st == dr:
        if st%2 == 0:
            return lista[st]
        else:
            return 1
    mid = (st+dr)//2
    return prod_pare(lista,st,mid) * prod_pare(lista,mid+1,dr)
def produs_numere_pozitii_pare(lista):
    n = len(lista)

    # Cazul de bază: lista are un singur element sau este goală
    if n <= 0:
        return 1

    # Cazul de bază: lista are un singur element pe poziție pară
    if n == 1 and n % 2 == 0:
        return lista[0]

    # Impart lista in doua parti egale
    mijloc = n // 2
    parte_stanga = lista[:mijloc]
    parte_dreapta = lista[mijloc:]

    # Apel recursiv pentru cele două părți ale listei
    produs_stanga = produs_numere_pozitii_pare(parte_stanga)
    produs_dreapta = produs_numere_pozitii_pare(parte_dreapta)

    # Returnează produsul celor două rezultate
    return produs_stanga * produs_dreapta

# Exemplu de utilizare
lista_exemplu = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
rezultat = produs_numere_pozitii_pare(lista_exemplu)
print("Produsul numerelor de pe pozițiile pare este:", rezultat)


lista = [1,2,3,4,5,6]
#print(prod_pare(lista,0,len(lista)))