#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
using namespace std;
int parinte[101], pruffer[101];
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
		parinte[fm] = fm;
	}
}
int main(int argc, char**argv)
{
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
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