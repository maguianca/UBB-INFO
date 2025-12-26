#include <QApplication>
#include <QPushButton>
#include "GUI.h"
#include "Board.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Board board(10,1);
    GUI gui{board};
    gui.show();

    return QApplication::exec();
}
