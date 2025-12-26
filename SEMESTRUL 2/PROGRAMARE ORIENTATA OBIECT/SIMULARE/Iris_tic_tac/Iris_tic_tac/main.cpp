#include "Iris_tic_tac.h"
#include <QtWidgets/QApplication>
#include "Repo.h"
#include "Service.h"
#include "UI.h"
int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    //    QPushButton button("Hello world!", nullptr);
    //    button.resize(200, 100);
    //    button.show();
    Repo rep;
    Service srv(rep);
    UI ui(srv);
    ui.show();
    return QApplication::exec();
}
