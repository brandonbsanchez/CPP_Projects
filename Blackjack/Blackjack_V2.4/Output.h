#ifndef OUTPUT_H
#define OUTPUT_H

#include "Display.h"

class Output : public Display //Deals with outputs without variables
{
    public:
        char playAgn(); //Prompts user if they want to play again
        void initTot(); //Outputs initial total title 
        void menu(); //Displays initial menu
        void newCrd(); //Outputs new card title
        void prompt(); //Prompts user whether they want to play or see rules
        void resOut(int); //Displays final results of game
        void rules(); //Displays rules
        virtual void totCrd(); //Displays total card title
};

#endif