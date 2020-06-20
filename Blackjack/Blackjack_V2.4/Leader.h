#ifndef LEADER_H
#define LEADER_H

#include <fstream> //File Library
#include <string> //String Library
using namespace std;

#include "Hist.h" //Contains wins/losses/ties

class Hist; //Forward declaration

class Leader //Contains leaderboard stats for each player
{
    private:
        bool found  = false; //If player name matches name in file
        string name; //Name of player
        int indx; //Index of a certain player in structure array
        int size; //Size of leader arrays
        long locate; //Locates a certain player in file
        Hist *hist; //History structure for each player
        fstream data; //Used for files
    public:
        Leader(); //Allocates memory for hist
        ~Leader() //Deallocates memory
        {delete []hist;}
        Leader(const Leader&); //Copy constructor
        Leader operator++(); //Adds 1 to wins
        Leader operator--(); //Adds 1 to losses
        Leader operator+=(int); //Adds number to tie
        bool getFnd(); //Returns found
        int getIndx(); //Returns indx
        int getLoss(); //Returns loss
        int getSize(); //Returns size
        int getTie(); //Returns tie
        int getWin(); //Returns win
        int getWL(); //Returns win/loss ratio
        long getLoc(); //Returns locate
        string getNme(); //Returns name
        void decSize(); //Decreases size by 1
        void fill(string, int, int, int); //Fills leader array
        void foundNm(long, int, bool); //If name is found
        void newName(string, int, int, int, int, bool); //If name is not found
        void playHis(bool); //Displays player's wins/losses/ties
        void setIndx(int); //Sets indx
        void setLoss(int); //Sets loss
        void setNme(string); //Sets name
        void setSize(int); //Sets size
        void setTie(int); //Sets tie
        void setWin(int); //Sets win
        void setWL(); //Sets win/loss
        void setWL(int); //Sets win/loss from file
};

#endif