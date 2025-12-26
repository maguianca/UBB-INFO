#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int n, m, matrice[100][100];

bool BFS(int s, int d, int parent[]) {
    queue <int> Q;
    bool viz[100];
    memset(viz, 0, sizeof(viz));

    viz[s] = true;
    parent[s] = -1;

    Q.push(s);
    while (!Q.empty()) {
        int nod = Q.front();
        Q.pop();
        for (int i = 0; i < n; i++) {
            if (viz[i] == false && matrice[nod][i] > 0) {
                if (i == d) {
                    parent[i] = nod;
                    return true;
                }
                Q.push(i);
                parent[i] = nod;
                viz[i] = true;

            }
        }
    }

    return false;
}

void Ford_Fulkerson(int s, int d) {

    int parent[100];
    int max_flow = 0;

    while (BFS(s, d, parent)) {
        int path_flow = INT_MAX;
        for (int i = d; i != s; i = parent[i]) {
            int u = parent[i];
            path_flow = min(path_flow, matrice[u][i]);
        }

        for (int i = d; i != s; i = parent[i]) {
            int u = parent[i];
            matrice[u][i] -= path_flow;
            matrice[i][u] += path_flow;
        }

        max_flow += path_flow;
    }

    fout << "Fluxul maxim este: " << max_flow;

}

int main() {
    int x, y, capacitate;

    fin >> n >> m;
    for (int i = 1; i <= m; i++) {
        fin >> x;
        fin >> y;
        fin >> capacitate;
        matrice[x][y] = capacitate;
    }

    Ford_Fulkerson(0, n - 1);
}