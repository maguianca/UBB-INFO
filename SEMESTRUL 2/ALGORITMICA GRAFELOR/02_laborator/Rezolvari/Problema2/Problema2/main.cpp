/*2. Sa se determine închiderea transitivã a unui graf orientat. (Închiderea tranzitivã poate fi 
reprezentatã ca matricea care descrie, pentru fiecare vârf în parte, care sunt vârfurile accesibile 
din acest vârf. Matricea inchiderii tranzitive aratã unde se poate ajunge din fiecare vârf.) ex. 
figura inchidere_tranzitiva.png - pentru graful de sus se construieste matricea de jos care arata 
inchiderea tranzitiva.*/
#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("citire.txt");

int matrice[100][100], n, matrice_inchidere[100][100];

void citire()
{
    fin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            fin >> matrice[i][j];
}
void inchidere_matrice() {

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            matrice_inchidere[i][j] = matrice[i][j];
        }
    }


    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (matrice_inchidere[i][j] == 1 || matrice_inchidere[i][k] == 1 && matrice_inchidere[k][j] == 1)
                    matrice_inchidere[i][j] = 1;
                else
                    matrice_inchidere[i][j] = 0;
            }
        }
    }


}

int main() {

    citire();
    inchidere_matrice();
    cout << "Matricea inchiderii tranzitive este:\n";
    for (int i = 1; i <= n; i++, cout << endl)
        for (int j = 1; j <= n; j++)
            cout << matrice_inchidere[i][j] << " ";

    return 0;
}
