#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Repo.h"
#include "validator.h"
#include "service.h"


void test_domain() {
    //Testeaza partea de domain
    Masina* m = creare_masina("sm21mrc", "sport", "coupe", 0);
    assert(strcmp(get_numar(m), "sm21mrc") == 0);
    assert(strcmp(get_categorie(m), "sport") == 0);
    assert(strcmp(get_model(m), "coupe") == 0);
    assert(get_inchiriere(m) == 0);
    set_numar(m, "sm80mrc");
    assert(strcmp(get_numar(m), "sm80mrc") == 0);
    set_categorie(m, "suv");
    assert(strcmp(get_categorie(m), "suv") == 0);
    set_model(m, "gle");
    assert(strcmp(get_model(m), "gle") == 0);
    distruge_masina(m);
    printf("Testul pentru domain a trecut cu succes.\n");
}

void test_repo() {
    //Testeaza partea de repo
    Repository* masini;
    masini = creeaza_vid();
    assert(masini->lungime == 0);
    Masina* m = creare_masina("sm21mrc", "sport", "coupe", 0);
    adaugareR(masini, m);
    assert(masini->lungime == 1);
    assert(strcmp(get_numar(masini->masini[0]), "sm21mrc") == 0);
    assert(strcmp(get_categorie(masini->masini[0]), "sport") == 0);
    assert(strcmp(get_model(masini->masini[0]), "coupe") == 0);
    actualizamR(masini, "sm21mrc", "suv", "gle");
    assert(strcmp(get_numar(masini->masini[0]), "sm21mrc") == 0);
    assert(strcmp(get_categorie(masini->masini[0]), "suv") == 0);
    assert(strcmp(get_model(masini->masini[0]), "gle") == 0);
    distruge(masini, (DestroyFunction) distruge_masina);
    printf("Testul pentru repo a trecut cu succes.\n");
}
void test_set() {
    //Testeaza partea de repo
    Repository* masini;
    masini = creeaza_vid();
    assert(masini->lungime == 0);
    //Masina* m = creare_masina("sm21mrc", "sport", "coupe", 0);
    adaugareR(masini, creare_masina("sm21mrc", "sport", "coupe", 0));
    assert(masini->lungime == 1);
    assert(strcmp(get_numar(masini->masini[0]), "sm21mrc") == 0);
    assert(strcmp(get_categorie(masini->masini[0]), "sport") == 0);
    assert(strcmp(get_model(masini->masini[0]), "coupe") == 0);
    Masina* m = creare_masina("sm21mrc", "mercedes", "coupe", 0);
    Masina* m1 = get(masini, 0);
    distruge_masina(m1);
    set(0, masini, m);
    assert(strcmp(get_numar(masini->masini[0]), "sm21mrc") == 0);
    assert(strcmp(get_categorie(masini->masini[0]), "mercedes") == 0);
    assert(strcmp(get_model(masini->masini[0]), "coupe") == 0);
    distruge(masini, (DestroyFunction) distruge_masina);
    printf("Testul pentru set a trecut cu succes.\n");
}
void test_validate_masina() {
    //Testeaza partea de validare
    assert(validate_masina("AB123CD", "Sedan", "Toyota") == 1);

    assert(validate_masina("A1#23CD", "Sedan", "Toyota") == 0);

    assert(validate_masina("AB123CD", "Sedan2", "Toyota") == 0);

    assert(validate_masina("AB123CD", "Sedan", "Toyota!") == 0);

    assert(validate_masina("", "", "") == 0);

    printf("Testul pentru validare a trecut cu succes.\n");
}

void test_creeaza_distruge() {
    Masina* m = creare_masina("sm21mrc", "sport", "coupe", 0);
    assert(strcmp(m->numar, "sm21mrc") == 0);
    assert(strcmp(m->categorie, "sport") == 0);
    assert(strcmp(m->model, "coupe") == 0);

    distruge_masina(m);
    //assert(m->inchiriata==-100);
}

void test_adauga() {
    //Testeaza partea de adaugare
    Service store = createService();
    int rez=adauga(&store, "AB123CD", "Sedan", "Toyota", 0);
    assert(rez == 1);

    rez=adauga(&store, "", "!Sedan", "21Toyota", 0);
    assert(rez==-1);
    rez = adauga(&store, "AB123CD", "Sedan", "Toyyyota", 0);
    assert(rez == 0);
    distruge_service(&store);
    printf("Testul pentru adaugare a trecut cu succes.\n");
}

void test_actualizare() {
    //Testeaza partea de actualizare
    Service store=createService();
    adauga(&store, "AB123CD", "Sedan", "Toyota", 0);
    int rez=actualizare(&store, "AB123CD", "!Coupe", "");
    assert(rez != 1);
    rez=actualizare(&store, "AB123CD", "Coupe", "Honda");
    assert(rez == 1);
    rez = actualizare(&store, "AB1", "Coupe", "Honda");
    assert(rez == 0);
    rez = actualizare(&store, "A1", "28e", "111");
    assert(rez == -1);

    distruge_service(&store);
    printf("Testul pentru actualizare a trecut cu succes.\n");
}

