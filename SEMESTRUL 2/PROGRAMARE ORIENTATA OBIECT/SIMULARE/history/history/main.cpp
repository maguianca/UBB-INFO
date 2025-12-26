#include "history.h"
#include <QtWidgets/QApplication>
#include"gui.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repo repo{ "fisier.txt" };
    Service service{ repo };
    GUI gui{ service };
    gui.show();
    return a.exec();
}
