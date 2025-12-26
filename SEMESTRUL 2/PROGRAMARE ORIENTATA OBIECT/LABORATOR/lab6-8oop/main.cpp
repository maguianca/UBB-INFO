#include <iostream>
#include "UI.h"
#include "Teste.h"
#include "Pet.h"
#include "teste_vector.h"
using std::cout;
using std::endl;

//void test_all(){
//    teste_domain();
//    cout << "Finished domain tests." << endl;
//    teste_repo();
//    cout << "Finished repo tests." << endl;
//    teste_service();
//    cout << "Finished service tests." << endl;
//}

void start_app(){
    Medicament_Repository repo;
    Medicament_Validator val;
    Medicamente_Service srv{repo, val};
    Console ui{srv};

    ui.run();
}

int main() {
    test_all();
    testAll<VectorDinamic<Pet>>();
    start_app();
    return 0;
}
