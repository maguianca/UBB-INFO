#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
ifstream f("kruskal.in");
ofstream g("kruskal.out");

struct muchie {
    int x, y,cost;

}v[10001],rez[100001];
int t[10001], rang[10001], n, m, z, sum;
bool criteriu(muchie a, muchie b)
{
    return a.cost < b.cost;
}

int multime(int nod)
{
    if (t[nod] != nod) return multime(t[nod]);
    return nod;
}

void unire(int x, int y)
{
    if (rang[x] < rang[y])
        t[y] = t[x];
    else
    {
        t[x] = t[y];
        if (rang[x] == rang[y])
            rang[x]++;
    }
}


int main()
{
    int i,tatax,tatay;
    f >> n >> m;
    for (i = 1; i <= m; i++)
    {
        f >> v[i].x >> v[i].y >> v[i].cost;

    }

    sort(v + 1, v + m + 1, criteriu);

    for (i = 1; i <= n; i++) t[i] = i;

    for (i = 1; i <= m&&z<n; i++)
    {
        tatax = multime(v[i].x);
        tatay = multime(v[i].y);
        if (tatax != tatay)
        {
            unire(tatax, tatay);
            sum += v[i].cost;
            z++;
            rez[z].x = v[i].x;
            rez[z].y = v[i].y;
        }
    }

    g << sum << '\n';//costul minim al arboreului minim de acoperire
    g<<z<<'\n';//nr muchii al arborelui
    for (i = 1; i <= z; i++)//muchiile arborelui
    {
        g << rez[i].x << " " << rez[i].y << '\n';
    }
    return 0;
}
