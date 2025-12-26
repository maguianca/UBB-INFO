#include "Board.h"
#include <fstream>
#include <string>
#include <QApplication>
using std::ifstream;

//facem configuratia din fisier
void Board::load_configuration(int config)
{
    string file_name="configuration"+std::to_string(config)+".txt";
            qDebug()<<file_name;
    ifstream f(file_name);
    if(!f)
        qDebug()<<" no file ";
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            f>>board[i][j];
            //qDebug()<<board[i][j]<<" ";
        }
        qDebug()<<"\n";
    }
}
void Board::attack_coordinates(int row, int col){
    moves--;
    int val=board[row][col];
    if(val==0){
        board[row][col]=2;
    }
    else if(val==1){
        board[row][col]=3;
        atacate++;
    }
    else throw BoardException("Deja lovit!\n") ;
    // daca nu am aruncat exceptie, modific statusul
    if(atacate==9)
        status=2;
    if(moves==0)
        status=1; // am epuizat mutarile si n am castigat inca

}
