#include <iostream>
#include <random>
#include <ctime>
#include "tictac.h"

int main()
{
    Field f;
    Human h(f);
    Robot r(f);
    MainLoop(&f, &r, &h);
    return 0;
}

