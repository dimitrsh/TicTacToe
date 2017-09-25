#ifndef FIELD_H
#define FIELD_H
#include <iostream>

class Field{
private:
    short vals[9];
    bool is_winner(short player){
        if ((vals[0] == vals[1] && vals[0] == vals[2] && vals[0] == player) || // first row
            (vals[3] == vals[4] && vals[3] == vals[5] && vals[3] == player) || // second row
            (vals[6] == vals[7] && vals[6] == vals[8] && vals[6] == player) || // third row
            (vals[0] == vals[3] && vals[0] == vals[6] && vals[0] == player) || // first column
            (vals[1] == vals[4] && vals[1] == vals[7] && vals[1] == player) || // second column
            (vals[2] == vals[5] && vals[2] == vals[8] && vals[2] == player) || // third column
            (vals[0] == vals[4] && vals[0] == vals[8] && vals[0] == player) || // diagonal from left top to right bottom
            (vals[2] == vals[4] && vals[2] == vals[6] && vals[2] == player))   // diagonal from right top to left bottom
            return true;
        return false;
    }
    bool is_full(){
        for(int i = 0; i < 9; i++){
            if(vals[i] == EMPTY) return false;
        }
        return true;
    }
public:
    const short X, O, EMPTY, P1_WIN, P2_WIN, TIE;
    Field() : X(1), O(2), EMPTY(0), P1_WIN(4), P2_WIN(-4), TIE(2) {
        for (int i = 0; i < 9; i++) vals[i] = EMPTY;
    }
    short status(){
        if(this->is_winner(X)) return P1_WIN;       // X is winner.
        else if(this->is_winner(O)) return P2_WIN;  // O is winner.
        else if(this->is_full()) return TIE;        // Tie.
        else return 0;                              // Game continues.
    }
    short & operator() (int lind) {
        return vals[lind];
    }
    void clear(){
        for (int i = 0; i < 9; i++) vals[i] = EMPTY;
    }

    friend std :: ostream & operator << (std :: ostream & os, const Field & f);
};

std :: ostream & operator << (std :: ostream & os, const Field & f){
    char symbols[] = {'.', 'X', 'O'};
    std :: cout << symbols[f.vals[0]] << '\t' << symbols[f.vals[1]] << '\t' << symbols[f.vals[2]] << std :: endl;
    std :: cout << symbols[f.vals[3]] << '\t' << symbols[f.vals[4]] << '\t' << symbols[f.vals[5]] << std :: endl;
    std :: cout << symbols[f.vals[6]] << '\t' << symbols[f.vals[7]] << '\t' << symbols[f.vals[8]] << std :: endl << std :: endl;
}

#endif // FIELD_H

