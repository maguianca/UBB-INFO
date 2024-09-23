#include "domeniu.h"
#include "repo.h"
#include "UI.h"
#include "teste.h"
#include"CosOferte.h"
#define _CRTDBG_MAP_ALLOC
#include<crtdbg.h>
#include<stdlib.h>
#include<string.h>
void run()
{
	//Repo repo;
	string fileName="C:\\Programare orientata obiect\\Lab 9\\Lab 9\\oferte.txt";
	RepoFile repo{ fileName };
	Validator val;
	CosOferte cos;
	Service service{ repo ,val ,cos };
	UI ui{ service };
	ui.run();
}
int main()
{
	teste_teste();
	run();
	_CrtDumpMemoryLeaks();
	return 0;
}