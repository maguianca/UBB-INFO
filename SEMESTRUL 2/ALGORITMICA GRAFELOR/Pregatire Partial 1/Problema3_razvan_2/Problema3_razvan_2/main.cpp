/*Se da un graf neorientat neponderat.Sa se determine daca acest graf
este aciclic.Hint: determinati daca, dupa o parcurgere in adancime raman
muchii din graf prin care nu ati trecut.Raspunsul va fi de forma �DA�
(graful este aciclic), respectiv �NU�(graful are cel putin un ciclu).*/

#include<iostream>
#include<fstream>
using namespace std;
ifstream fin("in.txt");
int viz[101], matrice[100][100], n,m;
bool cicluri(int nod,int parinte)
{
	viz[nod] = 1;
	for (int i = 1; i <= n; i++)
	{
		if (matrice[nod][i] == 1) {
			if (viz[i] == 0)
			{
				if (cicluri(i, nod))
					return true;
			}
			else
			{
				if (parinte != i)
					return true;
			}
		}
	}
	return false;

}
int main()
{
	int a, b;
	fin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		fin >> a >> b;
		matrice[a][b] = 1;
		matrice[b][a] = 1;
	}
	for (int i = 1; i <= n; i++)
	{
		viz[i] == 0;
	}
	bool raspuns = false;
	for (int i = 1; i <= n; i++)
	{
		if (viz[i] == 0)
		{
			if (cicluri(i, -1))
			{
				raspuns = true;
				break;
			}
		}
	}
	if (raspuns)
		cout << "Nu este aciclic";
	else
		cout << "Este aciclic";
	return 0;
}