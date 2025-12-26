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
ifstream fin("labirint.txt");

int n, m;
struct punct
{
    int linie;
    int coloana;
}punct_inceput, punct_sfarsit;
vector<string> labirint;
//pair<int, int> punct_inceput, punct_sfarsit;
map<pair<int, int>, pair<int, int>> parinte;
map<pair<int, int>, int> distante;
#define inf 10000000000

void citire()
{
    string linie;
    while (getline(fin, linie))
    {
        labirint.push_back(linie);
    }
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
bool valid(int i, int j)
{
    if (i < 0 || j < 0)
        return false;
    if (i >= n || j >= m)
        return false;
    if (labirint[i][j] == '1')
        return false;
    return true;
}
void parcurgere()
{
    queue<pair<int, int>> vizitare;
    vizitare.push({ punct_inceput.linie,punct_inceput.coloana});
    while (!vizitare.empty())
    {

        pair<int, int> curent = vizitare.front();
        int i = curent.first;
        int j = curent.second;

        if (valid(i - 1, j))
        {
            if (parinte[{i - 1, j}] == make_pair(0,0) && distante[make_pair(i - 1, j)] > distante[curent] + 1)
            {
                vizitare.push(make_pair(i - 1, j));
                parinte[{i - 1, j}] = curent;
                distante[{i - 1, j}] = distante[curent] + 1;

                if (i - 1 == punct_sfarsit.linie && j == punct_sfarsit.coloana)
                    return;
            }
        }
        if (valid(i + 1, j))
        {
            if (parinte[{i + 1, j}] == make_pair(0,0) && distante[make_pair(i + 1, j)] > distante[curent] + 1)
            {
                vizitare.push(make_pair(i + 1, j));
                parinte[{i + 1, j}] = curent;
                distante[{i + 1, j}] = distante[curent] + 1;

                if (i + 1 == punct_sfarsit.linie && j== punct_sfarsit.coloana)
                    return;
            }
        }
        if (valid(i, j - 1))
        {
            if (parinte[{i, j - 1}] == make_pair(0,0) && distante[make_pair(i, j - 1)] > distante[curent] + 1)
            {
                vizitare.push(make_pair(i, j - 1));
                parinte[{i, j - 1}] = curent;
                distante[{i, j - 1}] = distante[curent] + 1;

                if (i == punct_sfarsit.linie && j - 1 == punct_sfarsit.coloana)
                    return;
            }
        }
        if (valid(i, j + 1))
        {
            if (parinte[{i, j + 1}] == make_pair(0, 0) && distante[make_pair(i, j + 1)] > distante[curent] + 1)
            {
                vizitare.push(make_pair(i, j + 1));
                parinte[{i, j + 1}] = curent;
                distante[{i, j + 1}] = distante[curent] + 1;

                if (i == punct_sfarsit.linie && j + 1 == punct_sfarsit.coloana)
                    return;
            }
        }
        vizitare.pop();
    }
}
void initializare()
{
    distante[{punct_inceput.linie, punct_inceput.coloana}] = 0;
    parinte[{punct_inceput.linie, punct_inceput.coloana}] = make_pair(INF,INF);
    for (int i = 0; i < labirint.size(); i++)
    {
        for (int j = 0; j < labirint[i].length(); j++)
        {
            if (labirint[i][j] == ' ' || labirint[i][j] == 'F')
            {
                parinte[{i, j}] = make_pair(0,0);
                distante[{i, j}] = inf;
            }
        }
    }
}
void afisare()
{
    pair<int, int> curent = { punct_sfarsit.linie,punct_sfarsit.coloana };
    while (parinte[{curent.first, curent.second}] != make_pair(INF, INF))
    {
        labirint[curent.first][curent.second] = '.';
        curent = parinte[{curent.first, curent.second}];
    }
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < labirint.size(); i++, cout << endl)
    {
        for (int j = 0; j < labirint[i].length(); j++)
        {
            if (labirint[i][j] == '.')
                SetConsoleTextAttribute(hConsole, red);
            else
                SetConsoleTextAttribute(hConsole, white);
            cout << labirint[i][j];
        }
    }
}
int main()
{
    citire();
    initializare();
    parcurgere();
    afisare();
    return 0;
}
