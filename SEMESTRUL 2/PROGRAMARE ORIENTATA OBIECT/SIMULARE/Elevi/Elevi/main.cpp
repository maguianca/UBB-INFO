#include "Elevi.h"
#include <QtWidgets/QApplication>
#include"teste.h"
#include"gui.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    string fisier = "elevi.txt";
    Repo repo{ fisier };
    Service service{ repo };
    GUI gui{ service };
    teste();
    gui.show();
    return a.exec();
}
