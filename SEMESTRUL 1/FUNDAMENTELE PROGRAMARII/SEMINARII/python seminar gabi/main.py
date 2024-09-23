def creeaza_baller(id_baller,nume,valoare):
    return{
        "id_baller":id_baller,
        "nume":nume,
        "valoare":valoare,
    }

def get_id_baller(baller):
    return baller["id_baller"]
def get_nume(baller):
    return baller["nume"]
def get_valoare(baller):
    return baller["valoare"]

def test_creeaza_baller():
    print("ruleaza teste creeaza baller...")
    id_baller=23
    nume="Jordan"
    valoare=9000.1
    epsilon=0.00001
    baller=creeaza_baller(id_baller,nume,valoare)
    assert id_baller==get_id_baller(baller)
    assert nume==get_nume(baller)
    assert abs(valoare-get_valoare(baller))<epsilon
    print("teste creeaza baller finalizate cu succes...")
def valideaza_baller(baller):
    pass
def test_valideaza_baller():
    #baller valid sau invalid
    id_baller = 23
    nume = "Jordan"
    valoare = 9000.1
    epsilon = 0.00001
    baller = creeaza_baller(id_baller, nume, valoare)
    valideaza_baller(baller)

def ruleaza_toate_testele():
    test_creeaza_baller()
def main():
    ruleaza_toate_testele()
main()