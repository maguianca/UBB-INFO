#include "XsiO.h"
#include <QtWidgets/QApplication>
#include"gui.h"
#include"service.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repo repo{ "fis.txt" };
    Validator val{};
    Service service{ repo,val };
    GUI gui{ service };
    gui.show();
    return a.exec();
}
