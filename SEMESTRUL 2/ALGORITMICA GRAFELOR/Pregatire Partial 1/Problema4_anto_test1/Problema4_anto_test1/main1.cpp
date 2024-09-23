#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<queue>
#define INF 1000000
#define NMAX 1005
using namespace std;
ifstream fin("fisier.txt");
vector < vector<pair<int, int>>>G(NMAX);
vector<pair<int, int>>C;
int n, m, a, b,sursa,destinatie;
vector<int>distanta;
int extract_min(vector<int>dist,vector<bool>s)
{
	int min = INF, index = 0;
	for (int i = 1; i <= n; i++)
	{
		if (s[i] == false && dist[i] < min)
		{
			min = dist[i];
			index = i;
		}
	}
	return index;
}
vector<int> Dijkstra2(int source) {
	vector<int> dist(n + 1);
	vector<bool>s(n + 1, false);
	for (int i = 1; i <= n; ++i) {
		if (i != source) {
			dist[i] = INF;
		}
		else {
			dist[i] = 0;
		}
	}

	for(int i=1;i<=n;i++){
		int val = extract_min(dist,s);
		s[val] = true;
		for (auto p : G[val]) {
			if (dist[val] + p.second < dist[p.first]) {
				dist[p.first] = dist[val] + p.second;
			}
		}
	}

	return dist;
}
vector<int> Dijkstra(int source) {
	queue<int> q;
	vector<int> dist(n + 1);
	q.push(source);

	for (int i = 1; i <= n; ++i) {
		if (i != source) {
			dist[i] = INF;
		}
		else {
			dist[i] = 0;
		}
	}

	while (!q.empty()) {
		int val = q.front();
		q.pop();
		for (auto p : G[val]) {
			if (dist[val] + p.second < dist[p.first]) {
				q.push(p.first);
				dist[p.first] = dist[val] + p.second;
			}
		}
	}

	return dist;
}
int pondere(pair<int, int>a, pair<int, int>b)
{
	//cout << a.first << " " << b.first << " " << a.second << " " << b.second << endl;
	int x = (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
	x =(int)sqrt(x);
	return x;
}
int main()
{
	fin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		fin >> a >> b;
		pair<int, int>p;
		p.first = a;
		p.second = b;
		C.push_back(p);
	}
	for (int i = 1; i <= m; i++)
	{
		fin >> a >> b;
		int w = pondere(C[a-1], C[b-1]);
		pair<int, int>p;
		p.first = b;
		p.second = w;
		G[a].push_back(p);
	}
	cout << "Legaturile si distanta drumurilor \n";
	for (int i = 1; i <= n; i++)
	{
		for (auto p : G[i])
			cout << i << " " << p.first << " " << p.second << " "<<endl;
	}
	cout << "Varf sursa \n";
	cin >> sursa;
	cout << "Varf destinatie \n";
	cin >> destinatie;
	vector<int>dist = Dijkstra2(sursa);
	if (dist[destinatie] != INF) {
		cout << "distanta de la " << sursa << " la destinatie " << destinatie << " este " << dist[destinatie];
	}
	else
		cout << "distanta de la " << sursa << " la destinatie " << destinatie << " este INF";
}