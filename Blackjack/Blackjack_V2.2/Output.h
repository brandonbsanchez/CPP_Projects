#ifndef OUTPUT_H
#define OUTPUT_H

class Output //Deals with outputs without variables
{
    public:
        void dealCrd(); //Outputs dealer card title
        void initCrd(); //Outputs initial card title
        void initTot(); //Outputs initial total title
        void menu(); //Displays initial menu
        void newCrd(); //Outputs new card title
        void prompt(); //Prompts user whether they want to play or see rules
        void rules(); //Displays rules
        void totCrd(); //Displays total card title
        void finTot();
        void resOut(int); //Displays final results of game
        char playAgn(); //Prompts user if they want to play again
};

#endif

