#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Player.h"
#include "Output.h"
using namespace std;

Player::Player()
{
    ifstream inFile;
    inFile.open("Cards.txt"); 
    
    nameArr = new string*[ROW];
        for(int i = 0 ; i < ROW ; i++)
            nameArr[i] = new string[COL];
    
    for(int i = 0 ; i < COL ; i++)
        inFile >> nameArr[0][i];
    for(int i = 0 ; i < COL ; i++)
        inFile >> nameArr[1][i]; 
    
    inFile.close();
}
Player::~Player()
{
    for(int i = 0  ; i < ROW ; i++)
        delete []nameArr[i];
    
    delete []nameArr;
}
void Player::outDeal()
{
    int col = crdPlay(DEALER),
        indx = col - size + 1;
    
    cout << "Dealer Card " << indx << ": " << nameArr[0][name[col] - 1] << " of " << nameArr[1][suit[col] - 1] << " (" << val[col] << ")" << endl; 
    
    //Draws/Outputs dealer card
}
void Player::outPlay()
{
    int col = crdPlay(PLAYER),
        indx = col - size + 1;
    
    cout << "Player Card " << indx << ": " << nameArr[0][name[col] - 1] << " of " << nameArr[1][suit[col] - 1] << " (" << val[col] << ")" << endl; 
    
    //Draws/Outputs player card
}
int Player::crdPlay(int deck)
{
    int cName = nameVal(),
        cSuit = suitVal(),
        col;
    
    name.push_back(cName);
    suit.push_back(cSuit);
    val.push_back(cName);
    
    col = name.size() - 1;  
    
    if(val[col] > 10)
        val[col] = 10;
    else if(val[col] == 1 && deck == PLAYER)  
        val[col] = aceChce();
    else if(val[col] == 1 && deck == DEALER)
    {
        if(tot <= 10)
            val[col] = 11;
    }
    tot += val[col];
    
    return col;
    
    //Fills vector with card details when card is drawn
}
int Player::aceChce()
{
    int card;
    cout << endl << "You were dealt an Ace. Do you want it to be worth '1' or '11'?" << endl;
    cin >> card;
    cout << endl;
    
    while(card != 1 && card != 11)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input! Please select either '1' or '11'." << endl;
        cin >> card;
        cout << endl;
    }
    
    return card;
    
    //Player chooses their ace value, returns it's value
}
int Player::nameVal()
{
    const int MAX = 13, MIN = 1;
    int val = (rand() % (MAX - MIN + 1)) + MIN;
 
    return val;
    
    //Random number generator for card value
}
int Player::suitVal()
{
    const int MAX = 4, MIN = 1; 
    int val = (rand() % (MAX - MIN + 1)) + MIN;
    
    return val;
    
    //Random number generator for suit
}
void Player::aceChck()
{
    ace.ace1 = ace.ace11 = 0;
    for(int i = size ; i < name.size() ; i++)
    {
        if(val[i] == 1)
            ace.ace1++;
        if(val[i] == 11)
            ace.ace11++;
    }
    ace.aceCnt = ace.ace1 + ace.ace11;
    
    //Checks if deck contains aces
}
int Player::gtAce11()
{
    return ace.ace11;
}
bool Player::aceBust()
{
    Output temp;
    
    cout << endl << "Your ace value has been changed to '1' to prevent busting." << endl;
    for(int i = size ; i < name.size() ; i++)
    {
        if(val[i] == 11)
        {
            val[i] = 1;
            ace.ace11--;
            ace.ace1++;
            ace.aceCnt = ace.ace11 + ace.ace1;
            tot -= 10;
             
            temp.newCrd();
            cout << "Player Card " << i + 1 - size << ": " << nameArr[0][name[i] - 1] << " of " 
            << nameArr[1][suit[i] - 1] << " (" << val[i] << ")" << endl; 
            totPlay();
 
            return false;
        }  
    }
    /* Reduces ace value,
       changes counts,
       outputs the new card value*/
}
void Player::totDeal()
{
    cout << "Dealer Total: " << tot << endl;
    
    //Outputs dealer total
}
void Player::totPlay()
{
    cout << "Player Total: " << tot << endl;
    
    //Outputs player total
}
bool Player::hitFun()
{
    Output temp;
    bool bust = false;
    char hit;
    
    do
    {
        cout << endl << "Would you like to hit ('h') or stay ('s')?" << endl;
        cin >> hit;
        while(hit != 'h' && hit != 'H' && hit != 's' && hit != 'S')
        {
            cout << endl << "Invalid Input! Please type either 'h' or 's'." << endl;
            cin >> hit;
        }
        if(hit == 'h' || hit == 'H')
        {
            temp.newCrd();
            outPlay(); 
            totPlay();
        }
        if(tot > 21)
        {   
            aceChck();
            if(ace.ace11 > 0)
                bust = aceBust();
            else
                bust = true; 
        }
    }while((hit == 'h' || hit == 'H') && bust == false);
    
    return bust;
    
    //Keeps drawing cards until player stays or busts
}
void Player::dealDrw()
{
    Output temp;
    
    temp.dealCrd();
    while(tot < 17)
    {
        outDeal();
        if(tot > 21)
        {   
            aceChck();
            
            if(ace.ace11 > 0)
                aceDeal();
        }
    }
    cout << endl << "Press Enter to See Final Totals." << endl; 
    cin.ignore();
    cin.get();
    
    //Dealer drawing loop
}
void Player::aceDeal()
{   
    for(int i = size ; i < name.size() ; i++)
    {
        if(val[i] == 11)
        {
            val[i] = 1;
            ace.ace11--;
            ace.ace1++;
            ace.aceCnt = ace.ace11 + ace.ace1;
            tot -= 10;
        }  
    }
    
    //If dealer busts reduces ace value
}
void Player::pCards()
{
    for(int i = size; i < name.size() ; i++)
        cout << "Player Card " << i - size + 1 << ": " << nameArr[0][name[i] - 1] << " of " << nameArr[1][suit[i] - 1] << " (" << val[i] << ")" << endl; 
    
    //Outputs player card
}
void Player::dCards()
{ 
    for(int i = size ; i < name.size() ; i++)
        cout << "Dealer Card " << i - size + 1 << ": " << nameArr[0][name[i] - 1] << " of " << nameArr[1][suit[i] - 1] << " (" << val[i] << ")" << endl; 
    
    //Outputs dealer card
}
int Player::getTot()
{
    return tot;
}
void Player::reset()
{
    tot = 0;
    size = name.size();
    
    //Resets stats after each game
}