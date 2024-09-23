/*
Sa se scrie un program C pentru unul dintre urmatoarele probleme.
Aplicatia ofera un mic meniu pentru a efectua repetat operatia ceruta.
Programul trebuie sa contina cel putin 2 functii. (functia main+ 1,2 functii)
Fiecare funtie trebuie specificata. Specificatia contine: a scurta descriere, descrierea parametrilor, conditii impuse asupra datelor de intrare (preconditii), descriere rezultatului (post conditii)


Determina primele n perechi de numere prime gemene, unde n este un
numar natural nenul dat.Doua numere prime p si q sunt gemene
daca q - p = 2.
6. Tiparste triunghiul lui Pascal, cu toate combinarile C(m,k) de m obiecte
   luate cite k, k = 0, 1, ..., m, in linia m, pentru m = 1, 2, ..., n.
   */

#include<stdio.h>
int op,n;
int meniu()
{
	/*functie  void care printeaza meniul si citeste optiunea utilizatorului 
	* daca este 0 optiunea utilizatorului atunci se opreste programul fortat
		:param :none
		:preconditii: none
		:postconditii: functia opreste programul sau returneaza 1 sau 2 in functie de optiunea utilizatorului
	*/
	printf("***Meniu***\n");
	printf("0.introduceti tasta 0 pentru a termina programul\n");
	printf("1.introduceti tasta 1 pentru a afisa primele n perechi numere prime\n");
	printf("2.introduceti tasta 2 pentru a afisa triunghiul lui Pascal\n");
	printf("Tasta:");
	scanf_s("%d", &op);
	while(op != 0 && op !=1 && op!=2)
	{
		printf("tasta incorecta introduceti din nou:");
		scanf_s("%d:", &op);
	}
	if (op == 0)
	{
		printf("Program terminat\n");
		return 0;
	}
	return op;
}
int prim(int x)
{
	/*functia de tip int care verifica daca numarul x este prim
	:params: x int (numarul care trebuie verificat)
	:preconditii : x numar intreg 
	:postconditii : adevarat daca este prim (returneaza 1) altfel fals (returneaza 0)
	*/
	if (x < 2)
		return 0;
	if (x != 2 && x % 2 == 0)
		return 0;
	for(int i = 3; i*i<=x; i += 2)
		if (x % i == 0)
			return 0;
	return 1;
}
int combinari(int m, int k)
{
	/*
	* functia de tip int returneaza numarul de pe linia m coloana k din triunghiul lui Pascal
	* :params:m-int, k-int 
	* :preconditii:m,k numere naturale
	* :postconditii: se formeaza numarul din triunghiul lui Pascal dupa formula combinarilor
	*/
	int p = 1;
	for (int i = 1; i <= k; i++)
		p = p * (m - i + 1) / i;
	return p;
}
void triunghi(int n)
{
	/*
	* formeaza triunghiul lui Pascal apeland functia de combinari si printeaza
	* :params: n-int 
	* :preconditii:n numar natural 
	* :postconditii: afiseaza triunghiul 
	*/
	int x;
	for (int j = 0; j <= n; j++) {
		for (int i = 0; i <= j; i++)
		{
			x = combinari(j, i);
			printf("%d ", x);
		}
		printf("\n");
	}

}
void numere_gemene(int n)
{
	/*
	* Functie care afiseaza numerele gemene
	* se ia un contor care se incrementeaza la fiecare operatie si se afiseaza cate o pereche 
	* cat timp contor < numarul de perechi ,functia apeleaza functia prim
	* params: n int -reprezinta nr perechilor de numere gemene
	* return: printeaza numerele
	* preconditii: n>0
	* postconditii:printeaza primele n perechi de numere p,q prime unde q-p=2
	*/
	int contor = 0,numar_curent=2;
	printf("\nPrimele %d perechi de numere sunt:\n", n);
	while (contor < n)
	{
		if (prim(numar_curent) == 1 && prim(numar_curent + 2) == 1) {
			printf("<%d, %d>\n", numar_curent, numar_curent + 2);
			contor++;
		}
		numar_curent++;
	}

}
int main()
{
	/*
	* Functia principala care apeleaza functia de meniu si se executa pana cand optiunea utilizatorului 
	* este 0, citeste un numar n cat timp acesta este mai mare decat 0 si apeleaza functia
	* de numere gemene care va afisa numerele cerute daca optiunea utilizatorului este 1, respectiv apeleaza
	* functia de afisare a triunghiului daca optiunea este 2
	* :params : none
	* :postconditii:numarul n citit este >0
	*/
	op=meniu();
	while(op == 1) 
	{
		printf("introduceti numarul n:");
		scanf_s("%d", &n);
		if (n > 0)
			numere_gemene(n);
		else
			while (n <= 0)
			{
				printf("introduceti numarul n:");
				scanf_s("%d", &n);
			}
		meniu();
	}
	while (op == 2)
	{
		printf("introduceti numarul n:");
		scanf_s("%d", &n);
		if (n > 0)
			triunghi(n);
		else
			while (n <= 0)
			{
				printf("introduceti numarul n:");
				scanf_s("%d", &n);
			}
		meniu();
	}
	return 0;
}