#include<iostream>
#include<fstream>
#define INF 1000000
using namespace std;
ifstream fin("in.txt");
int matrice[1001][1001], n, sursa, destinatie, distanta[1001],p[1001], distanta1[1001];
bool s[1001] = { false };
int extract_min()
{
	int min = INF, index = 0;
	for (int i = 1; i <=n; i++)
	{
		if (s[i] == false && distanta[i] < min)
		{
			min = distanta[i];
			index =i;
		}
	}
	return index;
}
void Dijkstra(int sursa,int destinatie)
{
	for (int i = 1; i <= n; i++) {
		distanta[i] = INF;
		p[i] = 0;
	}
	distanta[sursa] = 0;
	for (int i = 1; i <=n; i++)
	{
		int u = extract_min();
		s[u] = true;
		for (int v = 1; v <=n; v++)
		{
			if (s[v] == false && distanta[u] != INF && matrice[u][v] !=0)
				if (distanta[v] > distanta[u] + matrice[u][v]) {
					distanta[v] = distanta[u] + matrice[u][v];
					p[v] = u;
				}
		}

	}
	cout << "distanta de la " << sursa << " la destinatie " <<destinatie<< " este " << distanta[destinatie];
}
void Bellman_Ford1(int sursa,int destinatie )
{
	for (int i = 0; i <=n; i++)
	{
		distanta1[i] = INF;
		p[i] = -1;
	}
	distanta1[sursa] = 0;
	for (int i = 1; i <=n; i++)
		for (int j = 1; j <=n; j++)
			if (matrice[i][j])
				if (distanta1[j] > distanta1[i] + matrice[i][j])
				{
					distanta1[j] = distanta1[i] + matrice[i][j];
					p[j] = i;
				}
	cout << "distanta de la " << sursa << " la destinatie " << destinatie << " este " << distanta1[destinatie] << endl;
}
void Bellman_Ford(int sursa,int destinatie)
{
	for (int i = 1; i <= n; i++)
	{
		distanta1[i] = INF;
		p[i] = 0;
	}
	distanta1[sursa] = 0;
	/*for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			if (matrice[i][j]!=0)
			{
				if (distanta1[j] > distanta1[i] + matrice[i][j] && distanta1[i]!=INF)
				{
					distanta1[j] = distanta1[i] + matrice[i][j];
					p[j] = i;
				}
			}
		}
	*/
	for (int i = 1; i <= n - 1; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= n; k++) {
				if (matrice[j][k] != 0 && distanta1[j] != INF && distanta1[k] > distanta1[j] + matrice[j][k]) {
					distanta1[k] = distanta1[j] + matrice[j][k];
					p[k] = j;
				}
			}
		}
	}
	cout << "distanta de la " << sursa << " la destinatie " <<destinatie<< " este " << distanta1[destinatie]<<endl;

}
void afiseaza(int varf_final)
{
	if (p[varf_final]==0)
	{
		cout << varf_final << "->";
		return;
	}
	afiseaza(p[varf_final]);
	cout << varf_final << "->";

}
int main()
{
	int a, b,c;
	//n = 0;
	fin >>n>> sursa >> destinatie;
	while (fin >> a >> b >> c)
	{
		matrice[a][b] = c;
		//n++;
	}
	//Dijkstra(sursa, destinatie);
	Bellman_Ford(sursa, destinatie);
	afiseaza(destinatie);
	return 0;
}