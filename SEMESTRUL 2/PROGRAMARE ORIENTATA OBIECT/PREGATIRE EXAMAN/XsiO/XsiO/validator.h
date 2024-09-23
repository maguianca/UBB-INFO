#pragma once
#include"rep.h"
#include<iostream>
using namespace std;
class ValException {
private:
	string msg;
public:
	ValException(const string& msg) :msg{ msg } {};
	string get_mesaj() { return msg; }
};
class Validator {
public:
	void valideaza(Joc& joc);
};