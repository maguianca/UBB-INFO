#include<iostream>
#include<fstream>
using namespace std;
ifstream fin("in.txt");
int main()
{
	int matricea_i[105][105]={0}, matricea_a[105][105]={0}, n, lista_adiacenta[105][105] = {0}, x, y,cnt=0,muchii;
	int lista_adiacenta_2[105][105] = { 0 }, multime_muchii[105][3] = { 0 }, matricea_adiacenta[105][105] = { 0 };
	fin >> n;
	while (fin >> x >> y)
	{
		matricea_a[x][y] = 1;
		matricea_a[y][x] = 1;
	}
	cout << "Matricea de adiacenta este:\n";
	for (int i = 1; i <= n; i++)
	{
		cout << endl;
		for (int j = 1; j <= n; j++)
			cout << matricea_a[i][j] << " ";
	}
	cout << endl;
	for (int i = 1; i <= n; i++)
	{
		cnt = 0;
		for (int j = 1; j <= n; j++) {
			if (matricea_a[i][j] == 1)
				lista_adiacenta[i][++cnt] = j;
		}
	}
	cout << "Lista de adiacenta este:\n";
	for (int i = 1; i <= n; i++)
	{
		cout << endl;
		cout <<i<< ":";
		for (int j = 1; j <= n; j++)
		{
              if (lista_adiacenta[i][j])
				cout << lista_adiacenta[i][j] << " ";
		}
	}
	cout << endl;
	cout << "Matricea de incidenta este:\n";
	cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			x = lista_adiacenta[i][j];
			if (lista_adiacenta[i][j] != 0 and i < x) {
				++cnt;
				matricea_i[i][cnt] = 1;
				matricea_i[x][cnt] = 1;
				multime_muchii[cnt][1] = i;
				multime_muchii[cnt][2] = x;
				//am salvat muchiile intr-o matrice pentru a le putea accesa mai tarziu 
				//la creearea listei de adiacenta
			}
		}

	}
	muchii = cnt;
	for (int i = 1; i <= n; i++)
	{
		cout << endl;
		for (int j = 1; j <=muchii; j++)
		{
				cout <<matricea_i[i][j] << " ";
		}
	}
	cout << endl;
	cout << "Multimea muchiilor aferente coloanelor :\n";
	for (int i = 1; i <= muchii; i++)
		cout << "c" << i << ": " << multime_muchii[i][1] << " " << multime_muchii[i][2] << endl;
	cout << endl;
	cout << "Lista de adiacenta:\n";
	for (int i = 1; i <= n; i++) {
		cnt = 0;
		for (int j = 1; j <= muchii; j++)
		{
			if (matricea_i[i][j] == 1)
			{
				cnt++;
				if (multime_muchii[j][1] == i)
					lista_adiacenta_2[i][cnt] = multime_muchii[j][2];
				else
					lista_adiacenta_2[i][cnt] = multime_muchii[j][1];
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		cout << endl;
		cout << i << ":";
		for (int j = 1; j <= n; j++)
		{
			if (lista_adiacenta_2[i][j])
				cout << lista_adiacenta_2[i][j] << " ";
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			x = lista_adiacenta[i][j];
			if (lista_adiacenta[i][j] != 0 and i < x)
			{
				matricea_adiacenta[i][x] = 1;
				matricea_adiacenta[x][i] = 1;
			}

				
		}
	}
	cout << endl;
	cout << "Matricea de adiacenta este:\n";
	for (int i = 1; i <= n; i++)
	{
		cout << endl;
		for (int j = 1; j <= n; j++)
			cout << matricea_adiacenta[i][j] << " ";
	}
	cout << endl;
	cout << "Lista initiala este:\n";
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			if (matricea_adiacenta[i][j] == 1 and i < j)
				cout << i << " " << j << endl;

	}
	return 0;
}