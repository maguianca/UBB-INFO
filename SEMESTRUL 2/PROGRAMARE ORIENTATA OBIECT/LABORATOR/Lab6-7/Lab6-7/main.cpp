#include "domeniu.h"
#include "repo.h"
#include "UI.h"
#include "teste.h"
int main()
{
	teste_teste();
	Repo repo;
	Service service{ repo };
	UI ui{ service };
	ui.run();
	return 0;
}