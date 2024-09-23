#include<iostream>
#include<vector>
using namespace std;
template<typename T>
class Carnet {
private:
	vector<pair<string, T>>note;
public:
	Carnet() = default;
	Carnet& add(const string& n, const int x) {
		note.push_back(make_pair(n, x));
		return *this;
	}
	Carnet& removeLast()
	{
		if (note.size() > 0)
			note.pop_back();
		return *this;
	}
	T& operator[](const string& m) {
		for (auto& l : note) {
			if (l.first == m)
				return l.second;
		}
		throw exception();
	}
};

int main() {
	Carnet<int>cat;
	cat.add("SDA", 9);
	cat.add("OOP", 7).add("FP",10);
	cout << cat["OOP"];
	cat.removeLast().removeLast();
	try {
		cout << cat["OOP"];
	}
	catch (std::exception& ex) {
		cout << "nu exista nota";
	}
}