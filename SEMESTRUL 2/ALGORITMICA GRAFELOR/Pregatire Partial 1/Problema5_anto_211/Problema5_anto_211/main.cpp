#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#define INF 1000000
#define NMAX 10001
using namespace std;
ifstream fin("fisier.txt");
int n, a, b,c,sursa,destinatie;
vector < vector<pair<int, int>>>G(NMAX);

pair<vector<int>,vector<int>>Dijkstra(int sursa)
{
	vector<int>parinte(n+1);
	vector<int>dist(n+1);
	for (int i = 1; i <= n; i++)
	{
		dist[i] = INF;
		parinte[i] = -1;
	}
	dist[sursa] = 0;
	parinte[sursa] = 0;
	queue<int>Q;
	Q.push(sursa);
	while (!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		for (auto p : G[x])
		{
			if (dist[p.first] > p.second + dist[x] && dist[x]!=INF) {
				dist[p.first] = p.second + dist[x];
				parinte[p.first] = x;
				Q.push(p.first);
			}

		}
	}
	return make_pair(dist, parinte);
}
void afisare_drum(int varf,vector<int>parinte)
{
	if (parinte[varf] == 0)
	{
		cout << varf << " ";
		return;
	}
	afisare_drum(parinte[varf],parinte);
	cout << varf<< " ";
}
int main()
{
	fin >> n;
	for (int i = 1; i <= n; i++)
	{
		pair<int, int>p;
		fin >> a >> b>>c;
		p.first = b;
		p.second = c;
		G[a].push_back(p);
	}
	//for (int i = 1; i <= n; i++)
	//	for (auto p : G[i])
	//		cout << i << " " << p.first << " " << p.second << endl;
	cin >> sursa >> destinatie;
	pair<vector<int>, vector<int>> result = Dijkstra(sursa);
	vector<int> dist = result.first;
	vector<int> parinte = result.second;
	/*for (int i = 1; i <= n; i++)
		cout << dist[i] << " ";
	cout << endl;
	for (int i = 1; i <= n; i++)
		cout << parinte[i] << " ";*/
	cout << "Distanta de la " << sursa << " la destinatia " << destinatie << " este " << dist[destinatie]<<endl;
	afisare_drum(destinatie,parinte);
}