void test_vizualizare() {
    //Testeaza partea de vizualizare
    Service store=createService();
    adauga(&store, "AB123CD", "Sedan", "Toyota", 0);
    adauga(&store, "XYZ987", "Hatchback", "Honda", 0);
    adauga(&store, "BCD456", "Sedan", "Nissan", 0);

    Repository* masini2 = vizualizare_categorie(&store, "Sedan");
    assert(size(masini2) == 2);
    assert(strcmp(get_categorie(masini2->masini[0]), "Sedan") == 0);
    assert(strcmp(get_categorie(masini2->masini[1]), "Sedan") == 0);
    distruge(masini2, (DestroyFunction) distruge_masina);
    masini2 = vizualizare_model(&store, "Honda");
    assert(size(masini2) == 1);
    assert(strcmp(get_model(masini2->masini[0]), "Honda") == 0);
    distruge(masini2, (DestroyFunction) distruge_masina);
    masini2 = vizualizare_disponibilitate(&store);
    assert(size(masini2) == 3);
    distruge(masini2, (DestroyFunction) distruge_masina);
    distruge_service(&store);

    printf("Testul pentru vizualizare a trecut cu succes.\n");
}



void test_inchiriere_returnare() {
    //Testeaza partea de inchiriere/returnare
    Service store=createService();
    adauga(&store, "AB123CD", "Sedan", "Toyota", 0);
    assert(inchiriere(&store, "AB123CD") == 1);

    assert(inchiriere(&store, "XYZ987") == -1);

    assert(inchiriere(&store, "AB123CD") == 0);


    assert(returnare(&store, "AB123CD") == 1);

    assert(returnare(&store, "AB123CD") == 0);

    assert(returnare(&store, "XYZ987") == -1);
    //distruge(masini, distruge_masina);
    distruge_service(&store);
    printf("Testul pentru inchiriere si returnare a trecut cu succes.\n");
}

void test_sortare_categorie_crescator() {
    //Testeaza partea de sortare categorie crescator
    Service store=createService();
    adauga(&store, "AB123CD", "Sedan", "Toyota", 0);
    adauga(&store, "XYZ987", "Hatchback", "Honda", 0);
    adauga(&store, "BCD456", "Sedan", "Nissan", 0);

    Repository* sort=sortare(&store, comparator_categorie_crescator);

    assert(strcmp(get_categorie(sort->masini[0]), "Hatchback") == 0);
    assert(strcmp(get_categorie(sort->masini[1]), "Sedan") == 0);
    assert(strcmp(get_categorie(sort->masini[2]), "Sedan") == 0);
    distruge(sort, (DestroyFunction) distruge_masina);
    distruge_service(&store);


}

void test_sortare_categorie_descrescator() {
    //Testeaza partea de sortare categorie descrescator
    Service store= createService();
    adauga(&store, "AB123CD", "Sedan", "Toyota", 0);
    adauga(&store, "XYZ987", "Hatchback", "Honda", 0);
    adauga(&store, "BCD456", "Sedan", "Nissan", 0);

    Repository* sort = sortare(&store, comparator_categorie_descrescator);

    assert(strcmp(get_categorie(sort->masini[0]), "Sedan") == 0);
    assert(strcmp(get_categorie(sort->masini[1]), "Sedan") == 0);
    assert(strcmp(get_categorie(sort->masini[2]), "Hatchback") == 0);
    distruge(sort, (DestroyFunction) distruge_masina);
    distruge_service(&store);
}

void test_sortare_model_crescator() {
    //Testeaza partea de sortare model crescator
    Service store = createService();
    adauga(&store, "AB123CD", "Sedan", "Toyota", 0);
    adauga(&store, "XYZ987", "Hatchback", "Honda", 0);
    adauga(&store, "BCD456", "Sedan", "Nissan", 0);

    Repository* sort=sortare(&store, comparator_model_crescator);

    assert(strcmp(get_model(sort->masini[0]), "Honda") == 0);
    assert(strcmp(get_model(sort->masini[1]), "Nissan") == 0);
    assert(strcmp(get_model(sort->masini[2]), "Toyota") == 0);
    distruge(sort, (DestroyFunction) distruge_masina);
    distruge_service(&store);
}

