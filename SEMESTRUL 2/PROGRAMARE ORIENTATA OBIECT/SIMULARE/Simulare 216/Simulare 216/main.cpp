#include "Simulare216.h"
#include <QtWidgets/QApplication>
#include"teste.h"
#include"gui.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    teste();
    string fisier = "catalog.txt";
    Repo repo{ fisier };
    Service service{ repo };
    Gui consola{ service };
    consola.show();
    return a.exec();
}
