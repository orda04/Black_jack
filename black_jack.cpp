#include "black_jack.h"

Card::Card(rank r,suit s, bool ifu): m_Rank(r),m_Suit(s),m_IsFaseUp(ifu)
{}

int Card::GetValue() const
{
    int value =0;
    if(m_IsFaseUp)
    {
        value=m_Rank;

        if(value>10)
          {
             value=10;
          }
     }
    return value;
}

void Card::Flip()
{
    m_IsFaseUp=!(m_IsFaseUp);
}

ostream& operator<<(ostream& os, const Card& aCard)
{
    const string RANKS[]={"0","A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    const string SUITS[]={"c","d","h","s"};
    if (aCard.m_IsFaseUp)
    {
        os<<RANKS[aCard.m_IsFaseUp]<<SUITS[aCard.m_Suit];

    }
    else
    {
        os<<"XX";
    }
    return os;
}
//--------------------------------------------------
Hand::Hand()
{
    m_Cards.reserve(7);
}
Hand::~Hand()
{
    Clear();
}
void Hand::Add(Card* pCard)
{
    m_Cards.push_back(pCard);
}
void Hand::Clear()
{
 vector<Card*>::iterator iter=m_Cards.begin();
 for(iter =m_Cards.begin();iter!=m_Cards.end();++iter)
    {
     delete *iter;
     *iter=0;
    }
 m_Cards.clear();
}
int Hand::GetTotal() const
{
    if(m_Cards.empty())
    {
        return 0;
    }
    if(m_Cards[0]->GetValue()==0)
    {
        return 0;
    }
    int total = 0;
    vector<Card*>::const_iterator iter;
    for(iter=m_Cards.begin();iter!=m_Cards.end();++iter)
    {
        total+=(*iter)->GetValue();
    }
    bool containsAce=false;
    for(iter=m_Cards.begin();iter!=m_Cards.end();++iter)
    {
     if((*iter)->GetValue()==Card::ACE)
     {
         containsAce=true;
     }
    }
    if(containsAce&&total<=11)
    {
    total+=10;
    }
        return total;
}
//--------------------------------------------------

GenericPlayer::GenericPlayer(const string& name):m_Name(name)
{}
GenericPlayer::~GenericPlayer()
{}
bool GenericPlayer::IsBoosted() const
{
    return (GetTotal()>21);
}
void GenericPlayer::Bust() const
{
    cout<<"m_Name"<<" busts.\n";
}
ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer)
{
    os<<aGenericPlayer.m_Name<<":\t";
    vector<Card*>::const_iterator pCard;
    if(!aGenericPlayer.m_Cards.empty())
    {
        for(pCard=aGenericPlayer.m_Cards.begin();pCard!=aGenericPlayer.m_Cards.end();++pCard)
        {
            os<<*(*pCard)<<"\t";
        }
        if(aGenericPlayer.GetTotal()!=0)
        {
            cout<<"("<<aGenericPlayer.GetTotal()<<")";
        }
    }
    else
    {
        os<<"empty";
    }
    return os;
}
//--------------------------------------------------
bool Player::IsHitting() const
{
    cout<<m_Name<<", do you want a hit?(Y/N): ";
    char response;
    cin>>response;
    return(response=='y'||response=='Y');

}
void Player::Win() const
{
    cout<<m_Name<<" wins.\n";
}
void Player::Lose() const
{
   cout<<m_Name<<" loose.\n";
}
void Player::Push() const
{
   cout<<m_Name<<" pushes.\n";
}
//--------------------------------------------------
bool House::IsHitting() const
{
    return (GetTotal()<16);
}
void House::FlipFirstCard()
{
    if(!(m_Cards.empty()))
    {
        m_Cards[0]->Flip();//m_Cards[0].Flip();
    }
    else
    {
        cout<<"No card to flip!\n";
    }
}
