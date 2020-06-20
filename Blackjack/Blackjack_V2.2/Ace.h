#ifndef ACE_H
#define ACE_H

class Player;

class Ace //Deals with aces
{
    private:
        bool found = false; //Marks if an ace was found
        int ace1 = 0; //# of aces worth 1
        int ace11 = 0; //# of aces worth 11
        int aceCnt = 0; //Total # of aces
    public:
        friend Player;
};

#endif

