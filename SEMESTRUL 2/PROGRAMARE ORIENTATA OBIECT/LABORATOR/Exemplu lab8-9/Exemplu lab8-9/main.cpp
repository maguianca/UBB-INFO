#include "consola.h"
#include "OfertaRepo.h"
#include "AgentieService.h"
#include "Validator.h"
#include "teste.h"

int main() {
    test_all();
    string fileName = "C:\\Programare orientata obiect\\Exemplu lab8-9\\Exemplu lab8-9\\oferte.txt";
    //OfertaRepoFile repo{ fileName };
        RepoLab repolab;
        repolab.setProbabilitate(0.5); // probabilitate [0, 1]
    //OfertaRepo repo;
    Validator valid;
    CosOferte cos;
    AgentieService service{ repolab, valid, cos };
    Consola ui{ service };
    ui.run();
}