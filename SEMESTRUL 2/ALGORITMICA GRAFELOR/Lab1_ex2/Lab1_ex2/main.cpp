#include<iostream>
#include<fstream>
#define Maxim 1000000
using namespace std;
ifstream fin("fisier.txt");
int n, ok, grad, grad_partial,matrice[105][105],matricea_distantelor[105][105],viz[105],z;
void DFS(int x)
{
	int i;
	viz[x] = 1;
	for (i = 1; i <= n; i++)
		if (matrice[x][i] == 1 && viz[i] == 0)
			DFS(i);

}
int Conex()
{
	int i;
	DFS(1);
	for (i = 1; i <= n; i++)
		if (viz[i] == 0)
			return 0;
	return 1;
}
int main()
{
	fin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			fin >> matrice[i][j];
	cout << "a.Nodurile izolate:";
	for (int i = 1; i <= n; i++)
	{
		grad = 0;
		for (int j = 1; j <= n; j++)
			grad += matrice[i][j];
		if (grad == 0)
			cout << i << " ";
	}
	//in grad este salvat deja gradul ultimului nod verificam daca gradul celorlalte noduri este egal cu s
	//setam ok pe 1 daca nu este regular,initial e 0
	for (int i = 1; i <= n - 1; i++)
	{
		grad_partial = 0;
		for (int j = 1; j <= n; j++)
			grad_partial += matrice[i][j];
		if (grad_partial != grad)
			ok = 1;
	}
	cout << endl;
	if (ok == 0)
		cout << "\nb.Graful este regular\n";
	else
		cout << "\nb.Graful nu este regular\n";
	cout << endl;
	cout << "c.Matricea distantelor:\n";
	for(int i=0;i<=n;i++)
		for (int j = 1; j <= n; j++)
		{
			if (matrice[i][j] != 1 and i != j)
				matrice[i][j] = Maxim;
		}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
					if (matrice[i][j] > matrice[i][k] + matrice[k][j])
						matrice[i][j] = matrice[i][k] + matrice[k][j];
	for (int i = 1; i <= n; i++)
	{
		cout << endl;
		for (int j = 1; j <= n; j++)
			if (matrice[i][j] == Maxim)
				cout << "inf" << " ";
			else
				cout << matrice[i][j] << " ";
				
	}
	cout << endl;
	z = Conex();
	if (z==1)
		cout << "d.Graful este conex\n";
	else
		cout << "d.Graful nu este conex\n";
	return 0;
}