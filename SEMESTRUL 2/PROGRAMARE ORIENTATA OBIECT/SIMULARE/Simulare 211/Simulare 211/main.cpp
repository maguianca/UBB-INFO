#include "Simulare211.h"
#include <QtWidgets/QApplication>
#include"gui.h"
#include"teste.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    string fisier = "fisier.txt";
    Repo repo{ fisier };
    Service service{ repo };
    Gui gui{ service };
    teste();
    gui.show();
    return a.exec();
}
