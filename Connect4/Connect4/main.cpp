/* 
* File:   main.cpp
* Author: Brandon Sanchez
* Created on December 9, 2019, 7:38 PM
* Purpose: Connect 4 Game
*/

#include <algorithm> //Sort STL function
#include <cctype> //Isdigit function
#include <cstdlib> //Random Number Generator
#include <ctime> //Time function
#include <fstream> //File IO
#include <iomanip> //Formatting
#include <iostream> //Input/Output
#include <iterator> //STL iterators
#include <list> //STL list
#include <map> //STL map
#include <queue> //STL queue
#include <set> //STL set
#include <string> //String
#include <stack> //STL stack
#include <vector> //STL vector
using namespace std;

#include "LinkedListTemplate.h" //Linked List
#include "Tree.h" //Tree
#include "Node.h" //Node

enum Board
{
    N = 0, //NONE
    P = 1, //PLAYER
    C = 2, //COMPUTER
    T = 3 //TIE
};

/*
struct Record //Holds player stats
{
    set<int> win = {0}; //Wins by player
    set<int> loss = {0}; //Losses by player
    set<int> tie = {0}; //Ties by player
    float winLoss; //Win/Loss % by player
};
*/
LinkedList<string> **initList(int); //Initializes list used for hash
list<int> fillList(const int); //Fills rows with 0
bool check(list<list<int> >, int); //Checks if column is full
bool compare(const pair<string,Record>&, const pair<string,Record>&); //Used for sorting of pairs
bool nameFound(LinkedList<string> **, int, string); //See if name is found in file
bool playAgn(); //Prompts user if they want to play again
int checkWin(list<list<int> >, int, bool&, int&); //Checks to see if player/computer won or tied after every move
int diagCheck(list<list<int> >, int); //Checks diagonal win
int horCheck(list<list<int> >, bool&, int&); //Checks horizontal win
int prompt(bool &done); //Prompts user which column to place their piece
int tieCheck(list<list<int> >, int); //Checks for tie
int vertCheck(list<list<int> >, int, bool&, int&); //Checks for vertical win
string getName(); //Gets the name of user
void fillBoard(list<list<int> >&, const int, const int); //Fills board with 0's, AKA blank
void fillHash(LinkedList<string> **, vector<string>); //Fills hash into list
void findName(string,Record&); //Sees if player is in file, updates record if true
void fillNameArr(vector<string>&); //Fills name array for hash
void fillStats(int[], const int); //Initializes stats array
void fullOut(); //Outputs column is full
void outInit(); //Outputs game title
void outLeader2(queue<pair<string,Record>>); //Outputs the leaderboard
void outWin(int); //Output win result
void place(list<list<int> >&, int, int); //Places the piece for player/computer
void playHis(Record); //Outputs player history
void printBoard(list<list<int> >, const int); //Prints the entire board
void printNList(list<list<int> >); //Prints each column
void readFile(map<string,Record>&, string, Record); //Reads players from file
void recursSort(vector<pair<string,Record>>&, vector<pair<string,Record>>::iterator); //Sorts the vector leaderboard
void refill(list<list<int> >&); //Resets board back to blank after each game
void result(Record&, int); //Updates player history
void rules(); //Outputs rules of Connect 4
void sort(map<string,Record>, vector<pair<string,Record>>&); //Converts map to vector, calls recursive sort
void toStack(vector<pair<string,Record>>, stack<pair<string,Record>>&); //Converts vector to stack
void toQueue(stack<pair<string,Record>>, queue<pair<string,Record>>&); //Converts stack to queue
void inStats(LinkedList<string> **, int[] ,int); //Inputs stats into stats array
void print(int, int); //Used to troubleshoot hash

        
unsigned int PhoneHash(const char*, unsigned int);

