def printeaza(lista):
    print(lista)

def conditie(lista,m):
    for i in range(0,len(lista)-1):
        if abs(lista[i]-lista[i+1])!=m:
            return False
    return True

def back(lista, k,m,ok,n):
    if len(lista)==k:
        if conditie(lista,m):
            printeaza(lista)
            ok.append(1)
        return

    for elem in range(1,n+1):
        lista.append(elem)
        back(lista, k,m,ok,n)
        lista.pop()

def main():
    ok=[]
    n=int(input('Introduceti un nr n: '))
    m = int(input('Introduceti un nr m: '))
    for i in range(2,n+1):
        back([],i,m,ok,n)
    if ok==[]:
        print("Problema nu are solutie")

main()