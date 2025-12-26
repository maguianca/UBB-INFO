#include "SimulareApartamente.h"
#include <QtWidgets/QApplication>
#include"ui.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repo repo{ "apartamente.txt" };
    Service service{ repo };
    GUI gui{ service };
    gui.show();
    return a.exec();
}
