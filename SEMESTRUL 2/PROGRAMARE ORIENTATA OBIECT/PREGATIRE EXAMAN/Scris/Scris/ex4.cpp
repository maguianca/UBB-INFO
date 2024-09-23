#include<iostream>
#include<vector>
using namespace std;
template<typename T>
class Adder {
private:
	vector<T>numere;
public:
	Adder(const T& ex) {
		numere.push_back(ex);
	}
	Adder& operator+(const T& ex) {
		numere.push_back(ex);
		return *this;
	}
	Adder& operator=(const T& other) {
		if (other != this) {
			numere = other.numere;
		}
		return *this;
	}
	Adder& operator--() {
		if (numere.size() > 0)
			numere.pop_back();
		return*this;
	}
	Adder &operator--(const T) {
		if (numere.size() > 0)
			numere.pop_back();
		return*this;
	}
	T suma() {
		T suma = 0;
		for (const auto& l : numere) {
			suma += l;
		}
		return suma;
	}
};
void adder() {
	Adder<int> add{ 1 }; 
	add = add + 7 + 3; 
	add + 8; 
	cout << add.suma() << endl; // Afi?eazã suma obiectelor din Adder 18
	add--; // Eliminã ultimul obiect din Adder 
	cout << add.suma() << endl; // Afi?eazã suma dupã eliminare 11
	--add--; // Eliminã din nou ultimul obiect din Adder
	cout << add.suma() << endl; // Afi?eazã suma dupã eliminare 1
}
/*
int main() {
	adder();
	return 0;
}*/