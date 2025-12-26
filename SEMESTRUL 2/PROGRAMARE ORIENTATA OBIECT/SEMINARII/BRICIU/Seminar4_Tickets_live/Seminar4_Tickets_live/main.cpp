#define _CRT_DBG_MALLOC
#include "customer.h"
#include <iostream>
#include <crtdbg.h>
using std::cout; 
using std::endl;

void run() {
	cout << "Standing ticket info:" << endl;

	//it would be better to use unique_ptr
	StandingTicket* t1 = new StandingTicket{ "Artist", "Show name 1", 20, 10 };
	cout << t1->getTicketDetails() << endl;
	t1->applyEarlyBirdDiscount();
	cout << t1->getTicketDetails() << endl;

	cout << "Seat ticket info:" << endl;

	SeatTicket* t2 = new SeatTicket{ "Artist", "Show name 1", 20, 1, 13 };
	cout << t2->getTicketDetails() << endl;
	t2->applyEarlyBirdDiscount();
	cout << t2->getTicketDetails() << endl;

	Customer c{ "a", "a@something.com" };
	c.purchaseTicket(t1);
	c.purchaseTicket(t2);

	cout << "Customer ticket information:" << endl;
	for (const auto& ticket : c.getAllTickets())
	{

		cout << "Before discount: " << ticket->getTicketDetails() << endl;
		ticket->applyEarlyBirdDiscount();
		cout << "After discount: " << ticket->getTicketDetails() << endl;
	}
}
int main() {
	
	run();
	_CrtDumpMemoryLeaks();

}