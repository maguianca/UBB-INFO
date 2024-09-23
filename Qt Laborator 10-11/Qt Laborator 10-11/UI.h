#pragma once
#pragma once
#pragma once
#include"service.h"
//#include"vector.h"
class UI
{
private:
	Service& service;
	void adaugaUI();
	/*functie care face legatura cu userul si apeleaza functia de adauga din Ui */
	void afisareUI()const;
	void afisareUI_cos()const;
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
	void Meniu();
	/*functie care afiseaza meniul si face apel la functiile care tin ce meniul respcetiv*/
	void cosAdaugaUI();
	/*functie care adauga in meniu de wishlist o oferta existenta deja*/
	void cosAdaugaRandomUI();
	/*functie care adauga random in wishlist oferte deja existente*/
	void cosStergeUI();
	/*functie care sterge o oferta din wishlist*/
	void raport_UI();
	/*functie care afiseaza un raport destinatie->nr oferte*/
	void cosExportUI();

public:
	explicit UI(Service& service) : service{ service }
	{

	}
	UI(const UI& ot) = delete;
	void run();
};