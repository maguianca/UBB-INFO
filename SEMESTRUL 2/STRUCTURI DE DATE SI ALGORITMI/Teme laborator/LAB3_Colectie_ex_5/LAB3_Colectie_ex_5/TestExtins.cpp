#include "TestScurt.h"
#include "Colectie.h"
#include "IteratorColectie.h"
#include <assert.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

void testCreeaza() {
	Colectie c;
	assert(c.vida() == true);
	assert(c.dim() == 0);

	for (int i = -10; i < 30; i++) {
		assert(c.sterge(i) == false);
	}
	for (int i = -10; i < 30; i++) {
		assert(c.cauta(i) == false);
	}
	for (int i = -10; i < 30; i++) {
		assert(c.nrAparitii(i) == 0);
	}
	IteratorColectie ic = c.iterator();
	assert(ic.valid() == false);
}

void testIterator(Colectie& col) {
	IteratorColectie ic = col.iterator();
	TElem e1;
	TElem e2;
	if (ic.valid()) {
		e1 = ic.element();
		ic.urmator();
	}
	while (ic.valid()) {
		e2 = e1;
		e1 = ic.element();
		ic.urmator();
		assert(col.cauta(e1) == true);
		assert(col.cauta(e2) == true);
		assert(col.nrAparitii(e1) > 0);
		assert(col.nrAparitii(e2) > 0);
		assert(rel(e2, e1));
	}
}

void testAdauga() {
	Colectie c;
	for (int i = 0; i < 100; i++) {
		c.adauga(i);
	}
	assert(c.dim() == 100);
	assert(c.vida() == false);
	testIterator(c);

	for (int i = 200; i >= -200; i--) {
		c.adauga(i);
	}
	assert(c.dim() == 501);
	testIterator(c);

	for (int i = -300; i < 300; i++) {
		bool exista = c.cauta(i);
		int nrA = c.nrAparitii(i);

		if (i < -200 || i > 200) {
			assert(exista == false);
			assert(nrA == 0);
		}
		else if (i >= -200 && i < 0) {
			assert(exista == true);
			assert(nrA == 1);
		}
		else if (i >= 0 && i < 100) {
			assert(exista == true);
			assert(nrA == 2);
		}
		else if (i >= 100 && i <= 200) {
			assert(exista == true);
			assert(nrA == 1);
		}
	}

	for (int i = 0; i < 100; i++) {
		c.adauga(0);
	}
	assert(c.nrAparitii(0) == 102);
	testIterator(c);

	Colectie c2;
	for (int i = 0; i < 300; i = i + 2) {
		c2.adauga(i);
		c2.adauga(2 * i);
		c2.adauga(-2 * i);
	}
	assert(c2.dim() == 450);
	testIterator(c2);
}

void testSterge() {
	Colectie c;
	for (int i = -100; i < 100; i++) {
		assert(c.sterge(i) == false);
		assert(c.cauta(i) == false);
		assert(c.nrAparitii(i) == 0);
	}
	assert(c.vida() == true);

	for (int i = -100; i < 100; i++) {
		c.adauga(i);
	}
	assert(c.dim() == 200);
	for (int i = -100; i < 100; i = i + 2) {
		assert(c.sterge(i) == true);
	}
	assert(c.dim() == 100);
	for (int i = -100; i < 100; i++) {
		if (i % 2 == 0) {
			assert(c.nrAparitii(i) == 0);
			assert(c.cauta(i) == false);
			assert(c.sterge(i) == false);
		}
		else {
			assert(c.nrAparitii(i) == 1);
			assert(c.cauta(i) == true);
		}
		c.adauga(i);
		c.adauga(i);
		c.adauga(i);
	}
	assert(c.dim() == 700);
	for (int i = -200; i < 200; i++) {
		if (i < -100 || i >= 100) {
			assert(c.cauta(i) == false);
			assert(c.nrAparitii(i) == 0);
			assert(c.sterge(i) == false);
		}
		else if (i % 2 == 0) {
			assert(c.cauta(i) == true);
			assert(c.nrAparitii(i) == 3);
			assert(c.sterge(i) == true);
			assert(c.sterge(i) == true);
			assert(c.sterge(i) == true);
			assert(c.sterge(i) == false);
		}
		else {
			assert(c.cauta(i) == true);
			assert(c.nrAparitii(i) == 4);
			assert(c.sterge(i) == true);
			assert(c.sterge(i) == true);
			assert(c.sterge(i) == true);
			assert(c.sterge(i) == true);
			assert(c.sterge(i) == false);
		}
	}
	Colectie c2;
	for (int i = 300; i >= -500; i--) {
		c2.adauga(i);
		c2.adauga(i * 2);
		c2.adauga(-2 * i);
	}
	for (int i = -100; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			c2.sterge(i);
		}
	}
	for (int i = -100; i < 100; i++) {
		assert(c2.nrAparitii(i) == 0);
		assert(c2.cauta(i) == false);
	}
}

void testQuantity() {
	Colectie c;
	for (int j = 0; j < 10; j++) {
		c.adauga(0);
		for (int i = 1; i < 3000; i++) {
			c.adauga(i);
			c.adauga(-i);
		}
		c.adauga(-3000);
	}
	int count = 60000;
	assert(c.dim() == 60000);
	for (int i = 0; i < 10000; i++) {
		TElem nr = rand() % 8000 - 4000;
		if (c.sterge(nr) == true) {
			count--;
		}
		assert(c.dim() == count);
	}
	assert(c.dim() == count);
}
void testFiltreaza()
{
	Colectie c;
	c.adauga(5);
	c.adauga(6);
	c.adauga(0);
	c.adauga(5);
	c.adauga(12);
	c.adauga(10);
	c.adauga(8);
	c.adauga(11);

	assert(c.dim() == 8);
	assert(c.nrAparitii(11) == 1);
	assert(c.nrAparitii(12) == 1);
	c.filtreaza();
	assert(c.dim() == 6);
	assert(c.nrAparitii(11) == 0);
	assert(c.nrAparitii(12) == 0);
	Colectie d;
	d.adauga(11);
	d.adauga(18);
	d.adauga(20);
	d.adauga(21);
	d.adauga(22);
	assert(d.dim() == 5);
	d.filtreaza();
	assert(d.dim() == 0);
	Colectie e;
	e.adauga(12);
	e.adauga(12);
	e.adauga(12);
	assert(e.dim() == 3);
	e.filtreaza();
	assert(e.dim() == 0);
	Colectie f;
	f.adauga(12);
	f.adauga(9);
	f.adauga(10);
	assert(f.dim() == 3);
	f.filtreaza();
	assert(f.dim() == 2);

}


void testAllExtins() {
	testCreeaza();
	testAdauga();
	testSterge();
	testQuantity();
	testFiltreaza();
	cout << "Testul extins a trecut\n";
}
