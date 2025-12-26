#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Joc {
private:
	int id;
	int dim;
	string joc;
	string jucator;
	string stare;
public:
	Joc(int id, int dim, string joc, string jucator, string stare) :id{ id }, dim{ dim }, joc{ joc }, jucator{ jucator }, stare{ stare } {};
	int get_dim() { return dim; }
	int get_id() { return id; }
	string get_jucator() { return jucator; }
	string get_joc() { return joc; }
	string get_stare() { return stare; }
	Joc& operator=(const Joc& other) {
		id = other.id;
		dim = other.dim;
		stare = other.stare;
		return *this;
	}
	void set_jucator(const string c) {
		jucator = c;
	}
	void set_joc(const string c) {
		joc = c;
	}
	void setStare(string newStare) { stare = newStare; }
	void setTabla(string tabla) { this->joc = tabla; }
	void setJucator(string jucator) { this->jucator = jucator; }

};