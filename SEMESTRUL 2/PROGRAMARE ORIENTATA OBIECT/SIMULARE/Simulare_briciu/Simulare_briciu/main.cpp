#include "Simulare_briciu.h"
#include <QtWidgets/QApplication>
#include"gui.h"
#include"service.h"
#include"teste.h"
#include"repo.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    string file = "oferte.txt";
    string d = "castigatori.txt";
    Repo repo{ file,d};
    Service service{ repo };
    GUI gui{ service };
    gui.show();
    return a.exec();
}
