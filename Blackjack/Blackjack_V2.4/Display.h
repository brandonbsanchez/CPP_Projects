#ifndef DISPLAY_H
#define DISPLAY_H

class Display //Display titles
{
    public:
        void dealCrd(); //Outputs dealer card title
        void finTot(); //Outputs final total title
        void initCrd(); //Outputs initial card title
        virtual void initTot() = 0; //Outputs initial total title
};

#endif