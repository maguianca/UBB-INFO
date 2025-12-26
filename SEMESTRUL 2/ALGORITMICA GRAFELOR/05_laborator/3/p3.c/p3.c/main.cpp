#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");
int n;
vector<int> L;
vector<vector<int>> G;

void Eulerian(int k)
{
    for (int i = 0; i < n; i++)
        if (G[k][i] != 0)
        {
            G[k][i] = G[i][k] = 0;
            Eulerian(i);
        }
    L.push_back(k);
}

int main()
{
    int x, y, m;
    fin >> n >> m;
    G = vector<vector<int>>(n, vector<int>(n, 0));
    for (int i = 1; i <= m; i++)
    {
        fin >> x >> y;
        G[x][y] = G[y][x] = 1;
    }
    Eulerian(0);
    for (auto& y : L)
        fout << y << " ";
    return 0;
}
