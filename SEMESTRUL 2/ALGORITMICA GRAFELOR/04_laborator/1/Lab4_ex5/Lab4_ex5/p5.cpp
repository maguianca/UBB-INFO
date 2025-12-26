#include <iostream>
#include <vector>
#include <fstream>
#define INF 100000000

using namespace std;

//extrage nodul cu cheia minima
int extract_min(const vector<int>& key, const vector<bool>& viz, int n) {
    int min = INF;
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (!viz[i] && key[i] < min) {
            min = key[i];
            index = i;
        }
    }
    return index;
}


pair<int, vector<pair<int, int>>> prim(int n, const vector<vector<pair<int, int>>>& adjList, int start) {
    vector<int> key(n, INF); 
    vector<int> parinte(n, -1);
    vector<bool> viz(n, false); 
    vector<pair<int, int>> muchii;

    key[start] = 0;

    int totalCost = 0;

    for (int i = 0; i < n; i++) {
        int u = extract_min(key,viz, n);
        viz[u] = true;
        if (parinte[u] != -1) {
            muchii.emplace_back(parinte[u], u);
            totalCost += key[u];
        }
        for (auto p : adjList[u]) {
            int v = p.first;
            int pondere = p.second;

            if (!viz[v] && pondere < key[v]) {
                key[v] = pondere; 
                parinte[v] = u;  
            }
        }
    }
    return { totalCost, muchii };
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n, m; 
    fin >> n >> m;
    vector<vector<pair<int, int>>> adjList(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        fin >> u >> v >> w; 
        adjList[u].emplace_back(v, w);
        adjList[v].emplace_back(u, w);
    }
    int varf = 0;
    auto result = prim(n, adjList, varf);

    int totalCost = result.first; 
    auto muchii = result.second;

    fout << totalCost << endl;
    fout << muchii.size() << endl;
    for (auto edge : muchii) {
        fout << edge.first << " " << edge.second << endl;
    }
    return 0;
}
