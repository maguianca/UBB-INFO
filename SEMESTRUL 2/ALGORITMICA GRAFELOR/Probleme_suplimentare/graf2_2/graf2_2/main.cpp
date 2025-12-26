#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("fisier.txt");
int matrice[100][100], n, matrice_inchidere[100][100];
void citire()
{
    fin >> n;
    for (int i = 1; i <=n; i++)
        for (int j = 1; j <=n; j++)
            fin >> matrice[i][j];
}
void inchidere_matrice(){

    for (int i = 1; i <=n; ++i) {
        for (int j =1; j <=n; ++j) {
            matrice_inchidere[i][j] = matrice[i][j];
        }
    }

   
    for (int k = 1; k <=n; k++) {
        for (int i =1; i <=n; i++) {
            for (int j =1; j <=n; j++) {
                if(matrice_inchidere[i][j]==1|| matrice_inchidere[i][k]==1 && matrice_inchidere[k][j]==1)
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
    for (int i =1; i <=n; i++,cout<<endl)
        for (int j = 1; j <=n; j++)
            cout << matrice_inchidere[i][j] << " ";

    return 0;
}
