/*3. Să se scrie un program care găsește o soluție pentru unul din
 * următoarele labirinturi: labirint_1.txt, labirint_2.txt,
 * labirint_cuvinte.txt. Pentru labirintul 1 si 2 punctul de pornire
 * este indicat de litera S și punctul de oprire este indicat de litera
 * F, spre deosebire de labirintul 1 și 2, labirintul 3 nu are o soluție
 * unică.*/
#include<fstream>
#include<vector>
#include<queue>
#include<iostream>
#include<string>
#include<map>
#include <windows.h>
#define INF 20000000
#define red 12
#define white 15

using namespace std;
ifstream fin("labirint_1.txt");

map<pair<int, int>, pair<int, int>> p;
map<pair<int, int>, int> dist;
int n, m;
struct punct
{
    int linie;
    int coloana;
}punct_inceput, punct_sfarsit;
vector<string> labirint;
queue<pair<int, int>> Q;

void citeste_fisier();
int validare();
int not_margine();
void algoritm();
void initializare();
void afisare();
int main()
{
    citeste_fisier();
    initializare();
    algoritm();
    afisare();
    return 0;
}
void citeste_fisier()
{
    string input;
    while (getline(fin, input))
        labirint.push_back(input);
    for (int i = 0; i < labirint.size(); i++)
    {
        for (int j = 0; j < labirint[i].length(); j++)
        {
            if (labirint[i][j] == 'S')
            {
                punct_inceput.linie = i;
                punct_inceput.coloana = j;
            }
            if (labirint[i][j] == 'F')
            {
                punct_sfarsit.linie = i;
                punct_sfarsit.coloana = j;
            }
        }
    }
    n = labirint.size();
    m = labirint[0].length();
}
int validare(int i, int j)
{
    if (i < 0 || j < 0|| i >= n || j >= m)
        return 0;
    return 1;
}
int not_margine(int i, int j)
{
    if (labirint[i][j] == '1')
        return 0;
    return 1;
}

void algoritm()
{
    Q.push({ punct_inceput.linie,punct_inceput.coloana });
    while (!Q.empty())
    {

        pair<int, int> obiect = Q.front();
        int linie = obiect.first;
        int coloana = obiect.second;


        if (validare(linie - 1, coloana) && not_margine(linie - 1, coloana))
        {
            if (p[{linie - 1, coloana}] == make_pair(0, 0) && dist[make_pair(linie - 1, coloana)] > dist[obiect] + 1)
            {
                Q.push(make_pair(linie - 1, coloana));
                p[{linie - 1, coloana}] = obiect;
                dist[{linie- 1, coloana}] = dist[obiect] + 1;

                if (linie - 1 == punct_sfarsit.linie && coloana == punct_sfarsit.coloana)
                    return;
            }
        }
        if (validare(linie + 1, coloana) && not_margine(linie + 1,coloana))
        {
            if (p[{linie + 1, coloana}] == make_pair(0, 0) && dist[make_pair(linie + 1, coloana)] > dist[obiect] + 1)
            {
                Q.push(make_pair(linie + 1, coloana));
                p[{linie + 1, coloana}] = obiect;
                dist[{linie + 1, coloana}] = dist[obiect] + 1;

                if (linie + 1 == punct_sfarsit.linie && coloana == punct_sfarsit.coloana)
                    return;
            }
        }
        if (validare(linie, coloana - 1)&& not_margine(linie,coloana-1))
        {
            if (p[{linie, coloana - 1}] == make_pair(0, 0) && dist[make_pair(linie, coloana - 1)] > dist[obiect] + 1)
            {
                Q.push(make_pair(linie, coloana - 1));
                p[{linie, coloana - 1}] = obiect;
                dist[{linie, coloana - 1}] = dist[obiect] + 1;

                if (linie == punct_sfarsit.linie && coloana - 1 == punct_sfarsit.coloana)
                    return;
            }
        }
        if (validare(linie, coloana + 1)&& not_margine(linie,coloana+1))
        {
            if (p[{linie, coloana + 1}] == make_pair(0, 0) && dist[make_pair(linie, coloana + 1)] > dist[obiect] + 1)
            {
                Q.push(make_pair(linie, coloana + 1));
                p[{linie, coloana + 1}] = obiect;
                dist[{linie, coloana + 1}] = dist[obiect] + 1;

                if (linie == punct_sfarsit.linie && coloana + 1 == punct_sfarsit.coloana)
                    return;
            }
        }
        Q.pop();
    }
}
void initializare()
{
    dist[{punct_inceput.linie, punct_inceput.coloana}] = 0;
    p[{punct_inceput.linie, punct_inceput.coloana}] = make_pair(INF, INF);
    for (int i = 0; i < labirint.size(); i++)
    {
        for (int j = 0; j < labirint[i].length(); j++)
        {
            if (labirint[i][j] == ' ' || labirint[i][j] == 'F')
            {
                p[{i, j}] = make_pair(0, 0);
                dist[{i, j}] = INF;
            }
        }
    }
}
void afisare()
{
    pair<int, int> obiect = { punct_sfarsit.linie,punct_sfarsit.coloana };
    while (p[{obiect.first, obiect.second}] != make_pair(INF, INF))
    {
        obiect = p[{obiect.first, obiect.second}];
        labirint[obiect.first][obiect.second] = '_';
    }
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < labirint.size(); i++, cout << endl)
    {
        for (int j = 0; j < labirint[i].length(); j++)
        {
            if (labirint[i][j] == '_')
                SetConsoleTextAttribute(hConsole, red);
            else
                SetConsoleTextAttribute(hConsole, white);
            cout << labirint[i][j];
        }
    }
}
