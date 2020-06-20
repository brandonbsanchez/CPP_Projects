#ifndef LEADER_H
#define LEADER_H

#include "Hist.h"

#include <fstream>
#include <string>
using namespace std;

class Hist;

class Leader //Contains wins/losses for each player
{
    private:
        bool found  = false; //If player name matches name in file
        char *name; //Name of player
        int indx; //Index of a certain player in structure array
        int nSize; //Size of player name
        int size; //Size of leader arrays
        long locate; //Locates a certain player in file
        Hist *hist; //History structure for each player
        fstream data;
    public:
        Leader();
        ~Leader()
        {delete []hist;}
        Leader(const Leader&);
        void fill(string, int, int, int);
        void foundNm(long, int);
        void newName(char[], int, int, int, int, bool);
        void setSize(int);
        int getSize();
        int getIndx();
        bool getFnd();
        void decSize();
        void playHis(bool); //Displays player's wins/losses/ties
        int getWin();
        int getLoss();
        void setWL();
        int getWL();
        Leader operator++();
        Leader operator--();
        Leader operator+=(int);
        long getLoc();
        char* getNme();
        int getTie();
        void setNme(char*);
        void setWin(int);
        void setLoss(int);
        void setTie(int);
        void setWL(int);
};

#endif

