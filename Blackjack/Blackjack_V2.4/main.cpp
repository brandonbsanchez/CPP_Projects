/* 
 * File:   main.cpp
 * Author: Brandon Sanchez
 * Created on July 26th, 2019, 5:26 PM
 * Purpose: Blackjack Game.
 */

//System Libraries
#include <cstdlib> //Random Number Generator Library
#include <ctime> //Time Library
#include <fstream> //File Library
#include <iomanip> //Formatting Library
#include <iostream> //I/O Library
#include <string> //String Library
#include <vector> //Vector Library
using namespace std;

//User Libraries
#include "Leader.h" //Leaderboard class
#include "Output.h" //Output class
#include "Player.h" //Player & dealer cards/stats class

enum Deck{DEALER, PLAYER}; //Differentiates dealer and player decks

//Function Prototypes
Leader* getData(); //Gets data from file
void check(string); //Validates name input
void finOut(Leader[]); //Outputs leaderboard
void freeMem(Leader[]); //Frees dynamically allocated memory
void getName(Leader[]); //Gets name of player
template <class T>
void ratio(T[]); //Deals with win/loss ratio
void result(Player[], Leader[]); //Calculates final results of game
void write(Leader[]); //Writes to file

int main()
{
    srand(static_cast<unsigned int>(time(0))); //Set the random number seed
    
    const int ROW = 2, SIZE = 0;
    bool bust; //If player busts
    char play; //Choice to play or see rules first
    Output output; //Output class
    Leader *leader = nullptr; //Holds Leader object for each player in leaderboard
    Player player[ROW]; //Card tracker for player and dealer
    
    leader = getData(); //Filling leader array from file
    output.menu(); //Fills card name array
    output.prompt(); //Outputs initial menu
    getName(leader); //Gets player name
    do
    {
    output.initCrd(); //Initial card title output
    player[DEALER].outDeal(); //Dealer first card
    player[PLAYER].outPlay(); //Player first card
    player[PLAYER].outPlay(); //Player second card
    player[PLAYER].aceChck(); //Checks for aces
    if(player[PLAYER].gtAce11() == 2)
        player[PLAYER].aceBust(); //Prevents from busting off 2 initial aces
    output.initTot(); //Outputs initial total title
    player[DEALER].totDeal(); //Outputs dealer total
    player[PLAYER].totPlay(); //Outputs player total
    bust = player[PLAYER].hitFun(); //Allows player to keep hitting, checks if they bust
    if(bust == false)
    {
        player[DEALER].dealDrw(); //Draw for dealer until tot<17 or bust
        output.totCrd(); //Total card output
        player[DEALER].dCards(); //Outputs all dealer cards
        player[PLAYER].pCards(); //Outputs all player cards
        output.finTot(); //Outputs totals title
        player[DEALER].totDeal(); //Outputs dealer total
        player[PLAYER].totPlay(); //Outputs player total
    }
    result(player, leader); //Outputs if player wins/loses/ties
    leader[leader[0].getIndx()].playHis(bust); //Outputs player wins/losses/ties
    play = output.playAgn(); //Prompts player to play again
    player[DEALER].reset(); //Resets stats for next game
    player[PLAYER].reset(); //Resets stats for next game
    }while(play == 'y' || play == 'Y');
    ratio(leader); //Calculates win/loss ratio
    write(leader); //Writes player history to file
    finOut(leader); //Outputs leaderboard
    freeMem(leader); //Frees allocated memory
    
    return 0;
}

