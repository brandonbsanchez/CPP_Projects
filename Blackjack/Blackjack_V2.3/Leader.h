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
        string name; //Name of player
        int indx; //Index of a certain player in structure array
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
        void foundNm(long, int, bool);
        void newName(string, int, int, int, int, bool);
        void setSize(int);
        static int getSize();
        int getIndx();
        bool getFnd();
        void decSize();
        void playHis(bool); //Displays player's wins/losses/ties
        int getWin();
        int getLoss();
        int getWL();
        Leader operator++();
        Leader operator--();
        Leader operator+=(int);
        long getLoc();
        string getNme();
        int getTie();
        void setNme(string);
        void setWin(int);
        void setLoss(int);
        void setTie(int);
        void setWL();
        void setIndx(int);
        void setWL(int);
};
#endif

