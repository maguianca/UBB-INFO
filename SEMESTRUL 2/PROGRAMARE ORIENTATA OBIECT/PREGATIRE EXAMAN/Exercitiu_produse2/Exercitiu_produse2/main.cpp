#include "Exercitiu_produse2.h"
#include <QtWidgets/QApplication>
#include"service.h"
#include"gui.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repo repo{ "produse.txt" };
    Validator val{ repo };
    Service service{ repo,val };
    GUI gui{ service };
    gui.show();
    return a.exec();
}
