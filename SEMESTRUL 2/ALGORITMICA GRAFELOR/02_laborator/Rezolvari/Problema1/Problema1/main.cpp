/*1. Implementați algoritmul lui Moore pentru un graf orientat neponderat
	(algoritm bazat pe Breath-first search, vezi cursul 2).
	Datele sunt citete din fisierul graf.txt.
	Primul rând din graf.txt conține numărul vârfurilor, iar următoarele rânduri conțin
	muchiile grafului. Programul trebuie să afiseze lanțul cel mai scurt dintr-un vârf
	(vârful sursa poate fi citit de la tastatura).*/
#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#define INF 10000
using namespace std;
ifstream fin("graf.txt");
vector<int> G[100];
int l[100] = { 0 };
int p[100] = { 0 };
//int l[100], p[100], n, varf, varf_final;
struct Graf
{
	int nrv;
	int matrice[100][100] = { 0 };
};

Graf citire()
{
	int n, a, b;
	Graf G;
	fin >> n;
	while (fin >> a >> b)
		G.matrice[a][b] = 1;
	G.nrv = n;
	return G;
}
pair<int*, int*>Moore(Graf G,int u)
{
	queue<int>Q;
	for (int i = 1; i <= G.nrv; i++)//initializare
	{
		l[i] = INF;
		p[i] = -1;
	}
	l[u] = 0;
	p[u] = 0;
	Q.push(u);
	while (!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		for (int i = 1; i <= G.nrv; i++) {
			if ( G.matrice[x][i] == 1  && l[i] == INF) {
				p[i] = x;
				l[i] = l[x] + 1;
				Q.push(i);
			}
		}
	}
	return make_pair(l, p);
}
void afiseaza(int varf_final, int* p)
{
	if (p[varf_final] == 0)
	{
		cout << varf_final << "->";
		return;
	}
	afiseaza(p[varf_final], p);
	cout << varf_final << "->";
	
}
int main()
{
	int varf,varf_final;
	cout << "Introduceti varful sursa: ";
	cin >> varf;
	cout << "Introduceti varful final: ";
	cin >> varf_final;
	Graf G = citire();
	cout << "Sunt " << G.nrv << " muchii\n";
	cout << "Matricea de adiacenta este:\n";
	for(int i=1;i<=G.nrv;i++,cout<<endl)
		for (int j = 1; j <= G.nrv; j++)
		{
			cout << G.matrice[i][j]<<" ";
		}
	pair<int*, int*>rezultat= Moore(G, varf);
	int* l = rezultat.first;
	int* p = rezultat.second;
	if (l[varf_final] == INF)
	{
		cout << "Nu exista drum\n";
		return 0;
	}
	afiseaza(varf_final, p);
	return 0;
}