#include <QtWidgets/QApplication>
#include <QLabel>
#include "teste.h"
#include"CosOferte.h"
#define _CRTDBG_MAP_ALLOC
#include<crtdbg.h>
#include<stdlib.h>
#include<string.h>
#include<GUI.h>
#include<GUIModele.h>
int main(int argc, char* argv[]) {
    teste_teste();
    QApplication a(argc, argv);
    string fileName = "C:\\Programare orientata obiect\\Qt Laborator 10-11\\Qt Laborator 10-11\\oferte.txt";
    RepoFile repo{ fileName };
    // RepoLab repolab;
    // repolab.setProbabilitate(1); // probabilitate [0, 1]
    // OfertaRepo repo;
    Validator valid;
    CosOferte cos{ repo };
    Service service{ repo, valid, cos };
    //GUI gui{ service };
    ModelGUI gui{ service };
    //    Consola ui{service};
    //    ui.run();
    gui.show();
    return a.exec();
}