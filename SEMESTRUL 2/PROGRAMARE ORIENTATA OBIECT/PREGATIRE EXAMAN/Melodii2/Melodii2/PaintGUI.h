#pragma once
/*#include<QWidget>
#include<QPainter>
#include"observer.h"
#include"service.h"
using namespace std;
class HistogramGUI :public QWidget, public Observer {
private:
	Service& service;
public:
	HistogramGUI(Service& service) :service{ service } {
		service.addObserver(this);
	}
	void update()override {
		repaint();
	}
	void paintEvent(QPaintEvent* ev)override {
		QPainter p{ this };
		int i = 0;
	}
	~HistogramGUI() {
		service.removeObserver(this);
	}
};*/
