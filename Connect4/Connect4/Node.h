#ifndef NODE_H
#define	NODE_H
#include <cstdlib>
#include <string>
#include <set>

using namespace std;


struct Record //Holds player stats
{
    set<int> win = {0}; //Wins by player
    set<int> loss = {0}; //Losses by player
    set<int> tie = {0}; //Ties by player
    float winLoss; //Win/Loss % by player
};

class Node {
public:
    //string name;
    pair<string,Record> record;
    int height;
    Node* left;
    Node* right;
};

#endif	/* NODE_H */