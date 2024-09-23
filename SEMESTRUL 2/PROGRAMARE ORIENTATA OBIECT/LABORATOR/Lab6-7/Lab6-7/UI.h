#pragma once
#include"service.h"
class UI
{
private:
	Service& service;
	void adaugaUI();
	void afisareUI(const std::vector<Turism>&oferte);
	void stergereUI();
	void modificareUI();
	void cautareUI();
	void filtrare_destinatieUI();
	void filtrare_pretUI();
	void sortare_denumireUI();
	void sortare_destinatieUI();
	void sortare_tip_pretUI();
public:
	UI(Service& service) : service{ service }
	{

	}
	UI(const UI& ot) = delete;
	void run();
};