int main()
{
    srand(static_cast<unsigned int>(time(0))); //Set random number seed
    
    const int ROW = 6, //Rows on board
              COL = 7; //Columns on board
    bool done = false, //If player wants to exit
         outBnd = false, //If player selects # not on col or full col
         three = false; //True if player gets 3 in a row
    int choice, //Choice of column
        compCol, //Computer column choice
        outcome, //Who won/loss or tie
        stop, //Column computer should
        prev = 100; //Previous column to stop, set to 100 to it won't trigger at first
    string name; //Holds player name
    Record record; //Holds player history
    
    list<int> sList; //Rows of ints
    list<list<int> > nList; //Columns of lists
    map<string,Record> leader; //Map of leaderboard
    stack<pair<string,Record>> sLeader; //Stack leaderboard
    queue<pair<string,Record>> qLeader; //Queue leaderboard
    vector<pair<string,Record>> sorted; //Vector leaderboard to sort
    
    fillBoard(nList, COL, ROW); //Fills board with 0's
    outInit(); //Outputs title
    name = getName(); //Gets player name
    findName(name, record); //Updates player history if name found
    rules(); //Outputs rules
    
    do
    {
        printBoard(nList, COL); //Prints board
        choice = prompt(done) - 1; //Gets user choice of column
        if(!done) //If user didn't exit
        {
            outBnd = check(nList, choice); //Checks if choice column is full
            while(outBnd) //Loops user to get valid column if full
            {
                fullOut(); //Outputs column is full
                choice = prompt(done) - 1;
                if(!done)
                    outBnd = check(nList, choice);
            }
            
            if(!done) //If user didn't exit
            {
                place(nList, choice, P); //Places piece in column user chose
                outcome = checkWin(nList, COL, three, stop); //Checks if anybody won
                if(outcome == N) //If nobody has won yet
                {
                    if(three && prev != (stop + 1))
                    {
                        compCol = stop + 1;
                        prev = compCol;
                        three = false;
                        outBnd = check(nList, compCol); //Checks if column is full
                        while(outBnd) //Computer chooses new column if invalid
                        {
                            compCol = rand()%7;
                            outBnd = check(nList, compCol);
                        }
                    }
                    else
                    {
                        compCol = rand()%7; //Computer chooses column
                        outBnd = check(nList, compCol); //Checks if column is full
                    }
                    
                    while(outBnd) //Computer chooses new column if invalid
                    {
                        compCol = rand()%7;
                        outBnd = check(nList, compCol);
                    }
                    place(nList, compCol, C); //Places computer piece
                    outcome = checkWin(nList, COL, three, stop); //Checks if anybody won
                }
                
                if(outcome != N) //If somebody has won
                {
                    printBoard(nList, COL); //Displays board
                    outWin(outcome); //Outputs who won
                    result(record, outcome); //Updates player history
                    playHis(record); //Outputs player history
                    done = playAgn(); //Prompts user to play again
                    if(!done) //If player wants to play again
                    {
                        refill(nList); //Reset board
                        prev = 100;
                    }
                }
            }
        }
    }while(!done); //While player wants to keep playing
    
    readFile(leader, name, record); //Reads players from file
    sort(leader, sorted); //Sorts the leaderboard, converts map to vector
    toStack(sorted, sLeader); //Converts vector to stack
    toQueue(sLeader, qLeader); //Converts stack to queue
    outLeader2(qLeader); //Outputs leaderboard as queue
    
    return 0; //Run successful
}

