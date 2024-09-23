#include "consola.h"
#include "OfertaRepo.h"
#include "AgentieService.h"
#include "Validator.h"
#include "teste.h"
#define _CRTDBG_MAP_ALLOC
#include<crtdbg.h>
#include<stdlib.h>
void alocare()
{
    int* p = new int{ 6 };
}
int main() {
    //alocare();
    test_all();
    OfertaRepo repo;
    Validator valid;
    AgentieService service{ repo, valid };
    Consola ui{ service };
    ui.run(); 
    _CrtDumpMemoryLeaks();
}