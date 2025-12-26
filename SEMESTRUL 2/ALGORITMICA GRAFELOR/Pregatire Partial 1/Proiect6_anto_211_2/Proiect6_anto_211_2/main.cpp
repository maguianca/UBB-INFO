#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<queue>
#define INF 1000000
#define NMAX 10005
using namespace std;
ifstream fin("fisier.txt");
vector < vector<pair<int, int>>>G(NMAX);
vector<pair<int, int>>C;
int n, m, a, b,c, sursa, destinatie;
vector<int>distanta;
vector<bool>s{ false };
pair<vector<int>,vector<int>> Dijkstra(int source) {
	queue<int> q;
	vector<int> dist(n + 1);
	vector<int>parinte(n + 1);
	q.push(source);

	for (int i = 1; i <= n; ++i) {
		if (i != source) {
			dist[i] = INF;
			parinte[i] = -1;
		}
		else {
			dist[i] = 0;
			parinte[i] = 0;
		}
	}

	while (!q.empty()) {
		int val = q.front();
		q.pop();
		for (auto p : G[val]) {
			if (dist[val] + p.second < dist[p.first]) {
				q.push(p.first);
				dist[p.first] = dist[val] + p.second;
				parinte[p.first] = val;
			}
		}
	}

	return make_pair(dist,parinte);
}
void afisare_drum(int varf, vector<int>parinte)
{
	if (parinte[varf] == 0)
	{
		cout << varf << "->";
		return;
	}
	afisare_drum(parinte[varf], parinte);
	cout << varf << "->";
}
vector<int> drum(int sursa, int destinatie, vector<int> parinte, vector<int> dist)
{
	vector<int> u;
	int nod_curent = destinatie;
	while (nod_curent != sursa) {
		u.push_back(nod_curent);
		nod_curent = parinte[nod_curent];
	}
	u.push_back(sursa);
	reverse(u.begin(), u.end());
	return u;
}
int main()
{
	fin >> m;
	while(fin>>a>>b>>c)
	{
		if (a > n)
			n = a;
		if (b > n)
			n = b;
		pair<int, int>p;
		p.first = b;
		p.second = c;
		G[a].push_back(p);
	}
	cout << "Legaturile si distanta drumurilor \n";
	for (int i = 1; i <= n; i++)
	{
		for (auto p : G[i])
			cout << i << " " << p.first << " " << p.second << " " << endl;
	}
	cout << "Varf sursa \n";
	cin >> sursa;
	cout << "Varf destinatie \n";
	cin >> destinatie;
	pair<vector<int>,vector<int>>p = Dijkstra(sursa);
	vector<int>dist = p.first;
	vector<int>parinte = p.second;
	if (dist[destinatie] != INF) {
		cout << "distanta de la " << sursa << " la destinatie " << destinatie << " este " << dist[destinatie]<<endl;
		afisare_drum(destinatie, parinte);
		cout << endl << endl;
		vector<int>u = drum(sursa, destinatie, parinte,distanta);
		for (auto x : u)
			cout << x << " ";

	}
	else
		cout << "distanta de la " << sursa << " la destinatie " << destinatie << " este INF";
}