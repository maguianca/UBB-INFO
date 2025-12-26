#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#define INF 1000000
using namespace std;

ifstream fin("citire.txt");

int n, sursa;
vector <int> G[100];
int matrice[100][100] = { 0 },a,b;
void citire()
{
    fin >> n;
    while (fin >> a >> b)
        matrice[a][b] = 1;
}
void BFS(int s) {
    cout << "Ordinea descoperirii nodurilor: " << s << " ";
    vector <char> color;
    vector <int> distanta;
    for (int i = 0; i <= n; i++) {
        color.push_back('a');
        distanta.push_back(INF);
    }
    color[s] = 'g';
    distanta[s] = 0;
    queue<int> Q;
    Q.push(s);
    while (!Q.empty()) {
        int nodCurent = Q.front();
        Q.pop();
        for (int x = 1; x <= n; x++) {
            if (matrice[nodCurent][x] == 1) {
                if (color[x] == 'a') {
                    color[x] = 'g';
                    cout << x << " ";
                    distanta[x] = distanta[nodCurent] + 1;
                    Q.push(x);
                }
            }
        }
        color[nodCurent] = 'n';
    }
    cout << "Distantele fata de nodul sursa " << s << " sunt" << endl;
    for (int i = 1; i <= n; i++) {
        cout << i << ": ";
        if (distanta[i] == INF) {
            cout << "-" << endl;
        }
        else {
            cout << distanta[i] << endl;
        }
    }
}

int main() {
    citire();
    cout << "Introduceti varful sursa: ";
    cin >> sursa;
    BFS(sursa);
    return 0;
}