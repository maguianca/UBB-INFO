#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class Channel {
public:
	Channel() = default;
	virtual~Channel() = default;
	virtual void send(string msg) = 0;

};
class Telefon :public Channel {
private:
	int nrTel;
public:
	Telefon(const int nrTel) :nrTel{ nrTel } {}
	virtual void send(string msg)override {
		int x = rand()%3;
		if (x != 0) {
			cout << "dail: " << nrTel <<endl;
		}
		else
			throw std::exception("nu se poate");
	}
};
class SMS :public Telefon {
public:
	SMS(const int nrtel) :Telefon(nrtel) {}
	void send(string msg)override {
		try {
			Telefon::send(msg);
			cout << "sending SMS" << endl;
		}
		catch (std::exception) {
			throw std::exception("nu se poate");
		}
	}
};
class Fax :public Telefon {
public:
	Fax(const int nrtel) :Telefon(nrtel) {}
	void send(string msg)override {
		try {
			Telefon::send(msg);
			cout << "sending Fax" << endl;
		}
		catch (std::exception) {
			throw std::exception("nu se poate");
		}
	}
};
class Contact {
private:
	Channel* c1;
	Channel* c2;
	Channel* c3;
public:
	Contact(Channel* c1, Channel* c2, Channel* c3) :c1{ c1 }, c2{ c2 }, c3{ c3 } {}
	void sendAlarm(string msg) {
		int k = 0;
		while (true) {
			try {
				if (k % 3 == 0)c1->send(msg);
				if (k % 3 == 1)c2->send(msg);
				if (k % 3 == 2)c3->send(msg);
				break;
			}
			catch (std::exception) {
				k = (k + 1) % 3;
			}
		}
	}
	~Contact() {
		if (c1 != nullptr)
			delete c1;
		if (c2 != nullptr)
			delete c2;
		if (c3 != nullptr)
			delete c3;
	}
};
class Failover :public Channel {
private:
	Channel* c1;
	Channel* c2;
public:
	Failover(Channel* c1, Channel* c2) :c1{ c1 }, c2{ c2 }{}
	void send(string msg)override {
		try {
			c1->send(msg);
		}
		catch (std::exception) {
			try {
				c2->send(msg);
			}
			catch(std::exception){
				cout << "esuat"<<endl;
			}
		}
	}
	~Failover() {
		if (c1 != nullptr)
			delete c1;
		if (c2 != nullptr)
			delete c2;
	}

};
Contact functie2() {
	Contact ob{ new Telefon{148},
				new Failover(new Fax{123},new SMS{234}),
				new Failover(new Telefon{987},new Failover(new Fax{346},new SMS{498}))
	};
	return ob;
}
//EXERCITIU 4
template<typename T>
class Expresie {
private:
	vector<pair<T,int>>op;
public:
	Expresie(const T& x) {
		op.push_back(make_pair(x, 1));
	};
	Expresie& operator=(const T& other) {
		if (this != other) {
			op = other.op;
		}
		return *this;
	}
	Expresie& operator+(const T& ex) {
		op.push_back(make_pair(ex, 1));
		return *this;
	}
	Expresie& operator-(const T& ex) {
		op.push_back(make_pair(ex, -1));
		return *this;
	}
	T valoare() {
		T sum = 0;
		for (const auto& l : op)
			sum += l.first * l.second;
		return sum;
	}
	Expresie &undo() {
		if(op.size()>1)
			op.pop_back();
		return *this;
	}
};
void operatii() {
	Expresie<int> exp{ 3 };//construim o expresie,pornim cu operandul 3
	//se extinde expresia in dreapta cu operator (+ sau -) si operand
	exp = exp + 7 + 3;
	exp = exp - 8;
	//tipareste valoarea expresiei (in acest caz:5 rezultat din 3+7+3-8)
	cout << exp.valoare() << "\n";
	exp.undo(); //reface ultima operatie efectuata
	//tipareste valoarea expresiei (in acest caz:13 rezultat din 3+7+3)
	cout << exp.valoare() << "\n";
	exp.undo().undo();
	cout << exp.valoare() << "\n"; //tipareste valoarea expresiei (in acest caz:3)
}
/*
int main() {
	
	Contact c = functie2();
	c.sendAlarm("Salut!");
	c.sendAlarm("Ce faci?");
	c.sendAlarm("Esti bine?");
	return 0;
}

int main() {
	operatii();
}*/