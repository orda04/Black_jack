#include <iostream>
#include <string>
#include<vector>
#include"black_jack.h"

using namespace std;

int main()
{
  cout<<"\t\t Welcome to BlackJAck\n\n";

  int numPlayers=0;
  while(numPlayers<1||numPlayers>7)
  {
   cout<<"How many players(1-7): ";
   cin>>numPlayers;
  }
vector<string> names;
string name;
for(int i=0;i<numPlayers;++i)
{
 cout<<"Enter Player Name: ";
 cin>>name;
 names.push_back(name);
}
cout<<endl;
Game aGame(names);
char again='y';
while (again != 'n' && again != 'N')
    {
      aGame.Play();
      cout<<"\nDo You want to play again (Y/N):";
      cin>>again;
    }
    return 0;
}
