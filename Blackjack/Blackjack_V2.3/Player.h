#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Ace.h"
using namespace std;

class Player : public Ace
{
    private:
        const int ROW = 2;
        const int COL = 13;
        int size = 0; //Keeps track of vector sizes from previous games
        int tot = 0; //Total
        string **nameArr; //Attaches card values to card names
        vector<int> name; //Contains card names
        vector<int> suit; //Contains suit names
        vector<int> val; //Contains card values
        Ace ace;
    public:
        Player();
        ~Player();
        int aceChce(); //Player chooses their ace value
        int crdPlay(int); //Draws card for dealer/player, stores in vectors
        int nameVal(); //Randomly generates card value
        int suitVal(); //Randomly generates suit value
        void outDeal(); //Outputs dealer card
        void outPlay(); //Outputs player card
        enum Deck{DEALER, PLAYER}; //Differentiates dealer and player decks
        void aceChck(); //Checks if ace was drawn
        int gtAce11();
        bool aceBust();
        void totDeal(); //Outputs dealer total
        void totPlay(); //Outputs player total
        bool hitFun(); //Prompts user to hit or stay
        void dealDrw(); //Draws dealer cards until tot < 17
        void aceDeal(); //Reduces dealer ace value to prevent busting
        void dCards(); //Displays all dealer cards in game
        void pCards(); //Displays all player cards in game
        int getTot();
        void reset();
};

#endif

