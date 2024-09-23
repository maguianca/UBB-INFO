#pragma once
#include"service.h"
class Observer {
public:
	virtual void update() = 0;
};
class Observable{
private:
	vector<Observer*>observeri;
public:
	void addObserver(Observer* obs) {
		observeri.push_back(obs);
	}
	void removeObserver(Observer* obs) {
		observeri.erase(remove(observeri.begin(), observeri.end(), obs), observeri.end());
	}
	void notify() {
		for (auto& l : observeri) {
			l->update();
		}
	}
};