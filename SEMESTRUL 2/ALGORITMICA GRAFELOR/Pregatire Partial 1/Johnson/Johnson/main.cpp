/*#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1 << 30;
const int NMAX = 1005;

int n, m;
vector<vector<pair<int, int>>> G(NMAX), newG(NMAX);

vector<int> BellmanFord(int source) {
    vector<int> dist(n + 1);

    for (int i = 0; i <= n; ++i) {
        dist[i] = INF;
    }
    dist[source] = 0;

    for (int i = 0; i <= n; ++i) {
        for (auto p : G[i]) {
            int u = i;
            int v = p.first;
            int w = p.second;

            if (dist[u] != NMAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    for (int i = 0; i <= n; ++i) {
        for (auto p : G[i]) {
            int u = i;
            int v = p.first;
            int w = p.second;

            if (dist[u] != NMAX && dist[u] + w < dist[v]) {
                vector<int> negSol;
                return negSol;
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
        for (auto p : newG[val]) {
            if (dist[val] + p.second < dist[p.first]) {
                q.push(p.first);
                dist[p.first] = dist[val] + p.second;
            }
        }
    }

    return dist;
}

void Johnson() {

    //Adaugam un nou nod
    for (int i = 1; i <= n; ++i) {
        pair<int, int> p = make_pair(i, 0);
        G[0].push_back(p);
    }

    //Facem BellmanFord
    vector<int> dist = BellmanFord(0);
    if (dist.empty()) {
        cout << -1;
        return;
    }
   // for (int i = 1; i <= n; i++)
    //    cout << dist[i] << " ";
    //cout << endl;


    vector<int>distanta_vect(m+1,0);
    int cnt = 1;
    //Reponderam
    for (int i = 1; i <= n; ++i) {
        for (auto p : G[i]) {
            pair<int, int> newP;
            newP = p;
            newP.second += (dist[i] - dist[newP.first]);
            distanta_vect[cnt++] = dist[newP.first];
            newG[i].push_back(newP);
        }
    }

    //Afisam graful reponderat
    for (int i = 1; i <= n; ++i) {
        for (auto p : newG[i]) {
            cout << i - 1 << " " << p.first - 1 << " " << p.second << '\n';
        }
    }

    //Facem Dijkstra pt toate nodurile
    for (int i = 1; i <= n; ++i) {
        vector<int>dist1 = Dijkstra(i);
        for (int j = 1; j <= n; ++j) {
            if (dist1[j] == INF) {
                cout << "INF";
            }
            else {
                cout << dist1[i];
               // cout << dist1[j]-dist[i]+distanta_vect[j];
                //cnt++;
            }
            cout << " ";
        }
        cout << '\n';
    }
    
}
/*
void Johnson() {

    //Adaugam un nou nod
    for (int i = 1; i <= n; ++i) {
        pair<int, int> p = make_pair(i, 0);
        G[0].push_back(p);
    }

    //Facem BellmanFord
    vector<int> dist = BellmanFord(0);
    if (dist.empty()) {
        cout << -1;
        return;
    }

    //Reponderam
    for (int i = 1; i <= n; ++i) {
        for (auto p : G[i]) {
            pair<int, int> newP;
            newP = p;
            newP.second += (dist[i] - dist[newP.first]);
            newG[i].push_back(newP);
        }
    }
    cout << endl;
    //Afisam graful reponderat
    for (int i = 1; i <= n; ++i) {
        for (auto p : newG[i]) {
           // cout << i - 1 << " " << p.first - 1 << " " << p.second << '\n';
        }
    }

    //Facem Dijkstra pt toate nodurile
    for (int i = 1; i <= n; ++i) {
        vector<int> dist1 = Dijkstra(i);
        //for (auto p : newG[i]) {
        //    if (dist1[i]!=INF) {
        //        dist1[i] = dist1[i] - dist[i] + dist[p.second];
        //    }
        //}
        for (int j = 1; j <= n; ++j) {
            if (dist1[j] == INF) {
                cout << "INF ";
            }
            else {
                cout << newG[i][0].first<<" ";
                // Ajustăm distanțele pentru a reflecta corect distanțele din graful original
                //cout << dist1[j] - (dist[i] - dist[newG[i][0].second]) << " ";
                //cout << dist1[j]<<" ";
            }
        }
        //cout << '\n';
    }
}

int main() {
    ifstream f("fisier.in");

    f >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int x, y, w;
        f >> x >> y >> w;
        x++, y++;
        pair<int, int> p = make_pair(y, w);
        G[x].push_back(p);
    }

    Johnson();

    f.close();
    return 0;
}
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1 << 30;
const int NMAX = 3005;

int n, m;
vector<vector<pair<int, int>>> G(NMAX), newG(NMAX);

vector<int> BellmanFord(int source) {
    vector<int> dist(n + 1);

    for (int i = 0; i <= n; ++i) {
        dist[i] = INF;
    }
    dist[source] = 0;
    for (int k = 1; k <= n; k++) {
        for (int i = 0; i <= n; ++i) {
            for (auto p : G[i]) {
                int u = i;
                int v = p.first;
                int w = p.second;

                if (dist[u] != INF && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }
    }
    for (int i = 0; i <= n; ++i) {
        for (auto p : G[i]) {
            int u = i;
            int v = p.first;
            int w = p.second;

            if (dist[u] != INF && dist[u] + w < dist[v]) {
                vector<int> negSol;
                return negSol;
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
        for (auto p : newG[val]) {
            if (dist[val] + p.second < dist[p.first]) {
                q.push(p.first);
                dist[p.first] = dist[val] + p.second;
            }
        }
    }

    return dist;
}

void Johnson() {

    //Adaugam un nou nod
    for (int i = 1; i <= n; ++i) {
        pair<int, int> p = make_pair(i, 0);
        G[0].push_back(p);
    }

    //Facem BellmanFord
    vector<int> dist = BellmanFord(0);
    if (dist.empty()) {
        cout << -1;
        return;
    }

    //Reponderam
    for (int i = 1; i <= n; ++i) {
        for (auto p : G[i]) {
            pair<int, int> newP;
            newP = p;
            newP.second += (dist[i] - dist[newP.first]);
            newG[i].push_back(newP);
        }
    }

    //Afisam graful reponderat
    for (int i = 1; i <= n; ++i) {
        for (auto p : newG[i]) {
            cout << i - 1 << " " << p.first - 1 << " " << p.second << '\n';
        }
    }

    //Facem Dijkstra pt toate nodurile
    for (int i = 1; i <= n; ++i) {
        vector<int>dist1 = Dijkstra(i);
        for (int j = 1; j <= n; ++j) {
            if (dist1[j] == INF) {
                cout << "INF";
            }
            else {
                if (i!=j)
                    cout << dist1[j]-dist[i]+dist[j];
                else
                    cout << 0<<" ";
            }
            cout << " ";
        }
        cout << '\n';
    }
}

int main() {
    ifstream f("fisier.in");

    f >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int x, y, w;
        f >> x >> y >> w;
        x++, y++;
        pair<int, int> p = make_pair(y, w);
        G[x].push_back(p);
    }

    Johnson();

    f.close();
    return 0;
}