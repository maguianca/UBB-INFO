#pragma once
#include<QWidget>
#include<QPainter>
#include"CosOferte.h"
using namespace std;
class HistogramGUI :public QWidget, public Observer {
private:
	CosOferte& cos;
public:
	HistogramGUI(CosOferte& cos) :cos{ cos } {
		cos.addObserver(this);
	}
	void update()override {
		repaint();
	}
	void paintEvent(QPaintEvent* ev)override {
		QPainter p{ this };
		int i = 0;
		srand(time(NULL));
		for (const auto& u : cos.getAllCos()) {
			i++;
			int x = rand()%300;
			int y = rand() % 300;
			p.drawRect(x, y, 20, u.get_pret() );
			//p.drawImage(x, y, QImage("gold.jpeg"));
		}
	}
	~HistogramGUI() {
		cos.removeObserver(this);
	}

};