LinkedList<string> **initList(int size)
{
    LinkedList<string> **link = new LinkedList<string>*[size];
    
    for(int i = 0 ; i < size ; i++)
        link[i] = new LinkedList<string>(" ");
   
    return link;
}
list<int> fillList(const int COL)
{
    list<int> sList; 
    
    for(int i = 0 ; i < COL ; i++)
    {
        sList.push_back(0);
    }
    
    return sList;
}
bool check(list<list<int> > nList, int col)
{
    list<list<int> >::iterator nItr;
    
    for(nItr = nList.begin() ; nItr != nList.end() ; nItr++)
    {
        list<int>::iterator sItr;
        list<int>& sPtr = *nItr;
        sItr = sPtr.begin();
        advance(sItr, col);
        
        if(*sItr == 0)
            return false;
    }
    
    return true;
}
bool compare(const pair<string,Record> &i, const pair<string,Record> &j)
{
      return (i.second.winLoss < j.second.winLoss);
}
bool nameFound(LinkedList<string> **list, int size, string name) 
{
    unsigned int temp = PhoneHash(name.c_str(), name.length());
    
    if(list[temp % size]->findLst(name) == -1)
        return false;
    else
        return true;
}
bool playAgn()
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
    
    if(play == 'y' || play == 'Y')
        return false;
    else
        return true;
}
int checkWin(list<list<int> > nList, int COL, bool &three, int &stop)
{
    int val = N;
    val = horCheck(nList,three,stop);
    
    if(val != N)
        return val;  
    
    val = vertCheck(nList, COL, three, stop);
    
    if(val != N)
        return val;
    
    val = diagCheck(nList, COL);
    
    if(val != N)
        return val;
    
    val = tieCheck(nList, COL);
    
    return val;
}
int diagCheck(list<list<int> > nList, int COL)
{
    list<list<int> >::iterator nItr;
    int pCount, cCount, j;
    
    for(int k = 0 ; k < COL - 1 ; k++)
    {
        for(int i = 0 ; i < COL - 1 ; i++)
        {
            j = pCount = cCount = 0;
            nItr = nList.begin();

            for(advance(nItr, i) ; nItr != nList.end() ; nItr++, j++)
            {
                list<int>::iterator sItr;
                list<int>& sPtr = *nItr;
                sItr = sPtr.begin();
                advance(sItr,j);
                advance(sItr, k);

                if(*sItr == P)
                {
                    pCount++;
                    cCount = 0;
                }
                else if(*sItr == C)
                {
                    cCount++;
                    pCount = 0;
                }
                else
                    pCount = cCount = 0;
                
                if(pCount >= 4)
                    return P;
                else if(cCount >= 4)
                    return C;
            }  
        }
    }
    
    for(int k = COL - 1 ; k > 0 ; k--)
    {
        for(int i = 0 ; i < COL - 1 ; i++)
        {
            pCount = cCount = 0;
            j = k;
            nItr = nList.begin();

            for(advance(nItr, i) ; nItr != nList.end() ; nItr++, j--)
            {
                list<int>::iterator sItr;
                list<int>& sPtr = *nItr;
                sItr = sPtr.begin();
                advance(sItr, j);
                advance(sItr, k);

                if(*sItr == P)
                {
                    pCount++;
                    cCount = 0;
                }
                else if(*sItr == C)
                {
                    cCount++;
                    pCount = 0;
                }
                else
                    pCount = cCount = 0;

                if(pCount >= 4)
                    return P;
                else if(cCount >= 4)
                    return C;
            }  
        }
    }
    
    return N;
}
int horCheck(list<list<int> > nList, bool &three, int &stop)
{
    list<list<int> >::iterator nItr;
    int pCount, cCount;
    
    for(nItr = nList.begin() ; nItr != nList.end() ; nItr++)
    {
        list<int>::iterator sItr;
        list<int>& sPtr = *nItr;
        pCount = cCount = 0;
        int j = 0;
        
        for(sItr = sPtr.begin() ; sItr != sPtr.end() ; sItr++, j++)
        {
            if(*sItr == P)
            {
                pCount++;
                cCount = 0;
            }
            else if(*sItr == C)
            {
                cCount++;
                pCount = 0;
            }
            else
                pCount = cCount = 0;
            
            if(pCount == 3)
            {
                three = true;
                stop = j;
            }
            if(pCount == 4)
                return P;
            else if(cCount == 4)
                return C;     
        }
    }
    
    return N;
}
int prompt(bool &done)
{
    int choice;
    
    cout << endl << "Which column would you like to place your piece? Type 0 to exit program." << endl;
    cin >> choice;
    
    while(choice < 0 || choice > 7)
    {
        cin.clear();
        cin.ignore();
        cout << endl << "Invalid input. Only integers 0-7. Please try again." << endl;
        cin >> choice;
    }
    
    if(choice == 0)
        done = true;
    
    cout << endl;
    
    return choice;
}
int tieCheck(list<list<int> > nList, int COL)
{
    list<list<int> >::iterator nItr;
    int count = 0;
    
    for(nItr = nList.begin() ; nItr != nList.end() ; nItr++)
    {
        list<int>::iterator sItr;
        list<int>& sPtr = *nItr;
        
        for(sItr = sPtr.begin() ; sItr != sPtr.end() ; sItr++)
        {
            if(*sItr == P || *sItr == C)
                count++;
        }
    }
    
    if(count == 42)
        return T;
    else
        return N;
}
int vertCheck(list<list<int> > nList, int COL, bool &three, int &stop)
{
    list<list<int> >::iterator nItr;
    int pCount, cCount;
    
    for(int i = 0 ; i < COL ; i++)
    {
        pCount = cCount = 0;
        
        for(nItr = nList.begin() ; nItr != nList.end() ; nItr++)
        {
            list<int>::iterator sItr;
            list<int>& sPtr = *nItr;
            sItr = sPtr.begin();
            advance(sItr, i);         
            
            if(*sItr == P)
            {
                pCount++;
                cCount = 0;
            }
            else if(*sItr == C)
            {
                cCount++;
                pCount = 0;
            }
            else
                pCount = cCount = 0;
            
            if(pCount == 3)
            {
                stop = i - 1;
                three = true;
            }
            
            if(pCount >= 4)
                return P;
            else if(cCount >= 4)
                return C;
        }    
    }
    
    return N;
}
string getName()
{
    string name;
    cout << "Please enter your first name. Max 10 characters. Do not start with a number." << endl;
    cin >> name;
    
    while(name.size() > 10 || isdigit(name[0]))
    {
        cout << endl << "Invalid input. Please try again." << endl;
        cin >> name;
    }
    
    return name;
}
void fillBoard(list<list<int> >& nList, const int COL, const int ROW)
{
    list<int> sList = fillList(COL);
    
    for(int i = 0 ; i < ROW ; i++)
    {
        nList.push_back(sList);
    }
}
void fillHash(LinkedList<string>** link, vector<string> names)
{
    unsigned int temp;
    
    for(int i = 0 ; i < names.size() ; i++)
    {
        temp = PhoneHash(names[i].c_str(), names[i].length());
        link[temp % (names.size())]->addLst(names[i]);
    }
}
void fillNameArr(vector<string> &names)
{   
    ifstream inFile;
    inFile.open("Data.dat");
    string temp;
    
    while(inFile >> temp)
    {
        names.push_back(temp);
        inFile >> temp;
        inFile >> temp;
        inFile >> temp;
    }
    /*
    for(int i = 0 ; i < names.size() ; i++)
        cout << names[i] << endl;
    */
    inFile.close();
}
void fillStats(int array[], const int size)
{
    for(int i = 0 ; i < size ; i++)
        array[i] = 0;
}
void inStats(LinkedList<string> **link, int array[], int size)
{
    for(int i = 0 ; i < size ; i++)
        array[link[i]->getSize()]++;
}
void print(int array[], int num)
{
    int total = 0 ;
    
    for(int i = 0 ; i < num ; i++)
    {
        total += array[i];
        cout << i + 1 << ": " << array[i] << endl;
    }
    
    cout << endl << "Total: " << total << endl;
}
void findName(string name, Record &record)
{
    ifstream inFile;
    inFile.open("Data.dat");
    string temp;
    int win = 0, loss = 0, tie = 0, sSize = 11;
    int stats[sSize];
    LinkedList<string> **link;
    vector<string> names;
    
    fillNameArr(names);
    fillStats(stats, sSize);
    link = initList(names.size());
    fillHash(link, names);
    inStats(link, stats, names.size());
    //print(stats, sSize);
    
    if(nameFound(link, names.size(), name))
    {
        while(inFile >> temp)
        {
                if(temp == name)
                {
                    inFile >> win;
                    if(win != 0)
                        record.win.insert(win);
                    inFile >> loss;
                    if(loss != 0)
                        record.loss.insert(loss);
                    inFile >> tie;
                    if(tie != 0)
                        record.tie.insert(tie);
                }
        }
    }
    
    inFile.close();
}
void fullOut()
{
    cout << "Column is full! Please select another column.";
}
void outInit()
{
    cout << "---------------" << endl;
    cout << " ~ Connect 4 ~ " << endl;
    cout << "---------------" << endl << endl;
}
void outLeader2(queue<pair<string,Record>> qLeader)
{
    const int W = 4;
    
    cout << "--------------------------------" << endl;
    cout << "     Leaderboard (By W/L %)     " << endl;
    cout << "--------------------------------" << endl;
    cout << fixed << setprecision(0) << left;
    cout << setw(11) << "" << setw(W) << "W" << setw(W) << "L" << setw(W) << "T" << setw(W) << "W/L" << endl;
    
    int size = qLeader.size();
    
    Tree* tree = new Tree();
    
    for(int i = 0 ; i < size ; i++)
    {
        pair<string,Record> temp = qLeader.front();
        //cout << setw(11) << temp.first;
        
        tree->insert(temp);
        /*
        Record& ptr = temp.second;
        set<int>& ptr2 = ptr.win;
        set<int>::iterator itr;

        itr = --ptr2.end();
        cout << setw(W) << *itr;
        ptr2 = ptr.loss;
        itr = --ptr2.end();
        cout << setw(W) << *itr;
        ptr2 = ptr.tie;
        itr = --ptr2.end();
        cout << setw(W) << *itr;
        cout << temp.second.winLoss * 100 << "%" << endl;
        */
        qLeader.pop();
    }
    
    tree->inorder();
}
void outWin(int win)
{
    cout << "-----------------------------" << endl;
    
    if(win == P)
        cout << "Player wins!" << endl;
    else if(win == C)
        cout << "Computer wins!" << endl;
    else if(win == T)
        cout << "Tie!" << endl;
    
    cout << "Press enter to see Player History." << endl;
    cin.get();
    cin.ignore();
}
void place(list<list<int> >& nList, int col, int side)
{
    list<list<int> >::iterator nItr;
    
    for(nItr = --nList.end() ; nItr != --nList.begin() ; nItr--)
    {
        list<int>::iterator sItr;
        list<int>& sPtr = *nItr;
      
        sItr = sPtr.begin();
        advance(sItr, col);
        
        if(*sItr == 0)
        {
           *sItr = side;
           break;
        }
    }  
}
void playHis(Record record)
{
    set<int>::iterator wItr = --record.win.end(), lItr = --record.loss.end(), tItr = --record.tie.end();
    
    cout << endl << "---------------" << endl;
    cout << "Player History" << endl;
    cout << "---------------" << endl;
    cout << "Wins:" << setw(3) << *wItr << endl;
    cout << "Losses:" << setw(3) << *lItr << endl;
    cout << "Ties:" << setw(3) << *tItr << endl;
}
void printBoard(list<list<int> > nList, const int COL)
{
    for(int i = 0 ; i < COL ; i++)
    {
        if(i == 0)
        {
            cout << "  " << i + 1;
        }
        else
        {
            cout << "   " << i + 1;
        }
    }   
    
    cout << endl;  
    printNList(nList);
}
void printNList(list<list<int> > nList)
{
    list<list<int> >::iterator nItr;
    
    for(nItr = nList.begin() ; nItr != nList.end() ; nItr++)
    {
        list<int>::iterator sItr;
        list<int>& sPtr = *nItr;
        
        cout << "|";
        for(sItr = sPtr.begin() ; sItr != sPtr.end() ; sItr++)
        {
            if(*sItr == 0)
            {
                cout << "   |";
            }
            else if(*sItr == 1)
            {
                cout << " X |";
            }
            else
            {
                cout << " O |";
            }
        }
        
        cout << endl;
    }
}
void readFile(map<string,Record>& leader, string name, Record pRecord)
{
    fstream inFile;
    inFile.open("Data.dat", ios::in);
    
    bool found = false;
    string temp1;
    int win, loss, tie, pos;
    
    while(inFile >> temp1)
    {
        Record record;
        if(temp1 == name)
        {
            pos = inFile.tellg();
            record = pRecord;
            inFile >> win;
            inFile >> loss;
            inFile >> tie;
            found = true;
        }
        else
        {
            inFile >> win;
            record.win.insert(win);
            inFile >> loss;
            record.loss.insert(loss);
            inFile >> tie;
            record.tie.insert(tie);
        }
        
        set<int>::iterator wItr = --record.win.end(), lItr = --record.loss.end(), tItr = --record.tie.end();
        
        if(win != 0 || loss != 0)
            record.winLoss = static_cast<float>(*wItr) / (*wItr + *lItr);
        else
            record.winLoss = 0;
            
        leader.insert(pair<string,Record>(temp1,record));
    }
    
    leader.insert(pair<string,Record>(name,pRecord));
    
    inFile.close();

    if(found)
    {
        inFile.open("Data.dat", ios::in | ios::out);
        inFile.seekp(pos - name.size(), ios::beg);
    }
    else
        inFile.open("Data.dat", ios::app);
    
    set<int>::iterator wItr = --pRecord.win.end(), lItr = --pRecord.loss.end(), tItr = --pRecord.tie.end();
    inFile << name << " " << *wItr << " " << *lItr << " " << *tItr << endl;
    
    inFile.close();
}
void recursSort(vector<pair<string,Record>> &sorted, vector<pair<string,Record>>::iterator itr1)
{
    if(itr1 == --sorted.end())
        return;
    
    vector<pair<string,Record>>::iterator itr2, tempItr, tempItr2;
    
    tempItr = itr1;
    itr2 == ++tempItr;
    for(itr2 = ++tempItr ; itr2 != sorted.end() ; itr2++)
    {
        if(itr1->second.winLoss > itr2->second.winLoss)
        {
            pair<string,Record> temp = *itr1;
            *itr1 = *itr2;
            *itr2 = temp;
        }

    }
    
    recursSort(sorted, ++itr1);
}
void refill(list<list<int> > &nList)
{
    list<list<int> >::iterator nItr;
    int count = 0;
    
    for(nItr = nList.begin() ; nItr != nList.end() ; nItr++)
    {
        list<int>::iterator sItr;
        list<int>& sPtr = *nItr;
        
        for(sItr = sPtr.begin() ; sItr != sPtr.end() ; sItr++)
            *sItr = 0;
    }
}
void result(Record &record, int outcome)
{
    int temp;
    set<int>::iterator wItr = --record.win.end(), lItr = --record.loss.end(), tItr = --record.tie.end();
    
    if(outcome == P)
    {
        temp = *wItr;
        record.win.insert(++temp);
    }
    else if(outcome == C)
    {
        temp = *lItr;
        record.loss.insert(++temp);
    }
    else
    {
        temp = *tItr;
        record.tie.insert(++temp);
    }
   
    wItr = --record.win.end(), lItr = --record.loss.end(), tItr = --record.tie.end();
    record.winLoss = static_cast<float>(*wItr) / (*wItr + *lItr + *tItr);
}
void rules()
{
    cout << endl << "Connect 4 pieces horizontally, diagonally, or vertically to win." << endl;
    cout << "Player = 'X' Computer = 'O'" << endl << endl; 
}
void sort(map<string,Record> leader, vector<pair<string,Record>> &sorted)
{
    copy(leader.begin(), leader.end(), back_inserter(sorted));
    const int W = 4;
    vector<pair<string,Record>>::iterator itr1 = sorted.begin(), itr2, tempItr, tempItr2;
    
    recursSort(sorted, itr1);
            
    /*
    for(itr1 = sorted.begin() ; itr1 != --sorted.end() ; itr1++)
    {
        tempItr = itr1;
                
        for(itr2 = ++tempItr ; itr2 != sorted.end() ; itr2++)
        {
            if(itr1->second.winLoss > itr2->second.winLoss)
            {
                cout << "First: " << itr1->first << itr1->second.winLoss << endl;
                cout << "Second: " << itr2->first << itr2->second.winLoss << endl;
                pair<string,Record> temp = *itr1;
                *itr1 = *itr2;
                *itr2 = temp;

                cout << "First:~ " << itr1->first << itr1->second.winLoss << endl;
                cout << "Second:~ " << itr2->first << itr2->second.winLoss << endl;
            }
            
        }
    }
    
    for(itr1 = sorted.begin() ; itr1 != sorted.end() ; itr1++)
    {
        pair<string,Record> temp = *itr1;
        cout << setw(11) << itr1->first;
        
        Record& ptr = temp.second;
        set<int>& ptr2 = ptr.win;
        set<int>::iterator itr;

        itr = --ptr2.end();
        cout << setw(W) << *itr;
        ptr2 = ptr.loss;
        itr = --ptr2.end();
        cout << setw(W) << *itr;
        ptr2 = ptr.tie;
        itr = --ptr2.end();
        cout << setw(W) << *itr;
        cout << setw(W) << fixed << setprecision(0) << temp.second.winLoss * 100 << "%" << endl;
    }
    */
    //sort(sorted.begin(), sorted.end(), compare);
}
void toStack(vector<pair<string,Record>> sorted, stack<pair<string,Record>> &sLeader)
{
    vector<pair<string,Record>>::iterator itr;
    
    for(itr = sorted.begin() ; itr != sorted.end() ; itr++)
        sLeader.push(*itr);
}
void toQueue(stack<pair<string,Record>> sLeader, queue<pair<string,Record>>& qLeader)
{
    int size = sLeader.size();
    
    for(int i = 0 ; i < size ; i++)
    {
        qLeader.push(sLeader.top());
        sLeader.pop();
    }
}
unsigned int PhoneHash(const char* str, unsigned int length) {
    unsigned int hash = 0;

    unsigned int (*swDtrmn)(int i, int number) = [](int i, int number) {
        unsigned int result = 0;
        switch (i) {
            case 0:
                result += number * 100;
                break;
            case 1:
                result += number * 10;
                break;
            case 2:
                result += number;
                break;
            default:
                cout << "out of bounds" << endl;
                break;
        }
        return result;
    };

    for (int i = 0; i < length; ++str, ++i) {
        switch (*str) {
            case 65:
            case 66:
            case 67:
                hash += swDtrmn(i, 2);
                break;
            case 68:
            case 69:
            case 70:
                hash += swDtrmn(i, 3);
                break;
            case 71:
            case 72:
            case 73:
                hash += swDtrmn(i, 4);
                break;
            case 74:
            case 75:
            case 76:
                hash += swDtrmn(i, 5);
                break;
            case 77:
            case 78:
            case 79:
                hash += swDtrmn(i, 6);
                break;
            case 80:
            case 81:
            case 82:
            case 83:
                hash += swDtrmn(i, 7);
                break;
            case 84:
            case 85:
            case 86:
                hash += swDtrmn(i, 8);
                break;
            case 87:
            case 88:
            case 89:
            case 90:
                hash += swDtrmn(i, 9);
                break;
            default:
                break;
        }
    }

    return hash;
}