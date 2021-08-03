#include "black_jack.h"

Card::Card(rank r,suit s, bool ifu): m_Rank(r),m_Suit(s),m_IsFaceUp(ifu)
{}

int Card::GetValue() const
{
    int value =0;
    if(m_IsFaceUp)
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
    m_IsFaceUp=!(m_IsFaceUp);
}

ostream& operator<<(ostream& os, const Card& aCard)
{
    const string RANKS[]={"0","A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    const string SUITS[]={"c","d","h","s"};
    if (aCard.m_IsFaceUp)
    {
        os<<RANKS[aCard.m_IsFaceUp]<<SUITS[aCard.m_Suit];

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

GenericPlayer::GenericPlayer(const string& name) :m_Name(name)
{}
GenericPlayer::~GenericPlayer()
{}

bool GenericPlayer::IsBusted() const
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
Player::~Player()
{
    Clear();
}
bool Player::IsHitting() const
{
    cout << m_Name << ", do you want a hit? (Y/N): ";
    char response;
    cin >> response;
    return (response == 'y' || response == 'Y');
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


House::~House()
{}
bool House::IsHitting() const
{
    return (GetTotal() <= 16);
}

void House::FlipFirstCard()
{
    if (!(m_Cards.empty()))
    {
        m_Cards[0]->Flip();
    }
    else
    {
        cout << "No card to flip!\n";
    }
}

//--------------------------------------------------
Deck::Deck()
{
    m_Cards.reserve(52);
    Populate();
}
Deck::~Deck()
{}
void Deck::Populate()
{
    Clear();
    for(int s=Card::CLUBS;s<=Card::SPADES;++s)
    {
        for(int r=Card::ACE;r<=Card::KING;++r)
        {
            Add(new Card (static_cast<Card::rank>(r),static_cast<Card::suit>(s)));
        }
    }
}
void Deck::Shuffle()
{
    random_shuffle(m_Cards.begin(),m_Cards.end());
}
void Deck::Deal(Hand &aHand)
{
    if(!m_Cards.empty())
    {
        aHand.Add(m_Cards.back());
        m_Cards.pop_back();
    }
    else
    {
        cout<<"Out of cards. Unable to deal";
    }
}
void Deck::AdditionalCards(GenericPlayer& aGenericPlayer)
{
    cout<<endl;
    while(!(aGenericPlayer.IsBusted())&&aGenericPlayer.IsHitting())
    {
        Deal(aGenericPlayer);
        cout<<aGenericPlayer<<endl;
        if(aGenericPlayer.IsBusted())
        {
            aGenericPlayer.Bust();
        }
    }
}
Game::Game( const vector<string>& names)
{
    // создает вектор игроков из вектора с именами
    vector<string>::const_iterator pName;

    for (pName = names.begin(); pName != names.end(); ++pName)
    {
       // m_Players.push_back(Player(*pName));//ругается именно на эту строку
    }
    // запускает генератор случайных чисел
    srand(static_cast<unsigned int>(time(0)));
    m_Deck.Populate();
    m_Deck.Shuffle();
}
Game::~Game()
{}
void Game::Play()
{
    // раздает каждому по две стартовые карты
    vector<Player>::iterator pPlayer;
    for (int i = 0; i < 2; ++i)
    {
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            m_Deck.Deal(*pPlayer);
        }
        m_Deck.Deal(m_House);
    }

    // прячет первую карту дилера
    m_House.FlipFirstCard();

    // открывает руки всех игроков
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        cout << *pPlayer << endl;
    }
    cout << m_House << endl;

    // раздает игрокам дополнительные карты
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        m_Deck.AdditionalCards(*pPlayer);
    }

    // показывает первую карту дилера
    m_House.FlipFirstCard();
    cout << endl << m_House;

    // раздает дилеру дополнительные карты
    m_Deck.AdditionalCards(m_House);

    if (m_House.IsBusted())
    {
        // все, кто остался в игре, побеждают
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            if (!(pPlayer->IsBusted()))
            {
                pPlayer->Win();
            }
        }
    }
    else
    {
        // сравнивает суммы очков всех оставшихся игроков с суммой очков дилера
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end();
             ++pPlayer)
        {
            if (!(pPlayer->IsBusted()))
            {
                if (pPlayer->GetTotal() > m_House.GetTotal())
                {
                    pPlayer->Win();
                }
                else if (pPlayer->GetTotal() < m_House.GetTotal())
                {
                    pPlayer->Lose();
                }
                else
                {
                    pPlayer->Push();
                }
            }
        }

    }

    // очищает руки всех игроков
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        pPlayer->Clear();
    }
    m_House.Clear();
}

