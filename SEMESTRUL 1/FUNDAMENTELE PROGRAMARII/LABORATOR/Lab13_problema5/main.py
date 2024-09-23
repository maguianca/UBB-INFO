def printeaza(lista):
    print(lista)

def back(lista, n):
    if len(lista)==n:
        if lista[n-1]!='X':
            printeaza(lista)
        return

    for elem in [1, 2, 'X']:
        if elem == 1 and lista.count(1)>=2:
            continue
        lista.append(elem)
        back(lista, n)
        lista.pop()

def main():
    n=int(input('Introduceti un nr n: '))
    back([],n)

main()