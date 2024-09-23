#include "UI.h"

void meniu()
{
	/*functia meniu care printeaza optiunile pe care le are utilizatorul
	:return: printeaza
	:params:none
	*/
	printf("\n***Meniu***\n");
	printf("1.Adauga cheltuiala\n");
	printf("2.Modifica cheltuiala\n");
	printf("3.Sterge cheltuiala\n");
	printf("4.Filtrare dupa suma,tip,zi\n");
	printf("5.Sortare dupa suma,tip si crescator sau descrescator\n");
	printf("6.Afisare buget\n");
	printf("0.Oprire program\n");
	printf("\n");
}
void meniu_filtrare()
{
	printf("Filtrare dupa:\n");
	printf("1.suma\n");
	printf("2.zi\n");
	printf("3.tip\n");
	printf("\noptiune:");
}
void afisare(Lista lista_buget)
{
	/*functie care parcurge toate elementele unui element de tip Lista si afiseaza cele 3 componente 
	ale listei 
	:return: printeaza elementele
	:params: element de tip Lista
	*/
	printf("Numarul de elemente este : %d\n", lista_buget.len);
	for (int i = 0; i < lista_buget.len; i++)
		printf("suma:   %d ziua:   %d tipul:   %s\n", lista_buget.array[i].suma, lista_buget.array[i].zi, lista_buget.array[i].tip);
}
void ui_adaugare(Lista* lista_buget)
{
	/*functie care citeste suma,zi si tip si apeleaza functia de adaugare de tip int din service care
	* returneaza 0 daca cheltuiala se poate adauga sau diferit de 0 daca datele sunt invalide
	:return : printeaza mesaj aferent executiei
	:params:elementul de tip Lista-pointer
	*/
	int zi, suma,erori;
	char tip[21];
	printf("suma: ");
	scanf_s("%d", &suma);
	printf("zi: ");
	scanf_s("%d", &zi);
	printf("tipul: ");
	tip[20] = '\0';
	scanf_s("%s", tip, 20);
	erori=service_adaugare(suma, zi, tip, lista_buget);
	if (erori != 0)
		printf("date invalide\n");
	else
		printf("cheltuiala adaugata cu succes\n");
}
void ui_modificare(Lista* lista_buget)
{
	/*functie din Ui care citeste componentele unui element care trebuie modificat (suma,zi,tip) si componentele
	* elementului cu care trebuie modificat(m_suma,m_tip,m_zi),functia verifica rezultatul functiei de tip int 
	* din service care valideaza si modifica elementul
	* :return: printeaza mesaj
	* :params:elementul de tip Lista-pointer
	*/
	int zi, suma,rezultat;
	int m_zi, m_suma;
	char m_tip[21];
	char tip[21];
	printf("suma: ");
	scanf_s("%d", &suma);
	printf("zi: ");
	scanf_s("%d", &zi);
	printf("tipul: ");
	tip[20] = '\0';
	scanf_s("%s", tip, 20);
	printf("Introduceti datele noi\n");
	printf("suma: ");
	scanf_s("%d", &m_suma);
	printf("zi: ");
	scanf_s("%d", &m_zi);
	printf("tipul: ");
	m_tip[20] = '\0';
	scanf_s("%s", m_tip, 20);
	rezultat = service_modificare(suma, zi, tip, m_suma, m_zi, m_tip, lista_buget);
	if (rezultat !=0 && rezultat!=5)
		printf("date invalide\n");
	else
	{
		if (rezultat == 5)
			printf("nu s-a gasit elementul\n");
		else
			printf("element modificat cu succes\n");
		return 0;
	}
}
void ui_stergere(Lista* lista_buget)
{
	/*functie care citeste componentele unui element de tip buget(suma,zi,tip) si verifica rezultatul
	* functiei din service de tip int care sterge elementul pentru a printa un mesaj corespunzator
	* :params:pointer la elementul de tip Lista
	* :return:printeaza mesaj
	*/
	int  zi, suma, rezultat;
	char tip[21];
	printf("suma: ");
	scanf_s("%d", &suma);
	printf("zi: ");
	scanf_s("%d", &zi);
	printf("tipul: ");
	tip[20] = '\0';
	scanf_s("%s", tip, 20);
	rezultat = service_stergere(suma, zi, tip, lista_buget);
	if (rezultat != 0 && rezultat!=5)
		printf("date invalide\n");
	else
	{
		if (rezultat == 5)
			printf("nu s-a gasit elementul");
		else
			printf("elementul s-a sters");
		return service_stergere(suma, zi, tip, lista_buget);
	}
}
void ui_filtrare(Lista* lista_buget)
{
	/*functie care citeste afiseaza optiunile de filtrare utilizatorului si citeste optiunea acestuia, respectiv
	* suma,zi sau tip si apeleaza functiile aferente de filtrare din service
	* :return:printeaza lista filtrata
	* :params:pointer la element de tip Lista 
	*/
	int zi, suma, erori,rezultat;
	char tip[21];
	erori = 0;
	int sub_op;
	meniu_filtrare();
	scanf_s("%d", &sub_op);
	if (sub_op == 1) {
		printf("suma:");
		scanf_s("%d", &suma);
		rezultat = validare_negativ(suma);
		if (rezultat == 0) {
			Lista new_l1 = service_filtrare_suma(suma, lista_buget);
			afisare(new_l1);
		}
		else
			printf("suma incorecta\n");
	}
	else if (sub_op == 2)
	{
		printf("zi:");
		scanf_s("%d", &zi);
		rezultat = valideaza_zi(zi);
		if (rezultat == 0) {
			Lista new_l2 = service_filtrare_zi(zi, lista_buget);
			afisare(new_l2);
		}
		else
			printf("zi incorecta\n");
	}
	else if (sub_op == 3)
	{
		tip[20] = '\0';
		printf("tipul: ");
		scanf_s("%s",tip,20);
		rezultat = validare_tipul(tip);
		if (rezultat==0) {
			Lista new_l3 = service_filtrare_tip(tip, lista_buget);
			afisare(new_l3);
		}
		else
			printf("tip incorect\n");

	}
	else
		printf("optiune incorecta");
}
void ui_sortare(Lista* lista_buget)
{
	/*functie care sorteaza o lista dupa optiunile utilizatorului, astfel afiseaza un submeniu si citeste optiunea
	* acestuia si apeleaza functia din service de ordonare cu parametrii dati de utilizator
	* :return:printeaza aferent
	* :pointer la elementul de tip Lista
	*/
	int zi, suma, erori;
	char tip[21];
	erori = 0;
	int tipul, ascensiune;
	printf("Lista ordonata dupa:\n");
	printf("1.suma\n");
	printf("2.tip\n");
	scanf_s("%d", &tipul);
	if (tipul != 2 && tipul != 1)
		printf("optiune incorecta\n");
	else {
		printf("\n\n Alegeti:\n");
		printf("1.crescator\n");
		printf("2.descrescator\n");
		scanf_s("%d", &ascensiune);
		if (ascensiune != 1 && ascensiune != 2)
			printf("optiune incorecta\n");
		else {
			Lista* new_l4 = service_ordonare(tipul, ascensiune, lista_buget);
			afisare(*new_l4);
		}
	}
}
void consola(Lista* lista_buget)
{
	/*functia principala de consola care apeleaza in functie de meniu functiile aferente fiecarei optiune
	a utilizatorului, functia ruleaza atata timp cat utilizatotul nu apasa tasta 0
	:params:pointer de elementul de tip Lista*/
	int ok = 1;
	while (ok)
	{
		meniu();
		int op;
		printf("Optiunea:");
		scanf_s("%d", &op);
		switch (op)
		{
		case 1:
			ui_adaugare(lista_buget);
			break;
		case 2:
			ui_modificare(lista_buget);
			break;
		case 3:
			ui_stergere(lista_buget);
			break;
		case 4:
			ui_filtrare(lista_buget);
			break;
		case 5:
			ui_sortare(lista_buget);
			break;
		case 0:
			return;
			break;
		case 6: 
			afisare(*lista_buget);
			break;
		default:
			break;
		}
	}
}
void test()
{
	//functie de teste care apeleaza functiile de teste din fiecare modul
	test_domeniu();
	test_repo();
	test_validators();
	test_service();
	printf("teste realizate cu succes!\n");
}