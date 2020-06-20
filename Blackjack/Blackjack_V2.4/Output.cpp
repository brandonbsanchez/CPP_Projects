#include <iostream>
using namespace std;

#include "Output.h"

char Output::playAgn()
{ 
    char play;
    
    cout << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Would you like to play again? Type 'y' or 'n'." << endl;
    cin >> play;
    cout << endl;
    
    while(play != 'Y' && play != 'y' && play != 'N' && play != 'n')
    {
        cout << "Invalid Input. Type 'y' or 'n'." << endl;
        cin >> play;
        cout << endl;
    }
    
    return play;
    
   //Asks user if they want to play again, returns choice
}
void Output::initTot()
{
    cout << "--------------" << endl;
    cout << "Initial Totals" << endl;
    cout << "--------------" << endl;
    
    //Initial totals output
}
void Output::menu()
{
    cout << "-------------" << endl;
    cout << "~ Blackjack ~" << endl;
    cout << "-------------" << endl << endl;
    cout << "Please select from the following menu." << endl;
    cout << "1. Play the Game" << endl;
    cout << "2. Display the Rules" << endl;
    
    //Initial menu output
}
void Output::newCrd()
{
    cout << endl;
    cout << "---------------------" << endl;
    cout << "New Card / New Total" << endl;
    cout << "---------------------" << endl;
    
    //New card output
}
void Output::prompt()
{
    int choice;
    
    cin >> choice;
    while((choice != 1) && (choice != 2))
    {
        cin.clear();
        cin.ignore();
        cout << endl << "Invalid Input. Please type '1' or '2'." << endl;
        cin >> choice;
    }
    cout << endl;
    if(choice == 2)
        rules();
   
    //Player chooses whether they want to see rules or not
}
void Output::resOut(int outcome)
{
    cout << endl;
    switch(outcome)
    {
        case 1: cout << "Bust! You lost. Better luck next time." << endl;
        break;
        case 2: cout << "Dealer busts. Congratulations you won!" << endl;
        break;
        case 3: cout << "Same total. Tie." << endl;
        break;
        case 4: cout << "Dealer has the greater total. You lost. Better luck next time." << endl;
        break;
        case 5: cout << "Player has the greater total. Congratulations you won!" << endl; 
    }
    
    //Outputs result
}
void Output::rules()
{
    cout << "----------------------" << endl;
    cout << "~ Rules of BlackJack ~" << endl;
    cout << "----------------------" << endl;
    cout << "1. The game is played with a random number standard 52-card decks (No jokers)." << endl;
    cout << "2. The goal of the game is to have more points than the dealer but not exceed 21 points." << endl;
    cout << "3. If either the player or dealer exceeds 21 points they 'bust' or lose the game." << endl;
    cout << "4. The number on the card is the value in the game." << endl;
    cout << "5. Face cards are worth 10 points and aces are worth 1 or 11." << endl;
    cout << "6. The player and the dealer are both given 2 cards each." << endl;
    cout << "7. At first the dealer only shows one card." << endl;
    cout << "8. The player can either choose to stay (add no cards) or hit (add a card)." << endl;
    cout << "9. After the player stays the dealer shows their 2nd card." << endl;
    cout << "10. If the dealer has 16 points or less, he draws until he busts or exceeds 16 points." << endl;
    cout << "11. If no busts occur, the player wins with higher points than the dealer or loses with lower points than the dealer." << endl;
    cout << "12. Same points = draw." << endl;
    cout << "13. No doubles or splits." << endl << endl;
    
    //Rules for blackjack
}
void Output::totCrd()
{
    cout << "------------" << endl;
    cout << "Card History" << endl;
    cout << "------------" << endl;
    
    //Card history
}