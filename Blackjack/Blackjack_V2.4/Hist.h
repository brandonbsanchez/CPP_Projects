#ifndef HIST_H
#define HIST_H

#include <iostream> //I/O library
using namespace std;

#include "Leader.h" //Contains leaderboard stats for each player

class Leader; //Forward declaration

class Hist //Contains wins/losses/ties
{
    private:
        float winLoss = 0; //Win/Loss %
        int loss = 0; //# of losses
        int tie = 0; //# of ties
        int win = 0; //# of wins
    public:
        friend Leader;
};

#endif