#include<iostream>
#include<fstream>
#define INF 1000000
using namespace std;
ifstream fin("file.txt");
int matrice[1001][1001], n, sursa, distanta1[1001];

void Bellman_Ford(int sursa)
{
	for (int i = 1; i <= n; i++)
	{
		distanta1[i] = INF;
	}
	distanta1[sursa] = 0;
	for (int i = 1; i <= n - 1; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= n; k++) {
				if (matrice[j][k] != 0 && distanta1[j] != INF && distanta1[k] > distanta1[j] + matrice[j][k]) {
					distanta1[k] = distanta1[j] + matrice[j][k];
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
		if(i!=sursa)
			cout << "distanta de la " << sursa << " la destinatie " << i << " este " << distanta1[i] << endl;

}
int main()
{
	int a, b, c;
	fin >> sursa;
	while (fin >> a >> b >> c)
	{
		if (n < a)//determinam cate varfuri sunt ca sa stim dimensiunea matricii
			n = a;
		if (n < b)
			n = b;
		matrice[a][b] = c;
	}
	Bellman_Ford(sursa);
	return 0;
}