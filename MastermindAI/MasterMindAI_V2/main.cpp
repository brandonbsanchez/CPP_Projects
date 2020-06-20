/*
    Dr. Mark E. Lehr
    CSC 7 Template for Mastermind AI
    December 1st, 2019
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

//Function Prototypes
string AI(int,int);
bool eval(string,string,int &,int &);
string set();

int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare variables
    string code,guess;  //code to break, and current guess
    int rr,rw;         //right digit in right place vs. wrong place
    int nGuess;         //number of guesses
    
    //Initialize Values
    nGuess=0;
    code=set();
    rr=rw=0;

    //Loop until solved and count to find solution
    do{
       nGuess++;
       guess=AI(rr,rw);
    }while(eval(code,guess,rr,rw));
    //Check evaluation
    cout<<nGuess<<" "<<code<<" "<<guess<<endl;
    guess=AI(rr,rw);
    
    /*cout<<code<<endl;
    for(int i=0;i<10000;i++){
        guess=AI(0,0);
        eval(code,guess,rr,rw);
        cout<<setw(5)<<code<<setw(5)<<guess
                <<setw(2)<<static_cast<int>(rr)
                <<setw(2)<<static_cast<int>(rw)<<endl;
    }*/
    
    //Exit the program
    return 0;
}

string AI(int rr,int rw){
    static const int SIZE = 10000, COLORS = 10;
    static int guessNum = 0; //Number of guesses
    static vector<string> guessesTotal; //Holds all 10,000 guesses
    static vector<string> prevGuesses; //Holds previous guesses
    static vector<bool> potentialIndex; //True = possible winning string, False = ruled out string
    static int rightColor[COLORS]; //Holds number of each color
    static int totalRR = 0; //Used to terminate guessing each color early
    static string sGuess = "0000"; //Holds the current guess
    
    if(guessNum == 0) //Fills guessesTotal vector
    {
        for(int i = 0 ; i < SIZE ; i++)
        {
            string temp = to_string(i);
            if(temp.size() < 4)
            {
                string zeros = "";

                for(int i = 0 ; i < 4 - temp.size() ; i++)
                    zeros += '0';

                temp = zeros + temp;
            }

            guessesTotal.push_back(temp);       
            potentialIndex.push_back(true);
        }
        prevGuesses.push_back(sGuess);
    }
    else
    {
        if(rr == 0 && rw == 0) //Eliminate all strings that match with completely wrong string
        {
            char digit = sGuess[0];

            for(int i = 0 ; i < SIZE ; i++)
            {
                if(potentialIndex[i] && guessesTotal[i].find(digit, 0) != string::npos)
                {
                    potentialIndex[i] = false;
                }
            }
        }
        prevGuesses.push_back(sGuess);
        
        if(guessNum <= 10) 
        {
            rightColor[guessNum - 1] = rr; //Holds number of each color
        }
        if(guessNum < 10)
        {
            totalRR += rr; //Running total
        }
        if(guessNum == 9) //To not guess 9999
        {
            rightColor[COLORS - 1] = 4 - totalRR;
            guessNum++;
        }
        if(totalRR == 4 && guessNum < 10) //Terminates adding sequence if all colors are found
        {
            for(int i = guessNum ; i < COLORS ; i++)
            {
                rightColor[i] = 0; //Fills rest of color numbers with 0
            }
            guessNum = 11;
        }
        if(guessNum < 10) //Guesses 0000-9999 unless terminated early
        {
            sGuess[0]++;
            sGuess[1]++;
            sGuess[2]++;
            sGuess[3]++;
        }
        if(guessNum == 10) //Eliminates combinations without right number of colors
        {
            for(int i = 0 ; i < SIZE ; i++)
            {
                if(potentialIndex[i])
                {
                    int tempColors[COLORS - 1];
                    bool match = true;
                    
                    for(int j = 0 ; j < COLORS - 1 ; j++)
                    {
                        tempColors[j] = 0;
                    }
                    
                    for(int j = 0 ; j < 4 ; j++)
                    {
                        int index = guessesTotal[i][j] - 48;
                        
                        tempColors[index]++;
                    }

                    for(int j = 0 ; j < COLORS - 1 ; j++)
                    {
                        if(rightColor[j] != tempColors[j])
                        {
                            match = false;
                        }
                    }

                    if(!match)
                    {
                        potentialIndex[i] = false;
                    }
                }
            }
        }
        if(guessNum == 11) //Eliminates combinations without right number of colors
        {
            for(int i = 0 ; i < SIZE ; i++)
            {
                if(potentialIndex[i])
                {
                    int tempColors[COLORS];
                    bool match = true;
                    
                    for(int j = 0 ; j < COLORS ; j++)
                    {
                        tempColors[j] = 0;
                    }
                    
                    for(int j = 0 ; j < 4 ; j++)
                    {
                        int index = guessesTotal[i][j] - 48;
                        
                        tempColors[index]++;
                    }

                    for(int j = 0 ; j < COLORS ; j++)
                    {
                        if(rightColor[j] != tempColors[j]) //Makes sure colors are correct numbers
                        {
                            match = false;
                        }
                    }

                    if(!match)
                    {
                        potentialIndex[i] = false;
                    }
                }
            }
        }

        if(guessNum >= 10) //Colors have all been guessed
        {
            if(rr != 0) //Atleast one position is right
            {
                for(int i = 0 ; i < SIZE ; i++)
                {
                    if(potentialIndex[i])
                    {
                        bool match = false;
                        
                        for(int j = 0 ; j < 4 ; j++)
                        {
                            if(sGuess[j] == guessesTotal[i][j])
                            {
                                match = true;
                            }
                        }
                        
                        if(!match) //If no matches for correct rr, eliminate
                        {
                            potentialIndex[i] = false;
                        }
                    }
                }
                for(int i = 0 ; i < SIZE ; i++)
                {
                    if(potentialIndex[i])
                    {
                        int matchCount = 0;
                        
                        for(int j = 0 ; j < 4 ; j++)
                        {
                            if(sGuess[j] == guessesTotal[i][j])
                            {
                                matchCount++;
                            }
                        }
                        
                        if(rr > matchCount)
                        {
                            potentialIndex[i] = false;
                        }
                    }
                }
            }
            else if(rr == 0) //None of the positions are right
            {
                for(int i = 0 ; i < SIZE ; i++)
                {
                    if(potentialIndex[i])
                    {
                        bool match = false;
                        
                        for(int j = 0 ; j < 4 ; j++)
                        {
                            if(sGuess[j] == guessesTotal[i][j])
                            {
                                potentialIndex[i] == false;
                            }
                        }
                    }
                }
            }
            for(int i = 0 ; i < SIZE ; i++) //Picks first potential guess in vector
            {
                if(potentialIndex[i])
                {
                    sGuess = guessesTotal[i];
                    potentialIndex[i] = false;
                    
                    guessNum++;
                    return sGuess;
                }
            }
        }
    }
    
    guessNum++;
    //Return the result
    return sGuess;
}

bool eval(string code,string guess,int &rr,int &rw){
    string check="    ";
    rr=0,rw=0;
    //Check how many are right place
    for(int i=0;i<code.length();i++){
        if(code[i]==guess[i]){
            rr++;
            check[i]='x';
            guess[i]='x';
        }
    }
    //Check how many are wrong place
    for(int j=0;j<code.length();j++){
        for(int i=0;i<code.length();i++){
            if((i!=j)&&(code[i]==guess[j])&&(check[i]==' ')){
                rw++;
                check[i]='x';
                break;
            }
        }
    }
    
    //Found or not
    if(rr==4)return false;
    return true;
}

string set(){
    string code="0000";
    for(int i=0;i<code.length();i++){
        code[i]=rand()%10+'0';
    }
    return code;
}