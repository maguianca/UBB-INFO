#include <assert.h>
#include "Matrice.h"
#include "TestExtins.h"
#include <iostream>
#include <exception>

using namespace std;


void testCreeaza() {
	Matrice m(10, 10);
	assert(m.nrLinii() == 10);
	assert(m.nrColoane() == 10);
	for (int i = 0; i < m.nrLinii(); i++)
		for (int j = 0; j < m.nrColoane(); j++)
			assert(m.element(i, j) == NULL_TELEMENT);
}

void testAdauga() {
	Matrice m(10, 10);
	for (int j = 0; j < m.nrColoane(); j++)
		m.modifica(4, j, 3);
	for (int i = 0; i < m.nrLinii(); i++)
		for (int j = 0; j < m.nrColoane(); j++)
			if (i == 4)
				assert(m.element(i, j) == 3);
			else
				assert(m.element(i, j) == NULL_TELEMENT);
}

void testQuantity() {//scopul e sa adaugam multe date
	Matrice m(300, 300);
	for (int i = m.nrLinii() / 2; i < m.nrLinii(); i++) {
		for (int j = 0; j < m.nrColoane() / 2; j++)
		{
			int v1 = j;
			int v2 = m.nrColoane() - v1 - 1;
			if (i % 2 == 0 && v1 % 2 == 0)
				m.modifica(i, v1, i * v1);
			else
				if (v1 % 3 == 0)
					m.modifica(i, v1, i + v1);
			if (i % 2 == 0 && v2 % 2 == 0)
				m.modifica(i, v2, i * v2);
			else
				if (v2 % 3 == 0)
					m.modifica(i, v2, i + v2);
		}
	}
	for (int i = 0; i <= m.nrLinii() / 2; i++) {
		for (int j = 0; j < m.nrColoane() / 2; j++)
		{
			int v1 = j;
			int v2 = m.nrColoane() - v1 - 1;
			if (i % 2 == 0 && v1 % 2 == 0)
				m.modifica(i, v1, i * v1);
			else
				if (v1 % 3 == 0)
					m.modifica(i, v1, i + v1);
			if (i % 2 == 0 && v2 % 2 == 0)
				m.modifica(i, v2, i * v2);
			else
				if (v2 % 3 == 0)
					m.modifica(i, v2, i + v2);
		}
	}
	for (int i = 0; i < m.nrLinii(); i++)
		for (int j = 0; j < m.nrColoane(); j++)
			if (i % 2 == 0 && j % 2 == 0)
				assert(m.element(i, j) == i * j);
			else
				if (j % 3 == 0)
					assert(m.element(i, j) == i + j);
				else assert(m.element(i, j) == 0);
}

void testExceptii() {
	Matrice m(10, 10);
	try {
		m.element(-1, -1);
	}
	catch (exception&) {
		assert(true); //ar trebui sa arunce exceptie
	}
	try {
		m.modifica(12, 0, 1);
	}
	catch (exception&) {
		assert(true); //ar trebui sa arunce exceptie
	}
	try {
		assert(m.nrLinii());
	}
	catch (exception&) {
		assert(false); //nu ar trebui sa arunce exceptie
	}
}
void test_position()
{
	Matrice m(4, 4);
	m.modifica(0, 0, 1);
	m.modifica(0, 2, 2);
	m.modifica(1, 1, 5);
	std::pair<int, int> pozitie = m.position(5);
	assert(pozitie.first == 1);
	assert(pozitie.second == 1);
	std::pair<int, int> pozitie1 = m.position(100);
	assert(pozitie1.first == -1);
	assert(pozitie1.second == -1);
	m.modifica(3, 2, 7);
	std::pair<int, int> pozitie3 = m.position(7);
	assert(pozitie3.first == 3);
	assert(pozitie3.second == 2);
	m.modifica(3, 1, 11);
	std::pair<int, int> pozitie4 = m.position(11);
	assert(pozitie4.first == 3);
	assert(pozitie4.second == 1);
	m.modifica(3, 3, 121);
	std::pair<int, int> pozitie5 = m.position(121);
	assert(pozitie5.first == 3);
	assert(pozitie5.second == 3);
	m.modifica(3, 2, 11);
	std::pair<int, int> pozitie6 = m.position(11);
	assert(pozitie6.first == 3);
	assert(pozitie6.second == 2);
}
void testAllExtins() {
	testCreeaza();
	testAdauga();
	testQuantity();
	testExceptii();
	test_position();
}
