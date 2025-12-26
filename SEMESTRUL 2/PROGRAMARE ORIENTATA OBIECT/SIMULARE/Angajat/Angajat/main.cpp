#include "Angajat.h"
#include <QtWidgets/QApplication>
#include"teste.h"
#include"GUI.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    test();
    string file = "persoane.txt";
    Repo repo{ file };
    Service service{ repo };
    GUI gui{ service };
    gui.show();
    return a.exec();
}