void test_sortare_model_descrescator() {
    //Testeaza partea de sortare model descrescator
    Service store = createService();
    adauga(&store, "AB123CD", "Sedan", "Toyota", 0);
    adauga(&store, "XYZ987", "Hatchback", "Honda", 0);
    adauga(&store, "BCD456", "Sedan", "Nissan", 0);

    Repository* sort=sortare(&store, comparator_model_descrescator);

    assert(strcmp(get_model(sort->masini[0]), "Toyota") == 0);
    assert(strcmp(get_model(sort->masini[1]), "Nissan") == 0);
    assert(strcmp(get_model(sort->masini[2]), "Honda") == 0);
    distruge(sort, (DestroyFunction) distruge_masina);
    distruge_service(&store);
    printf("Testul pentru sortare a trecut cu succes.\n");
}
void test_liste_de_liste()
{
    Repository* lista = creeaza_vid();
    adaugareR(lista, creare_masina("AB12MNG", "Mercedes", "Coupe", 0));
    adaugareR(lista, creare_masina("BH12MNG", "Mercedes", "Sedan", 0));
    Repository* lista2 = creeaza_vid();
    Repository* undo = creeaza_vid();
    adaugareR(undo, lista);
    assert(size(undo) == 1);
    adaugareR(undo, lista2);
    assert(size(undo) == 2);

    distruge(undo, (DestroyFunction) distrugereliste);
    printf("Testul pentru lista de liste a trecut cu succes.\n");
}
void test_copie_lista()
{
    Repository* lista = creeaza_vid();
    adaugareR(lista, creare_masina("bh12amg", "mercedes", "coupe", 0));
    assert(size(lista) == 1);
    Repository* lista_rez = lista_copie(lista);
    assert(size(lista_rez) == 1);
    distruge(lista, (DestroyFunction) distruge_masina);
    distruge(lista_rez, (DestroyFunction) distruge_masina);
    printf("Testul pentru copia de liste a trecut cu succes.\n");
}
void test_stergere()
{
    Repository* v1 =creeaza_vid();
    adaugareR(v1, creare_masina("sm21mrc", "mercedes","coupe",0));
    adaugareR(v1, creare_masina("sm20mrc", "mercedes", "coupe", 0));


    assert(size(v1) == 2);
    Masina*m=stergere(v1, 0);

    assert(strcmp(m->numar, "sm21mrc") == 0);
    assert(strcmp(m->categorie, "mercedes") == 0);
    distruge_masina(m);

    assert(size(v1) == 1);
    distruge(v1, (DestroyFunction) distruge_masina);
    printf("Testul pentru stergere a trecut cu succes.\n");

}
void test_undo() {
    Service store = createService();
    assert(adauga(&store, "sm20mrc", "volvo", "coupe", 0) == 1);
    assert(adauga(&store, "sm21mrc","mercedes","coupe", 0) == 1);
    assert(actualizare(&store, "sm21mrc", "bmw","coupe") == 1);
    assert(inchiriere(&store, "sm21mrc") == 1);
    assert(returnare(&store, "sm21mrc") == 1);
    //undo returnare
    undo(&store);

    Repository* List = vizualizare_model(&store, "coupe");
    assert(size(List) == 2);
    assert(get_inchiriere(List->masini[1]) == 1);
    distruge(List, (DestroyFunction) distruge_masina);

    //undo inchiriere
    undo(&store);

    List = vizualizare_model(&store,"coupe");
    assert(size(List) == 2);
    assert(get_inchiriere(List->masini[1])==0);
    distruge(List, (DestroyFunction) distruge_masina);

    //undo modify
    undo(&store);

    List= vizualizare_categorie(&store, "mercedes");
    assert(size(List) == 1);
    assert(strcmp(get_numar(List->masini[0]),"sm21mrc")== 0);
    distruge(List, (DestroyFunction) distruge_masina);

    //undo add
    undo(&store);
    List = vizualizare_model(&store, "coupe");
    assert(size(List) == 1);
    assert(strcmp(get_numar(List->masini[0]), "sm20mrc") == 0);
    distruge(List, (DestroyFunction) distruge_masina);
    undo(&store);

    int moreUndo = undo(&store);
    assert(moreUndo == 0);
    distruge_service(&store);
    printf("Testul pentru undo efectuat cu succes\n");
}
void test_cauta()
{
    Service store = createService();
    int rez = adauga(&store, "AB123CD", "Sedan", "Toyota", 0);
    assert(rez == 1);
    assert(cauta(&store, "AB123CD")==0);
    assert(cauta(&store, "AB") == -1);
    distruge_service(&store);
    printf("Testul pentru cauta a trecut cu succes.\n\n");
}
void ruleaza_toate_testele() {
    //Ruleaza toate testele
    test_domain();
    test_repo();
    test_set();
    test_validate_masina();
    test_adauga();
    test_actualizare();
    test_vizualizare();
    test_inchiriere_returnare();
    test_sortare_categorie_crescator();
    test_sortare_categorie_descrescator();
    test_sortare_model_crescator();
    test_sortare_model_descrescator();
    test_creeaza_distruge();
    test_liste_de_liste();
    test_copie_lista();
    test_stergere();
    test_undo();
    test_cauta();
    printf("***Toate testele au trecut cu SUCCES!***\n");
}

