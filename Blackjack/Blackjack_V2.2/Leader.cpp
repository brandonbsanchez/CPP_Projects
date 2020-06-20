#include <fstream>
#include <cstring>
#include <string>
#include <iomanip>
#include "Leader.h"
using namespace std;

Leader::Leader()
{
    hist = new Hist[2];
}
void Leader::fill(string temp, int w, int l, int t)
{ 
    hist->win = w;
    hist->loss = l;
    hist->tie = t;
    name = new char(temp.size());
        for(int j = 0 ; j < temp.size() ; j++)
        {
            name[j] = temp[j];
        }
}
void Leader::foundNm(long l, int i)
{
    locate = l;
    indx = i;
}
void Leader::setSize(int s)
{
    size = s;
}
int Leader::getSize()
{
    return size;
}
void Leader::newName(char n[], int i, int w, int l, int t, bool f)
{
    name = n;
    indx = i;
    hist->win = w;
    hist->loss = l;
    hist->tie = t;
    found = f;
}
Leader::Leader(const Leader &leader)
{
    hist = new Hist[2];
    found = leader.found;
    name = leader.name;
    indx = leader.indx;
    nSize = leader.nSize;
    size = leader.size;
    locate = leader.locate;
    hist->win = leader.hist->win;
    hist->loss = leader.hist->loss;
    hist->tie = leader.hist->tie;
}
Leader Leader::operator++()
{
    ++hist->win;
    
    return *this;
}
Leader Leader::operator--()
{
    --hist->loss;
    
    return *this;
}
Leader Leader::operator+=(int num)
{
    hist->tie += num;
    
    return *this;
}
int Leader::getIndx()
{
    return indx;
}
void Leader::playHis(bool bust)
{
    cout << endl << "Press Enter to See Player History." << endl;
    
    if(bust == true)
        cin.ignore();
    
    cin.get();
    
    cout << "---------------" << endl;
    cout << "Player History" << endl;
    cout << "---------------" << endl;
    cout << "Wins:" << setw(3) << hist->win << endl;
    cout << "Losses:" << setw(3) << hist->loss << endl;
    cout << "Ties:" << setw(3) << hist->tie << endl;
    
    //Outputs player's wins/losses/ties
}
bool Leader::getFnd()
{
    return found;
}
void Leader::decSize()
{
    size--;
}
int Leader::getWin()
{
    return hist->win;
}
int Leader::getLoss()
{
    return hist->loss;
}
void Leader::setWL()
{
    hist->winLoss = static_cast<float>(hist->win) / (hist->loss + hist->win);
    hist->winLoss *= 100;
}
int Leader::getWL()
{
    return hist->winLoss;
}
long Leader::getLoc()
{
    return locate;
}
char *Leader::getNme()
{
    return name;
}
int Leader::getTie()
{
    return hist->tie;
}
void Leader::setNme(char *n)
{
    name = n;
}
void Leader::setWin(int w)
{
    hist->win = w;
}
void Leader::setLoss(int l)
{
    hist->loss = l;
}
void Leader::setTie(int t)
{
    hist->tie = t;
}
void Leader::setWL(int wl)
{
    hist->winLoss = wl;
}