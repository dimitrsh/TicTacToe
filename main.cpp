#include <iostream>
#include <random>
#include "tictac.h"

int main()
{
    Field f;
    Human h(f);
    Robot r(f);
    int continue_flag = 1;
    int order;
    while(continue_flag == 1){
        do{
            std :: cout << "Chose player(1 - X, 2 - O): ";
            std :: cin >> order;
            if (order == 1)
                MainLoop(&f, &h, &r);
            else if(order == 2)
                MainLoop(&f, &r, &h);
        } while (order != 1 && order != 2);
        std :: cout << "1 - continue, any other number - exit: ";
        std :: cin >> continue_flag;
        f.clear();
    }
    return 0;
}

