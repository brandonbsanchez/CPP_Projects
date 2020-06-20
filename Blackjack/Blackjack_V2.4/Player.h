#ifndef PLAYER_H
#define PLAYER_H

#include <string> //String Library
#include <vector> //Vector Library
using namespace std;

#include "Ace.h" //Contains ace vectors

class Player : public Ace //Player stats/cards, derived from ace
{
    private:
        const int ROW = 2; //Row for name array
        const int COL = 13; //Column for name array
        int size = 0; //Keeps track of vector sizes from previous games
        int tot = 0; //Total
        string **nameArr; //Attaches card values to card names
        vector<int> name; //Contains card names
        vector<int> suit; //Contains suit names
        vector<int> val; //Contains card values
    public:
        Player(); //Fills name array
        ~Player(); //Deletes name array
        enum Deck{DEALER, PLAYER}; //Differentiates dealer and player decks
        bool aceBust(); //Finds aces if player busts
        bool hitFun(); //Prompts user to hit or stay
        int aceChce(); //Player chooses their ace value
        int crdPlay(int); //Draws card for dealer/player, stores in vectors
        int getTot(); //Returns total
        int gtAce11(); //Returns ace11 value
        int nameVal(); //Randomly generates card value
        int suitVal(); //Randomly generates suit value
        void aceChck(); //Checks if ace was drawn
        void aceDeal(); //Reduces dealer ace value to prevent busting
        void dCards(); //Displays all dealer cards in game
        void dealDrw(); //Draws dealer cards until tot < 17
        void outDeal(); //Outputs dealer card
        void outPlay(); //Outputs player card
        void pCards(); //Displays all player cards in game
        void reset(); //Resets game stats
        void totDeal(); //Outputs dealer total
        void totPlay(); //Outputs player total
};
#endif