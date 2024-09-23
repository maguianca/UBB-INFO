#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#define INF 100000000

using namespace std;

int varf, muchie;

struct varfuri
{
	int parinte;
	int distanta;
	int index;

}V;
struct muchii
{
	int sursa;
	int destinatie;
	int pondere;
}E;
void initializare(vector<varfuri>&V, int sursa)
{
	for (int v = 0; v <V.size(); v++) {
			V[v].distanta = INF;
			V[v].parinte = -1;//NIL

	}
	V[sursa].distanta = 0;

}
void relaxare(vector<varfuri>& V, muchii& E)
{
	int u = E.sursa;
	int v = E.destinatie;
	int w = E.pondere;
	if (V[v].distanta > V[u].distanta + w)
	{
		V[v].distanta = V[u].distanta + w;
		V[v].parinte = u;

	}
}
bool Bellman_Ford(vector<varfuri>& V, vector<muchii>& E, int sursa)
{
	initializare(V, sursa);
	for (int i = 0; i < V.size(); i++)
	{
		for (int j = 0; j < E.size(); j++)
			relaxare(V, E[j]);
	}
	for (int i = 0; i < E.size(); i++)
	{
		int u = E[i].sursa;
		int v = E[i].destinatie;
		int w = E[i].pondere;
		if (V[v].distanta > V[u].distanta + w)
			return false;
	}
	return true;
}
int extract_min(vector<bool>& S, vector<int>& distanta) {
	int min_distanta = INF, index = -1;
	for (int i = 0; i < distanta.size(); ++i) {
		if (!S[i] && distanta[i] < min_distanta) {
			min_distanta = distanta[i];
			index = i;
		}
	}
	return index;
}

void Dijkstra(vector<muchii>& E, vector<int>& distanta, int sursa) {
	int dim = distanta.size();
	int dem = E.size();
	vector<bool> S(dim, false); // noduri procesate
	distanta[sursa] = 0;

	for (int i = 0; i <dim+1; ++i) {
		int u = extract_min(S, distanta);
		if (u == -1) break; // iesim cand nu mai avem noduri neprocesare
		S[u] = true;

		// actualizam distanta
		for (int j = 0; j <dim+1; j++) {
			int v = E[j].destinatie;
			int w = E[j].pondere;
			int u = E[j].sursa;
			if (!S[v] && distanta[u] != INF ) {
				if (distanta[v] > distanta[u] + w) {
					distanta[v] = distanta[u] + w;
				}
			}
		}
	}
}
void adaugaNodQ(vector<varfuri>& V, vector<muchii>& E)
{
	int n = V.size();
	for (int i = 0; i < n; ++i)
	{
		muchii edge = { n, i, 0 }; //adaugam o noua muchie cu pondere zero la fiecare nod existent
		E.push_back(edge); 
	}
	V.push_back({ -1, 0, n }); 
}
void repondereMuchii(vector<varfuri>& V, vector<muchii>& E)
{
	for (int i = 0; i < E.size(); ++i)
	{
		int u = E[i].sursa;
		int v = E[i].destinatie;
		int w = E[i].pondere;
		E[i].pondere = w + V[u].distanta - V[v].distanta;
	}
}

vector<vector<int>> Johnson(vector<varfuri>& V, vector<muchii>& E)
{
	vector<vector<int>> D(varf, vector<int>(varf, 0));
	adaugaNodQ(V, E);
	if (!Bellman_Ford(V, E, varf)) {
		cout << "Graful contine un ciclu negativ!";
		exit(1);
	}
	else
	{
		repondereMuchii(V, E); 
		for (int i = 0; i < E.size(); ++i)
		{
			if (E[i].sursa != varf)
				cout << E[i].sursa << " " << E[i].destinatie << " " << E[i].pondere << endl;
		}
	}
	for (int u = 0; u < varf; ++u) {
		vector<int> distanta(varf, INF);
		Dijkstra(E, distanta, u);
		for (int v = 0; v < varf; ++v) {
			if (distanta[v] != INF)
				D[u][v] = distanta[v] + V[v].distanta - V[u].distanta;
			else
				D[u][v] = INF;
		}
	}
	return D;
}
int main(int argc,char**argv)
{
	int s,d,p;
	ifstream f(argv[1]);
	ofstream g(argv[2]);
	f >> varf >> muchie;
	vector<varfuri>V(varf);
	vector<muchii>E(muchie);
	for (int i = 0; i < muchie; i++) {
		f >> s >> d >> p;
		E[i] = {s,d,p};
	}
	vector<vector<int>> D=Johnson(V,E);
	for (int i = 0; i < E.size(); ++i)
	{
		if (E[i].sursa != varf)//daca muchia e diferita de muchiile nou adaugate cu pondere 0
			g << E[i].sursa << " " << E[i].destinatie << " " << E[i].pondere << endl;
	}
	for (int i = 0; i < varf; ++i) {
		for (int j = 0; j < varf; ++j) {
			if (D[i][j] != INF) {
				cout << D[i][j] << " ";
				g << D[i][j] << " ";
			}
			else {
				cout << "INF ";
				g<< "INF ";
			}
		}
		cout << endl;
		g << endl;
	}
	return 0;
}

