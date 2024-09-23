#include<iostream>
#include<fstream>
#include<queue>
#define INF 1000000
using namespace std;
ifstream fin("graf.txt");
struct Graf
{
	int nrv;
	int muchii[100][100] = { 0 };
};
Graf citire()
{
	int n, a, b;
	Graf G;
	fin >> n;
	G.muchii[100][100] = {0};
	while (fin >> a >> b)
	{
		G.muchii[a][b] = 1;
	}
	G.nrv = n;
	return G;
}
pair<int* , int*> Moore(Graf G, int u)
{
	int l[100] = { 0 };
	int p[100] = { 0 };
	for (int i = 1; i <= G.nrv; i++) {
		l[i] = INF;
		p[i] = -1;
	}
	l[u] = 0;
	queue<int> Q;
	Q.push(u);
	while (!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		for (int i = 1; i <= G.nrv; i++) {
			if (G.muchii[x][i] == 1  && l[i] == INF) {
				p[i] = x;
				l[i] = l[x] + 1;
				Q.push(i);
			}
		}
	}
	return make_pair(l,p);
}
void drum(int* p, int poz)
{
	/*if (p[varf] == 0)
	{
		cout << "Nu exista lant\n";
		return;
	}*/
	int drum[100] = { 0 };
	int index=1;
	while (poz != -1) {
			drum[index++] =poz ;
			poz = p[poz];
	}
	cout << "lantul cel mai scurt este:\n";
	for (int i = index-1; i >= 1; i--)
	{
		cout << drum[i];
		if (i != 1)
			cout << " -> ";
	}
	cout << endl;
}
int main()
{
	/*1. Implementați algoritmul lui Moore pentru un graf orientat neponderat 
	(algoritm bazat pe Breath-first search, vezi cursul 2). 
	Datele sunt citete din fisierul graf.txt. 
	Primul rând din graf.txt conține numărul vârfurilor, iar următoarele rânduri conțin
	muchiile grafului. Programul trebuie să afiseze lanțul cel mai scurt dintr-un vârf
	(vârful sursa poate fi citit de la tastatura).*/
	int varf;
	cout << "Introduceti varful:\n";
	cin >> varf;
	Graf G = citire();
	cout << G.nrv<<endl;
	for (int i = 1; i <= G.nrv; i++, cout << endl)
		for (int j = 1; j <= G.nrv; j++)
			cout << G.muchii[i][j]<<" ";
	pair<int*, int*> rezultat = Moore(G, varf);
	int* l = rezultat.first;
	int* p = rezultat.second;
	int lmax = 0, poz = 0;
	for (int i = 1; i <= G.nrv; i++)
		if (lmax < l[i] and l[i]!=INF) {
			lmax = l[i];
			poz = i;
		}
	drum(p, poz);
	cout << "lungimea drumului minim este:" << lmax<<" incepe de pe pozitia " <<poz;
	//drum(p, poz);
	return 0;
}