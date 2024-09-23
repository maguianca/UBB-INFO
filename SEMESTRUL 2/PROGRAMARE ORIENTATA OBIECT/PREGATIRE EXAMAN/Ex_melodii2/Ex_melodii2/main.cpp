#include "Ex_melodii2.h"
#include <QtWidgets/QApplication>
#include"gui.h"
#include"service.h"
#include"teste.h"
int main(int argc, char *argv[])
{
    test();
    QApplication a(argc, argv);
    Repo repo{ "fisier.txt" };
    Service service{ repo };
    GUI gui{ service };
    gui.show();
    return a.exec();
}
