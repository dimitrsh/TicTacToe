#ifndef TICTAC_H
#define TICTAC_H
#include <random>
#include "field.h"
#include "player.h"

#include <ctime>

using namespace std;

void MainLoop(Field * f, Player * p1, Player * p2){
    srand(time(0));
    short stat = 0;
    p1->set_index(1); // players got they numbers automatically, but we can renumerate them.
    p2->set_index(2);
    p1->first_move(); // make sense only at AI first step.
    cout << *f;
    while (stat == 0){
        p2->move();
        cout << *f;
        stat = f->status();
        if (stat != 0) break;
        p1->move();
        cout << *f;
        stat = f->status();
    }
    if(stat == f->P1_WIN) cout << "P1 wins!" << endl;
    else if(stat == f->P2_WIN) cout << "P2 wins!" << endl;
    else cout << "Tie!" << endl;
}

#endif // TICTAC_H