Leader* getData()
{
    fstream data;
    data.open("Data.dat" , ios::in);
    string temp;
    int count = 0, lines = 0, win, loss, tie, size;
    Leader *leader = nullptr;
    
    while(getline(data, temp))
        lines++;
    
    data.close();
    data.open("Data.dat" , ios::in);
    
    leader = new Leader[lines + 1];
    size = lines;
    leader[0].setSize(size);
    
    for(int i = 0 ; i < lines ; i++)
    {
        data >> temp;
        data >> win;
        data >> loss;
        data >> tie;
        leader[i].fill(temp, win, loss, tie);
    } 
            
    data.close();
    
    return leader;
    //Receives each players info from file
}
void check(string temp)
{
    if(temp.size() > 10 || isdigit(temp[0]))
    {
        string error = "Invalid Input! Max 10 characters. Do not start with a number.";
        throw error;
    }
    
    //Validates name input
}
void freeMem(Leader leader[])
{
    delete []leader;

    //Frees allocated memory
}
void finOut(Leader leader[])
{
    const int W = 4;
    
    cout << "--------------------------------" << endl;
    cout << "     Leaderboard (By W/L %)     " << endl;
    cout << "--------------------------------" << endl;
    cout << fixed << setprecision(0) << left;
    cout << setw(11) << "" << setw(W) << "W" << setw(W) << "L" << setw(W) << "T" << setw(W) << "W/L" << endl;
    for(int i = 0 ; i < leader[0].getSize() ; i++)
    {
        for(int j = i + 1 ; j <= leader[0].getSize() ; j++)
        {
            if(leader[i].getWL() < leader[j].getWL())
            {
                Leader *temp = new Leader[1];
                temp[0].setNme(leader[j].getNme());
                leader[j].setNme(leader[i].getNme());
                leader[i].setNme(temp[0].getNme());
                temp[0].setWin(leader[j].getWin());
                leader[j].setWin(leader[i].getWin());
                leader[i].setWin(temp[0].getWin());
                temp[0].setLoss(leader[j].getLoss());
                leader[j].setLoss(leader[i].getLoss());
                leader[i].setLoss(temp[0].getLoss());
                temp[0].setTie(leader[j].getTie());
                leader[j].setTie(leader[i].getTie());
                leader[i].setTie(temp[0].getTie());
                temp[0].setWL(leader[j].getWL());
                leader[j].setWL(leader[i].getWL());
                leader[i].setWL(temp[0].getWL());
                
                delete []temp;
            }
        }
    }
    
    for(int i = 0 ; i <= leader[0].getSize() ; i++)
    {
        cout << setw(11) << leader[i].getNme() << setw(W) << leader[i].getWin() << setw(W) << leader[i].getLoss()
             << setw(W) << leader[i].getTie() << leader[i].getWL() << "%" << endl;
    }
    cout << "--------------------------------" << endl;
    
    //Arranges players by W/L %, outputs leaderboard
}
void getName(Leader leader[])
{
    string temp, temp2;
    bool found = false, again = true;
    int indx;
    long locate;
    int win, loss, tie;
    fstream data;
    cout << "Please enter your first name. Max 10 characters. Do not start with a number." << endl;
    cin.ignore();
    while(again)
    {
        try
        {
            getline(cin, temp);
            check(temp);
            again = false;
        }
        catch(string error)
        {
            cout << endl << error << endl;
        }
    }
    data.open("Data.dat" , ios::in);
    for(int i = 0 ; i < leader[0].getSize() ; i++)
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            data >> temp2;
            if(temp2 == temp)
            {
                found = true;
                locate = data.tellg() - temp.size();
                indx = i;
                leader[0].foundNm(locate, indx, found);
            }
        }
    }
    data.close();
    if(found == false)
    {
        indx = leader[0].getSize();
        
        win = loss = tie = 0;
        leader[indx].newName(temp, indx, win, loss, tie, found);
        leader[0].setIndx(indx);
    }
    cout << endl;
    
    //Gets name of player, checks if it's in file
}
template <class T>
void ratio(T leader[])
{
    fstream winLoss;
    winLoss.open("WinLoss.dat", ios::out | ios::binary);
    
    winLoss << fixed << setprecision(0);
            
    if(leader[0].getFnd() == true)
        leader[0].decSize();
    
    for(int i = 0 ; i <= leader[0].getSize(); i++)
    {
        if(leader[i].getWin() != 0 && leader[i].getLoss() != 0)
            leader[i].setWL();
        
        int temp = leader[i].getWL();
        winLoss.write(reinterpret_cast<char *>(&temp), sizeof(temp));
        if(i != leader[0].getSize())
            winLoss << endl;
    }
    
    winLoss.close();
    
    //Calculates W/L % for each player, outputs to file
}
void result(Player player[], Leader leader[])
{
    int outcome, indx;
    static Output temp;
    
    if(player[PLAYER].getTot() > 21)
        outcome = 1;
    else if(player[DEALER].getTot() > 21)
        outcome = 2;
    else if(player[PLAYER].getTot() == player[DEALER].getTot())
        outcome = 3;
    else if(player[DEALER].getTot() > player[PLAYER].getTot())
        outcome = 4; 
    else
        outcome = 5;
    
    indx = leader[0].getIndx();
      
    if(outcome == 2 || outcome == 5)
        ++leader[indx];
    else if(outcome == 1 || outcome == 4)
        --leader[indx];
    else
        leader[indx] += 1;
    
    temp.resOut(outcome);
    
    //Determines result
}
void write(Leader leader[])
{
    fstream data;
    data.open("Data.dat", ios::in | ios::out);
    
    if(leader[0].getFnd() == false)
        data.seekp(0L , ios::end);
    else
        data.seekp(leader[0].getLoc(), ios::beg);
    
    data << leader[leader[0].getIndx()].getNme() << " ";
    data << leader[leader[0].getIndx()].getWin() << " ";
    data << leader[leader[0].getIndx()].getLoss() << " ";
    data << leader[leader[0].getIndx()].getTie() << endl;
    
    data.close();
    
    //Writes players name/wins/losses/ties to file
}