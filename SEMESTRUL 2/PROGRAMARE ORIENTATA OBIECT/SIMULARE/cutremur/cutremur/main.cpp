
#include <QtWidgets/QApplication>
#include"service.h"
#include"domeniu.h"
#include"teste.h"
#include"gui.h"
int main(int argc, char* argv[])
{
    toate_testele();
    QApplication a(argc, argv);
    string file = "cutremur.txt";
    Repo repo{ file };
    Validator val;
    Service service{ repo,val };
    GUI gui{ service };
    gui.show();
    return a.exec();
}
