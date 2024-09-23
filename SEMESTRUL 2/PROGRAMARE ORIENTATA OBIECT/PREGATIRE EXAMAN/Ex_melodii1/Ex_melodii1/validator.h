#pragma once
#include"repo.h"
#include<iostream>
class ValException {
private:
	string msg;
public:ValException(string msg) :msg{ msg } {}
	  string get_msg() { return msg; };
};
class Validator {
public:
	void valideaza(const Melodie& m);
};