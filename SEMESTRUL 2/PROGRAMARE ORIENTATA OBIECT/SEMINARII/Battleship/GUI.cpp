//
// Created by A on 05/06/2024.
//
#include <QMessageBox>
#include <QFormLayout>

#include "GUI.h"
void GUI::init_gui() {
    QFormLayout *layout= new QFormLayout{};
    main = new QHBoxLayout;
    right_side = new QVBoxLayout;
    mesaj = new QLabel("Alege un numar de la 1 la 5 si apasa NewGame");
    status = new QLabel;
    movess = new QLabel("Mutari ramase: 30");
    reguli = new QLabel("Dimensiuni barci:\n1*barca de 2\n1* barca de 3\n1*barca de 4");
    attack= new QPushButton("Attack");
    new_game = new QPushButton("New Game");
    config = new QLineEdit;
    table_view = new QTableView;
    table_model = new BattleshipTableModel(board);
    //model = partea de date
    //view ia datele din model; gen view data
    table_view->setModel(table_model);
    table_view->resizeColumnsToContents();
    table_view->resizeRowsToContents();

    layout->addRow("Alege jocul (nr de la 1 la 5):",config);
    setLayout(main);
    main->addWidget(table_view);
    right_side->addWidget(mesaj);
    right_side->addWidget(reguli);
    right_side->addWidget(movess);
    right_side->addWidget(status);
    right_side->addWidget(attack);
    right_side->addLayout(layout);
    right_side->addWidget(new_game);
    main->addLayout(right_side);

}

void GUI::connect(){
    QObject::connect(attack, &QPushButton::clicked, [&](){
        QModelIndexList indexes = table_view->selectionModel()->selectedIndexes();
        //apas attack si atac celula corespunzatoare
        if(indexes.isEmpty()){
            QMessageBox::warning( nullptr, "hopa","selecteaza o celula.");
        }
        else{
            QModelIndex index =table_view->selectionModel()->selectedIndexes()[0];
            qDebug()<<index.row()<<" "<<index.column()<<"\n";
            try{
                board.attack_coordinates(index.row(),index.column());
            }
            catch (BoardException &ex){
                // am exceptie daca incerc sa lovesc un punct deja lovit
                //afisez in qmessagebox msj de eroare
                QMessageBox::warning(nullptr,"hopa", "ai mai atacat o data...");
            }
        }
        reload_table();
    });
    QObject::connect(new_game,&QPushButton::clicked, [&](){
        int nr = config->text().toInt();
        qDebug()<<"Numar din edit: "<<nr;
        if(nr<1 || nr>5)
        {
            QMessageBox::warning(nullptr, "numaram....","de la 1 la 5...");
        }
        else{
            board= Board(10,nr);
            reload_table();
        }

    });
}

void GUI::reload_table() {
    string msj="Mutari ramase: "+std::to_string(board.get_moves());
    movess->setText(QString::fromStdString(msj));
    //setez statusul
    if(board.get_status()==0)
    {
        status->setText(QString::fromStdString("In progress..."));
    }
    else if(board.get_status()==1){
        status->setText(QString::fromStdString("Ai pierdut :("));
    }
    else {
        status->setText(QString::fromStdString("Ai castigat!! :)"));
        QMessageBox::information(nullptr,"bravooo","Ai castigat!! :)");
    }
    table_model->update();
}