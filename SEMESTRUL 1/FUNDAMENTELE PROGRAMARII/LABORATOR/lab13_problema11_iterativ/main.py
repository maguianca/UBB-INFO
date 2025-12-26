def printeaza(lista):
    print(lista)

def printeaza_mesaj():
    print("Problema nu are solutie")

def conditie(lista, m):
    for i in range(0, len(lista) - 1):
        if abs(lista[i] - lista[i + 1]) != m:
            return False
    return True

def back_iterative(n, m, ok):
    stack = []
    stack.append(([], 0))

    while stack:
        lista, k = stack.pop()

        if k > 1 and k <= n:
            if conditie(lista, m):
                printeaza(lista)
                ok.append(1)

        if k < n:
            for elem in range(n, 0, -1):
                new_lista = lista + [elem]
                stack.append((new_lista, k + 1))

    if ok==[]:
        printeaza_mesaj()



def main():
    n = int(input('Introduceti un nr n: '))
    m = int(input('Introduceti un nr m: '))
    ok = []
    back_iterative(n, m, ok)

main()
