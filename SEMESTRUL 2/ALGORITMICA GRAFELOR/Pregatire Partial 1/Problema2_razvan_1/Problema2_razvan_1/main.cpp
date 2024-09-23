#include<iostream>
#include<fstream>
using namespace std;
ifstream fin("in.txt");
int viz[101], n, nr_varf,matrice[101][101];
void dfs(int k)
{
	viz[k] = 1;
	cout << k << " ";
	for (int i = 1; i <= nr_varf; i++) // determinam vecinii nevizitati ai lui x
		if (matrice[k][i] == 1 && viz[i] == 0)
		{
			dfs(i); // continuam parcurgerea cu vecinul curent i
		}
}
int main()
{
	int a, b,cnt;
	fin >> nr_varf >> n;
	for (int i = 1; i <= n; i++)
	{
		fin >> a >> b;
		matrice[a][b] = 1;
		//matrice[b][a] = 1;
	}
	cnt = 0;
	//cnt = 1;
	//cout << "grup:" << cnt << ":";
	for (int i = 1; i <= n; i++)
			if (viz[i] == 0)
			{
				cout << endl;
				cnt++;
				cout << "grup "<<cnt<<":";
				dfs(i);
			}
	return 0;
}