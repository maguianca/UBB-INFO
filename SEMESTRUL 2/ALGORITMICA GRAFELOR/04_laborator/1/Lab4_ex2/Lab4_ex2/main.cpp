#include<iostream>
#include<fstream>
#include<deque>
#include<vector>
using namespace std;
int parinte[100001];
deque<int>coada;
int get_min(int n)
{
	int nr = coada.size();
    int frecventa[100001] = {0};
	for (auto& i : coada)
		frecventa[i] = 1;
	for (int i = 0; i <= coada.size(); i++)
		if (frecventa[i] == 0)
			return i;
	return -1;
}
void decodare(int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int y = get_min(n);
		int x = coada.front();
		coada.pop_front();
		parinte[y] = x;
		coada.push_back(y);
	}
}
int main(int argc,char** argv)
{
	int n,l;
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	fin >> l;
	n = l + 1;
	for (int i = 0; i < l; i++)
	{
		int x;
		fin >> x;
		coada.push_back(x);
	}
	for (int i = 0; i < n; i++)
		parinte[i] = -1;
	decodare(n);
	fout << n << endl;
	for (int i = 0; i < n; i++)
		fout << parinte[i] << " ";

}