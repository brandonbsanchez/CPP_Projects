#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

#include "Player.h"
#include "Output.h"
#include "Leader.h"

enum Deck{DEALER, PLAYER}; //Differentiates dealer and player decks

Leader* getData(); //Gets data from file
void getName(Leader[]); //Gets name of player
void result(Player[], Leader[]); //Calculates final results of game
void ratio(Leader[]); //Deals with win/loss ratio
void write(Leader[]); //Writes to file
void finOut(Leader[]); //Outputs leaderboard
void freeMem(Leader[]); //Frees dynamically allocated memory

int main()
{
    srand(static_cast<unsigned int>(time(0))); //Set the random number seed
    
    const int ROW = 2, SIZE = 0;
    Player player[ROW];
    Leader *leader = nullptr;
    Output output;
    bool bust;
    char play;
    
    leader = getData();
    output.menu();
    output.prompt();
    getName(leader);
    do
    {
    output.initCrd();
    player[DEALER].outDeal();
    player[PLAYER].outPlay();
    player[PLAYER].outPlay();
    player[PLAYER].aceChck();
    if(player[PLAYER].gtAce11() == 2)
        player[PLAYER].aceBust();
    output.initTot();
    player[DEALER].totDeal();
    player[PLAYER].totPlay();
    bust = player[PLAYER].hitFun();
    if(bust == false)
    {
        player[DEALER].dealDrw();
        output.totCrd();
        player[DEALER].dCards();
        player[PLAYER].pCards();
        output.finTot();
        player[DEALER].totDeal();
        player[PLAYER].totPlay();
    }
    leader[leader[0].getIndx()].playHis(bust);
    result(player, leader);
    play = output.playAgn();
    player[DEALER].reset();
    player[PLAYER].reset();
    }while(play == 'y' || play == 'Y');
    ratio(leader);
    write(leader);
    finOut(leader);
    freeMem(leader);
    
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
void getName(Leader leader[])
{
    string temp, temp2;
    bool found = false;
    int indx;
    long locate;
    char *name;
    int win, loss, tie;
    fstream data;
    
    cout << "Please enter your first name. Max 10 characters. Do not start with a number." << endl;
    cin.ignore();
    getline(cin, temp);
    
    while(temp.size() > 10 || isdigit(temp[0]))
    {
        cout << endl;
        cout << "Invalid Input! Max 10 characters. Do not start with a number." << endl;
        getline(cin, temp);
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
                leader[0].foundNm(locate, indx);
            }
        }
    }
    data.close();
    
        
    if(found == false)
    {
        indx = leader[0].getSize();
        name = new char[temp.size() + 1];
        
        for(int i = 0 ; i < temp.size() + 1; i++)
            name[i] = temp[i];
        
        win = loss = tie = 0;
        
        leader[indx].newName(name, indx, win, loss, tie, found);
        
        delete []name;
    }
    cout << endl;

    //Gets name of player, checks if it's in file
}
void result(Player player[], Leader leader[])
{
    int outcome, indx;
    Output temp;
   
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
void ratio(Leader leader[])
{
    fstream winLoss;
    winLoss.open("WinLoss.dat", ios::out | ios::binary);
    
    winLoss << fixed << setprecision(0);
            
    if(leader[0].getFnd() == true)
        leader[0].decSize();
    
    for(int i = 0 ; i <= leader[0].getSize(); i++)
    {
        if(leader[i].getWin() == 0 && leader[i].getLoss() != 0)
            leader[i].setWL();
        
        int temp = leader[i].getWL();
        winLoss.write(reinterpret_cast<char *>(&temp), sizeof(temp));
        if(i != leader[0].getSize())
            winLoss << endl;
    }
    
    winLoss.close();
    
    //Calculates W/L % for each player, outputs to file
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
void freeMem(Leader leader[])
{
    delete []leader;

    //Frees allocated memory
}