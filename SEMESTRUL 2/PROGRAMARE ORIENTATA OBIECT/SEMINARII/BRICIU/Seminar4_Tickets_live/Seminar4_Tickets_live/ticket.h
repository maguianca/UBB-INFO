#pragma once
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
class Ticket {
protected:
	string showName;
	string showDate;
	double price;
public:
	Ticket(string _showName, string _showDate, double _price) : showName{ _showName }, showDate{ _showDate }, price{ _price } {};
	virtual string getTicketDetails() {
		return "Show: [" + showName + " | " + showDate + " | " + std::to_string(price) + "]";
	};
	virtual void applyEarlyBirdDiscount() = 0;
	virtual ~Ticket() {
		cout << "Ticket destructor called" << endl;
	}
};

class StandingTicket : public Ticket {
private:
	int area;
public:
	StandingTicket(string _showName, string _showDate, double _price, int _area) : Ticket(_showName, _showDate, _price), area{ _area } {};
	string getTicketDetails() {
		return Ticket::getTicketDetails() + " in area " + std::to_string(area);
	}
	void applyEarlyBirdDiscount() override{
		price = price - (0.5 * price);
	};
	~StandingTicket() {
		cout << "StandingTicket destructor called." << endl;
	}
	

};

class SeatTicket : public Ticket {
private:
	int seatNumber;
	int seatRow;
public:
	SeatTicket(string _showName, string _showDate, double _price, int _seatR, int _seatN) : Ticket(_showName, _showDate, _price), seatNumber{ _seatN }, seatRow{ _seatR } {};
	string getTicketDetails() {
		return Ticket::getTicketDetails() + " in row " + std::to_string(seatRow) +" and seat number "+std::to_string(seatNumber);
	}
	void applyEarlyBirdDiscount() override{
		price = price - (0.1 * price);
	};

	~SeatTicket() {
		cout << "SeatTicket destructor called." << endl;
	}

};