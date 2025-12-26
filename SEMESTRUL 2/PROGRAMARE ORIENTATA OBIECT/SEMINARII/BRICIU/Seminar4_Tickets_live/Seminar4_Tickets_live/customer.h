#pragma once
#include "ticket.h"
#include <vector>
using std::vector;
class Customer {
private:
	string name;
	string email;
	vector<Ticket*> tickets;
public:
	Customer(string _n, string _e) : name{ _n }, email{ _e } {};
	void purchaseTicket(Ticket* t) {
		tickets.push_back(t);
	}
	const vector<Ticket*>& getAllTickets() {
		return this->tickets;
	}
	~Customer() {
		for (Ticket* ticket : tickets)
			delete ticket;
	}
};