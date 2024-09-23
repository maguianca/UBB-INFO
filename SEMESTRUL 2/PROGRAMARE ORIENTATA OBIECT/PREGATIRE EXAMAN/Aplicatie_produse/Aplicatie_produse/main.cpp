#include "Aplicatie_produse.h"
#include <QtWidgets/QApplication>
#include"gui.h"
#include"service.h"
#include"teste.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    teste();
    Repo repo{ "produse.txt" };
    Validator val{ repo };
    Service service{ repo,val };
    GUI gui{ service };
    gui.show();
    return a.exec();
}