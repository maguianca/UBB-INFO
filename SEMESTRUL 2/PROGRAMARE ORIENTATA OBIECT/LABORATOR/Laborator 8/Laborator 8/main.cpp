#include "domeniu.h"
#include "repo.h"
#include "UI.h"
#include "teste.h"
#include"CosOferte.h"
#define _CRTDBG_MAP_ALLOC
#include<crtdbg.h>
#include<stdlib.h>
#include<string.h>
#include"vector.h"
void run()
{
	Repo repo;
	Validator val;
	CosOferte cos;
	Service service{ repo ,val ,cos};
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