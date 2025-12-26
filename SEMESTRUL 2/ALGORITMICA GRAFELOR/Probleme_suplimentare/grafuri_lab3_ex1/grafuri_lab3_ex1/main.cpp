#include <iostream>
#include <fstream>
#define INF 10000000
using namespace std;
int v, m, w, nr_vf, a, b, sursa;
int matrice[101][101], distanta[101];
bool S[101];
int extract_min()
{
    int min = INF, index = 0;
    for (int i = 0; i < nr_vf; i++)
        if (S[i] == false && distanta[i] < min)
        {
            min = distanta[i];
            index = i;
        }
    return index;
}
void Dijkstra(int sursa)
{
    for (int i = 0; i < nr_vf; i++)
        distanta[i] = INF;
    distanta[sursa] = 0;
    for (int i = 0; i < nr_vf - 1; i++)
    {
        int u = extract_min();
        S[u] = true;
        for (int v = 0; v < nr_vf; v++)
            if (!S[v] && matrice[u][v] && distanta[u] != INF)
                if (distanta[v] > distanta[u] + matrice[u][v])
                    distanta[v] = distanta[u] + matrice[u][v];

    }
}
int main(int argc, char** argv)
{
    ifstream f(argv[1]);
    ofstream g(argv[2]);

    f >> nr_vf>> m >> sursa;

    while (f >> a >> b >> w)
    {
        matrice[a][b] = w;
    }
    Dijkstra(sursa);
    for (int i = 0; i < nr_vf; i++)
    {
        cout << distanta[i] << " ";
        g << distanta[i] << " ";
    }
    cout << endl;
    f.close();
    g.close();
    return 0;
}

