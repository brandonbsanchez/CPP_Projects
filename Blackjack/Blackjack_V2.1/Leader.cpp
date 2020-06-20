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
Leader::~Leader()
{
    delete []hist;
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
    
        cout << found << endl;
    cout << name << endl;
    cout << indx << endl;
    cout << nSize << endl;
    cout << size << endl;
    cout << locate << endl;
    cout << hist->win << endl;
    cout << hist->loss << endl;
    cout << hist->tie << endl;
    
    cout << "---------------" << endl;
    cout << "Player History" << endl;
    cout << "---------------" << endl;
    cout << "Wins:" << setw(3) << hist->win << endl;
    cout << "Losses:" << setw(3) << hist->loss << endl;
    cout << "Ties:" << setw(3) << hist->tie << endl;
    
    //Outputs player's wins/losses/ties
}
