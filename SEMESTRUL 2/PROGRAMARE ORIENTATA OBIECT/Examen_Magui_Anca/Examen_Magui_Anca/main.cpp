#include "Examen_Magui_Anca.h"
#include <QtWidgets/QApplication>
#include"gui.h"
#include"service.h"
#include"teste.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    test();
    Repo repo{ "utilaje.txt" };
    Service service{ repo };
    GUI gui{ service };
    gui.show();
    return a.exec();
}
