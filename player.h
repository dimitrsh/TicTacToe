#ifndef PLAYER
#define PLAYER
#include <iostream>
#include "field.h"
#include <random>

class Player{
// Abstract, you see.
protected:
    Field * field;      // can't exist out of game.
    short index;        // X or O?
    static short count; // static to watch over all players.
public:
    Player(Field & f) : field(&f) {
        // automatically numerated in creation order.
        index = ++count;
    }
    void set_index(short ind){
        // to renumerate players.
        index = ind;
    }

    virtual void move() = 0;       // for common interface.
    virtual void first_move() = 0; // ai first step will be different from all other steps. We don't have to precalculate it.
};

short Player::count = 0;

class Human : public Player{
public:
    Human(Field & f) : Player(f) {}
    void move(){                                                 // keyboard input. Now it's only console version.
        std :: cout << "Insert x, y : ";
        short x, y;
        std :: cin >> x >> y;
        int lind = (x - 1) * 3 + (y - 1);
        if (lind >= 0 && lind < 9 && (*field)(lind) == field->EMPTY) (*field)(lind) = index;
        else move();
    }
    void first_move(){                                           // the same as other 'move' for human.
        move();
    }
};

class Robot : public Player {
protected:
    short max_depth;
public:
    Robot(Field & f, short max_depth_) : Player(f), max_depth(max_depth_) {}
    Robot(Field & f) : Robot(f, 8) {}

    // maxy and miny functions are quite the same. They differs only in the side they are looking from.
    // maxy is needed to find the better place for X
    // miny is needed to find the better  cell for O

    short maxy(short cur_depth){
        short status = field->status();
        if (status != field->EMPTY || cur_depth == max_depth) return status;
        short res_stat = -10;                                    // there may be any other negative number that less than -4.
        for(int i = 0; i < 9; i++){
            if((*field)(i) == field->EMPTY) {
                (*field)(i) = field->X;                        // put current player sign in the first empty cell
                short cur_stat = miny(cur_depth + 1);  // try to find the better position for opponent, if this cell was used.
                (*field)(i) = field->EMPTY;                      // return field to previous state,
                if (cur_stat > res_stat) res_stat = cur_stat;    // find the worst state for opponent.
                if (res_stat == field->P1_WIN ) return res_stat; // use first better position. All others will not be better than this.
                                                                 // it accelerates first wise ai step for about 12 times!
            }
        }
        return res_stat;
    }

    short miny(short cur_depth){
        short status = field->status();
        if (status != field->EMPTY || cur_depth == max_depth) return status;
        short res_stat = 10;                                     // there may be any other positive number that greater than 4.
        for(int i = 0; i < 9; i++){
            if((*field)(i) == field->EMPTY) {
                (*field)(i) = field->O;
                short cur_stat = maxy(cur_depth + 1);
                (*field)(i) = field->EMPTY;
                if (cur_stat < res_stat) res_stat = cur_stat;
                if (res_stat == field->P2_WIN ) return res_stat;
            }
        }
        return res_stat;
    }

    void move(){
        int mind = -1;  // index of next position.
        // next two conditions are just the first steps of 'miny' or 'maxy' functions, depends on what player it is.
        if(index == field->X){
            short res_stat = -10;
            for(int i = 0; i < 9; i++){
                if((*field)(i) == field->EMPTY){
                    (*field)(i) = field->X;
                    short cur_stat = miny(1);
                    (*field)(i) = field->EMPTY;
                    if (cur_stat > res_stat){
                        res_stat = cur_stat;
                        mind = i;
                    }
                    if (res_stat == field->P1_WIN) break;
                }
            }
        }
        else{
            short res_stat = 10;
            for(int i = 0; i < 9; i++){
                if((*field)(i) == field->EMPTY){
                    (*field)(i) = field->O;
                    short cur_stat = maxy(1);
                    (*field)(i) = field->EMPTY;
                    if (cur_stat < res_stat){
                        res_stat = cur_stat;
                        mind = i;
                    }
                    if (res_stat == field->P2_WIN) break;
                }
            }
        }
        // now 'mind' contains the index of cell, that AI should use.
        (*field)(mind) = index;
    }

    void first_move(){
        // just random position.
        int lind = rand() % 9;
        (*field)(lind) = index;
    }
};

#endif // PLAYER

