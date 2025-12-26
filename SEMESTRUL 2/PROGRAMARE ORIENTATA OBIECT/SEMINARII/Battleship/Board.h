#pragma once
#include <vector>
#include <string>

using std::vector;
using std::string;

class BoardException: public std::exception{
    string mesaj;
public:
    BoardException(string msj):mesaj{msj}{};
    string get_mesaj()
    {
        return mesaj;
    }
};

class Board{
private:
    int size;
    vector<vector<int>> board;
    int configuration;
    int moves;
    int status; // 0 = in progress; 1 = lost, 2 = won;
    int atacate; // nr de pozitii de barci atacate ; cand am 9 pozitii atacate, statusul devine 2
    void load_configuration(int config);

public:
    Board(int size, int configuration):size{size}{
        board = vector(size,vector<int>(size,0)); // el din vector initializate cu zero
        // vector de vector de elemente initializate cu 0
        moves=30; // nr initial de mutari posibile
        status=0; // status = 1 -> pierdut, status = 2 -> castigat, status = 0 -> in progres
        atacate=0;
        load_configuration(configuration);
    }
    int get_size() const{ // pot pune const, nu modiifca obiectul board
        return size;
    };
    int get_coordinates(int row, int col)const{
        return board[row][col];
    }
    void attack_coordinates(int row, int col);

    int get_moves(){
        return moves;
    }

    int get_status(){
        return status;
    }

    int get_atacate(){
        return atacate;
    }

};