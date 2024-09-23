#include "domeniu.h"
#include "repo.h"
#include "UI.h"
#include "teste.h"
#define _CRTDBG_MAP_ALLOC
#include<crtdbg.h>
#include<stdlib.h>
#include<string.h>
#include"vector.h"
int main()
{
	teste_teste();
	{Repo repo;
	Validator val;
	Service service{ repo ,val };
	UI ui{ service };
	ui.run(); }
	_CrtDumpMemoryLeaks();
	return 0;
}