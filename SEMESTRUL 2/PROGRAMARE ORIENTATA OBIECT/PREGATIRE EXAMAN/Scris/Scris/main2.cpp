#include<iostream>
#include<vector>
#include<algorithm>
#include<assert.h>
using namespace std;
class Meniu {
private:
	int pret;
public:
	Meniu(const int pret) :pret{ pret } {}
	virtual ~Meniu() = default;
	virtual string descriere() = 0;
	virtual int getPret() {
		return pret;
	}

};
class MicDejun :public Meniu {
private:
	string denumire;
public:
	MicDejun(const string& denumire, const int pret) :denumire{ denumire }, Meniu(pret) {}
	int getPret()override {
		return Meniu::getPret();
	}
	 string descriere()override {
		return denumire;
	}
	
};
class CuRacoritoare :public Meniu {
private:
	Meniu* m;
public:
	CuRacoritoare(Meniu* m) :Meniu(m->getPret()), m{ m } {}
	~CuRacoritoare() { delete m; }
	string descriere()override {
		return m->descriere() + " cu racoritoare ";
	}
	int getPret()override {
		return m->getPret() + 4;
	}
};
class CuCafea :public Meniu {
private:
	Meniu* m;
public:
	CuCafea(Meniu* m) :Meniu(m->getPret()), m{ m } {}
	~CuCafea() { delete m; }
	string descriere()override {
		return m->descriere() + " cu cafea ";
	}
	int getPret()override {
		return m->getPret() + 5;
	}
};
vector<Meniu*>functie2()
{
	vector<Meniu*>meniu;
	meniu.push_back(new CuCafea(new CuRacoritoare(new MicDejun{ "Omleta",15 })));
	meniu.push_back(new CuCafea(new MicDejun{ "Ochiuri",10 }));
	meniu.push_back(new MicDejun{ "Omleta",15 });
	return meniu;
}
//exercitiul 4
template<typename Telem>
class Measurement {
private:
	Telem val;
public:
	Measurement(Telem val) :val{ val } {}
	Telem value()const {
		return val;
	}
	Measurement& operator+ (const Telem&e)
	{
		val += e;
		return *this;
	}
	bool operator<(const Measurement& other) {
		return val < other.value();
	}
};
std::pair<int, int> f(std::vector<int> l) {
	if (l.size() < 2) throw std::exception{};
	std::pair<int, int> rez{ -1,-1 };
	for (auto el : l) {
		if (el < rez.second) continue;
		if (rez.first < el) {
			rez.second = rez.first;
			rez.first = el;
		}
		else {
			rez.second = el;
		}
	}
	return rez;
}
void test() {
	vector<int>l1{ 1,2,3 };
	pair<int, int>x = f(l1);
	assert(x.first == 3);
	assert(x.second == 2);
	vector<int>l2{ 1,2 };
	pair<int, int>y = f(l2);
	assert(y.first == 2);
	assert(y.second == 1);
	vector<int>l3{};
	try {
		f(l3);
		assert(false);

	}
	catch (std::exception) {
		assert(true);
	}
	vector<int>l4{2};
	try {
		f(l4);
		assert(false);

	}
	catch (std::exception) {
		assert(true);
	}
}
/*
int main()
{
	//test();
	//cout << "testul a trecut"<<endl;
	vector<Meniu*>meniu = functie2();
	sort(meniu.begin(), meniu.end(), [](Meniu* o1, Meniu* o2) {
		return o1->getPret() > o2->getPret();
		});
	for (auto l : meniu)
	{
		cout << l->descriere() << " " << l->getPret() << endl;
	}


		//creaza un vector de masuratori cu valorile (10,2,3)
		std::vector<Measurement<int>> v{ 10,2,3 };
		v[2] + 3 + 2; //aduna la masuratoarea 3 valuarea 5
		std::sort(v.begin(), v.end()); //sorteaza masuratorile
		//tipareste masuratorile (in acest caz: 2,8,10)
		for (const auto& m : v) std::cout << m.value() << ",";
		return 0;
	
}*/
