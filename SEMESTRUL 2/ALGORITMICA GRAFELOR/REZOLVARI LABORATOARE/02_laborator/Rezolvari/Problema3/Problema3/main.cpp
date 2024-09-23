﻿/*3. Să se scrie un program care găsește o soluție pentru unul din următoarele labirinturi: labirint_1.txt, 
labirint_2.txt, labirint_cuvinte.txt. Pentru labirintul 1 si 2 punctul de pornire este indicat de litera S și punctul 
de oprire este indicat de litera F, spre deosebire de labirintul 1 și 2, labirintul 3 nu are o soluție unică.*/
#include <fstream>
#include <queue>
#include <iostream>
#include <windows.h>
#define red 12
#define white 15
using namespace std;

ifstream f("labirint_1.txt");

int labirint[1000][1000];
bool ok = false;
struct punct
{
    int linie, coloana;
}start,finish;
int n, m;
pair<int, int> precedent[1000][1000];
queue<pair<int, int>> Q;
int di[] = { -1, 1, 0, 0 }, dj[] = { 0, 0, -1, 1 };

void citire() {
    char s[1000];
    while (f.getline(s, 1000)) {
        m = strlen(s);
        for (int i = 0; i < m; ++i)
            if (s[i] == '1')
                labirint[n][i] = 1;
            else if (s[i] == 'S') {
                start.linie = n;
                start.coloana = i;
                labirint[n][i] = 1;
            }
            else if (s[i] == 'F') {
                finish.linie = n;
                finish.coloana = i;
                labirint[n][i] = 1;
            }
            else
                labirint[n][i] = 0;
        ++n;
    }
}

void bordare() {
    for (int i = 0; i < n; ++i)
        labirint[i][0] = labirint[i][m - 1] = 1;
    for (int i = 0; i < m; ++i)
        labirint[0][i] = labirint[n - 1][i] = 1;
}

void lee() {
    precedent[start.linie][start.coloana] = { -1, -1 };
    Q.push({ start.linie, start.coloana });
    while (!Q.empty() && !ok) {
        int i = Q.front().first;
        int j = Q.front().second;
        Q.pop();
        for (int k = 0; k < 4; ++k) {
            int i_nou = i + di[k], j_nou = j + dj[k];
            if (0 <= i_nou && i_nou < n && 0 <= j_nou && j_nou < m)
                if (labirint[i_nou][j_nou] != 1 && !precedent[i_nou][j_nou].first && 
                    !precedent[i_nou][j_nou].second || i_nou == finish.linie && j_nou == finish.coloana) {
                    precedent[i_nou][j_nou] = { i, j };
                    Q.push({ i_nou, j_nou });
                    if (i_nou == finish.linie && j_nou == finish.coloana) {

                        ok = true;
                        break;
                    }
                }
        }
    }
}

void afisare() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int i = finish.linie, j = finish.coloana;
    while (i != -1 && j != -1) {
        labirint[i][j] = 2;
        int i_nou = precedent[i][j].first, j_nou = precedent[i][j].second;
        i = i_nou;
        j = j_nou;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (labirint[i][j] == 1) {
                SetConsoleTextAttribute(hConsole, white);
                cout << "1";
            }
            else if (labirint[i][j] == 2) {
                SetConsoleTextAttribute(hConsole, red);
                cout << "*";
            }
            else
                cout << " ";
        }
        cout << "\n";
    }
}

int main() {
    citire();
    bordare();
    lee();
    afisare();
    return 0;
}