/*

4. Pentru un graf dat să se afișeze pe ecran vârfurile descoperite de 
algoritmul BFS și distanța față de vârful sursă 
(arborele descoperit).*/

#include <iostream>
//#include <fstream>

using namespace std;
//ifstream fin("citire.txt");
int a[101][101], n;//matricea de adiacenta, n=nr de varfuri
int v[101];//lista varfurilor vizitate, initial toate nevizitate=0
int x[101];//varfurile gri din coada
int start=0;

void bfs(int start)
{
    int i, k, st, dr;
    //initializez coada
    st = dr = 1;
    x[1] = start;
    v[start] = 1;//vizitez varful initial
    while (st <= dr)//cat timp coada nu este vida
    {
        k = x[st];//preiau un element din coada
        for (i = 1; i <= n; i++)//parcurg varfurile
            if (v[i] == 0 && a[k][i] == 1)//daca i este vecin cu k si nu este vizitat
            {
                v[i] = 1;//il vizitez
                x[++dr] = i;//il adaug in coada
            }
        st++;//sterg din coada
    }
}

int main() {

    int varf;

    cout << "introduceti nr de vf si matricea de adiacenta";
    cin >> n;//nr de varfuri
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> a[i][j];

    cout << "introduceti nodul de inceput pentru gasirea arborelui:";
    cin >> varf;

    bfs(varf);

    cout << "varfurile arborelui gasit sunt: ";
    for (int i = 1; i <= n; i++)
        if (v[i] == 1)
            cout << i << " ";

    return 0;
}