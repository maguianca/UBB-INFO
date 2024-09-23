#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
using namespace std;
int parinte[101], pruffer[101];

	ifstream fin("input.txt");
	ofstream fout("output.txt");
int frunza_min(int n)
{
	int fm = 0, i = 0;
	while (i < n) {
		if (fm == parinte[i])
		{
			fm++;
			i = -1;
		}
		i++;
	}
	return fm;

}
void codare_prufer(int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int fm = frunza_min(n);
		pruffer[i] = parinte[fm];
		parinte[fm] = fm;//nu mai iau frunza in considerare ca facand parte din arborele initial
	}
}
int main()
{
	int n;
	fin >> n;
	for (int i = 0; i < n; i++)
		fin >> parinte[i];
	codare_prufer(n);
	fout << n - 1 << endl;
	for (int i = 0; i < n - 1; i++)
		fout << pruffer[i] << ' ';
	return 0;
}
//se gaseste frunza cu eticheta minima si se adauga tatal ei in coda de codare prufer
//frunza este eliminata din arbore
//se repeta procedeul pana cand ramane doar radacina, care nu are pe cine sa mai adauge in codare
//deci, cum s edau n noduri pt care avem tati si radacina nu adauga pe nimeni in codare, avem n-1 noduri care adauga un nr in codare
