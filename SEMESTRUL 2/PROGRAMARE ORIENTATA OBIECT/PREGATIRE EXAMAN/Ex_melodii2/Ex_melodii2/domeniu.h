#pragma once
#include<iostream>
using namespace std;
class Melodie {
private:
	int id;
	string titlu;
	string artist;
	string gen;
public:
	Melodie(const int id, const string titlu, const string artist, const string gen) :id{ id }, titlu{ titlu }, artist{ artist }, gen{ gen } {}
	//constructor Melodie id-int string-titlu,artist,gen
	int get_id()const { return id; }
	//getter returneaza id int
	string get_titlu()const { return titlu; }
	//getter returneaza titlu string
	string get_artist()const { return artist; }
	//getter returneaza artist string
	string get_gen()const { return gen; }
	//getter returneaza gen string
	
};