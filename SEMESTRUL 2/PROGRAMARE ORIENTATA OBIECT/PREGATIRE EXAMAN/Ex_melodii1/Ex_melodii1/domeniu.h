#pragma once
#include<iostream>
using namespace std;
class Melodie {
private:
	int id;
	string titlu;
	string artist;
	int rank;
public:
	Melodie(const int id, const string titlu, const string artist, const int rank) :id{ id }, titlu{ titlu }, artist{ artist }, rank{ rank } {}
	//constrctor primeste id-int si titlu,artist-string rank int
	int get_id()const { return  id; }
	//metoda getter returneaza id
	string get_titlu()const { return titlu; }
	//metoda getter returneaza string titlu
	string get_artist()const { return artist; }
	//metoda getter returneaza string titlu
	int get_rank()const { return rank; }
	//metoda getter returneaza rank int
	Melodie& operator=(const Melodie& other) {
		if (this != &other)
		{
			id = other.id;
			titlu = other.titlu;
			artist = other.artist;
			rank = other.rank;
		}
		return *this;
	}
};