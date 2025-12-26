//
// Created by Iris on 6/21/2024.
//

#include "Validator.h"
#include <stdexcept>

bool Validator::valideazaDate(int dim, string tabla, string jucator, string stare) {
    string errors[] = { "Dimensiunea nu este 3,4 sau 5\n","Tabla nu are dim x dim caractere\n","Caracterele din tabla nu sunt doar X,O sau -\n","Jucatorul nu este X sau O\n","Starea nu este Neinceput,In derulare sau Terminat\n" };
    string myErrors;
    if (!(dim == 3 || dim == 4 || dim == 5))
        myErrors += errors[0];
    if (tabla.size() != dim * dim)
        myErrors += errors[1];
    for (char c : tabla)
        if (c != 'X' && c != 'O' && c != '-')
            myErrors += errors[2];
    if (jucator != "X" && jucator != "O")
        myErrors += errors[3];
    if (stare != "Neinceput" && stare != "In derulare" && stare != "Terminat")
        myErrors += errors[4];
    if (!myErrors.empty())
        throw std::invalid_argument(myErrors);
    return true;
}
