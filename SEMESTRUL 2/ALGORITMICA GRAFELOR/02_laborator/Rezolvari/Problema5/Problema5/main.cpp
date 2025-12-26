/*/*5. Pentru un graf dat să se afișeze pe ecran vârfurile descoperite de apelul
recursiv al procedurii DFS_VISIT(G, u)
(apadurea descoperită de DFS).*/

#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("citire.txt");
int a[101][101], n;//matricea de adiacenta, n=nr de varfuri
int v[101];//lista vf vizitate

void dfs(int k)
{
    v[k] = 1; 
    cout << k << " ";
    for (int i = 1; i <= n; i++) // determinam vecinii nevizitati ai lui x
        if (a[k][i] == 1 && v[i] == 0)
        {
            dfs(i); // continuam parcurgerea cu vecinul curent i
        }
}


int main() {

    int varf;
    fin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            fin >> a[i][j];

    cout << "arborii gasiti in padurea dfs sunt:";
    for (int i = 1; i <= n; i++)
        if (v[i] == 0)
        {
            cout << endl;
            dfs(i);
        }

    return 0;
}