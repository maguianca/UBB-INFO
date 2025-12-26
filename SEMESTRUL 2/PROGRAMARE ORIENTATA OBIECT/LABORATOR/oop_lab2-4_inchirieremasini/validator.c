#include <ctype.h>
#include <string.h>

int validate_masina(const char* numar, const char* categorie, const char* model) {
    //Returneaza 1 daca masina este valida, 0 altfel
    int i;
    for (i = 0; i < strlen(numar); i++) {
        if (!isalnum(numar[i])) {
            return 0;
        }
    }
    for (i = 0; i < strlen(categorie); i++) {
        if (!isalpha(categorie[i]) && !isspace(categorie[i])) {
            return 0;
        }
    }
    for (i = 0; i < strlen(model); i++) {
        if (!isalpha(model[i]) && !isspace(model[i])) {
            return 0;
        }
    }
    if (strlen(numar) == 0 || strlen(categorie) == 0 || strlen(model) == 0) {
        return 0;
    }
    return 1;
}