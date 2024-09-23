#pragma once
#include"service.h"
#include"vector.h"
class UI
{
private:
	Service& service;
	void adaugaUI();
	/*functie care face legatura cu userul si apeleaza functia de adauga din Ui */
	static void afisareUI(VectD<Turism> oferte);
	void stergereUI();
	/*functie care face legatura cu userul si apeleaza functia de stergere din Ui */
	void modificareUI();
	/*functie care face legatura cu userul si apeleaza functia de modifica din Ui */
	void cautareUI();
	/*functie care face legatura cu userul si apeleaza functia de cautare din Ui */
	void filtrare_destinatieUI();
	/*functie care face legatura cu userul si apeleaza functia de filtrare din Ui */
	void filtrare_pretUI();
	/*functie care face legatura cu userul si apeleaza functia de filtrare din Ui */
	void sortare_denumireUI();
	/*functie care face legatura cu userul si apeleaza functia de sortare din Ui */
	void sortare_destinatieUI();
	/*functie care face legatura cu userul si apeleaza functia de sortare din Ui */
	void sortare_tip_pretUI();
	/*functie care face legatura cu userul si apeleaza functia de sortare din Ui */
public:
	explicit UI(Service& service) : service{ service }
	{

	}
	UI(const UI& ot) = delete;
	void run();
};