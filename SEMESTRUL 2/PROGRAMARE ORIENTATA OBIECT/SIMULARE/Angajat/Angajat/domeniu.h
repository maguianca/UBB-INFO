#pragma once
#include<iostream>
using namespace std;
class Persoana {
private:
	string nume;
	string job;
	string status;
	int id;
public:
	Persoana(string nume, string job, string status, int id) :nume{ nume }, job{ job }, status{ status }, id{ id } {};
	Persoana() = default;
	int get_id() {
		return id;
	}
	string get_job() {
		return job;
	}
	string get_nume() {
		return nume;
	}
	string get_status() {
		return status;
	}
	bool operator==(Persoana& r) {
		return id == r.get_id();
	}
	bool operator!=(Persoana& r) {
		return !(r == *this);
	}
	Persoana& operator= (const Persoana & p){
		nume = p.nume;
		job = p.job;
		status = p.status;
		id = p.id;
		return(*this);
	}

};