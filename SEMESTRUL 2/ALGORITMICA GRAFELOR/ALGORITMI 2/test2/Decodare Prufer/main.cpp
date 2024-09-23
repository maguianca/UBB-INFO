#include<iostream>
#include<fstream>
#include<deque>
#include<vector>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int parinte[100001];
deque<int>coada;

int get_min(int n)
{
    int ap[100001] = {0};
	for (auto& i : coada)
		ap[i] = 1;
	for (int i = 0; i <= coada.size(); i++)
		if (ap[i] == 0)
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

int main()
{
	int n,l;
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
//se ia o coada care contine codarea prufer
//primul nr din coada devine parintele celui mai mic nr care nu apare in coada
//acest nr se adauga in coada
//se face pop primului nr din coada anterioara
//pe coada nou obtinuta se repeta procesul pana cand am executat decodarea prufer pe un nr de n cozi
//rad il are ca tata pe -1 si de aceea avem nevoie sa initializam tatii tuturor nodurilor cu -1 la inceput, deoarece
//acestea incep si ca fiind noduri izolate
