#include "Procesor.h"
#include <QtWidgets/QApplication>
#include "teste.h"
#include "ui.h"
int main(int argc, char *argv[])
{
    test();
    QApplication a(argc, argv);
    Repo repo{ "fisier1.txt","fisier2.txt" };
    Service service(repo);
    GUI gui(service);
    gui.show();
    //w.show();
    return a.exec();
}
