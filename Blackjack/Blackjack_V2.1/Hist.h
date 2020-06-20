#ifndef HIST_H
#define HIST_H

#include <iostream>
#include "Leader.h"
using namespace std;

class Leader;

class Hist //Contains wins/losses/ties
{
    private:
        float winLoss; //Win/Loss %
        int loss = 0; //# of losses
        int tie = 0; //# of ties
        int win = 0; //# of wins
    public:
        friend Leader;
};

#endif

