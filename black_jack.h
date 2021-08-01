#ifndef BLACK_JACK_H
#define BLACK_JACK_H
#include <iostream>
#include <string>
#include<vector>


using namespace std;


class Card// карта
{
   public:
     enum suit
     {CLUBS,
         DIAMONDS,
               HEARTS,
                  SPADES };
     enum rank
     {ACE=1,
         DOUBLE=2,
            TRIPLE=3,
               FOUR=4,
                  FIVE=5,
                     SIX=6,
                       SEVEN=7,
                          EIGHT=8,
                             NINE=9,
                                TEN=10,
                                   JACK=11,
                                      QUEEN=12,
                                         KING=13};

    Card(rank r=ACE,suit s=SPADES,bool ifu=true);


     int GetValue()const;
     void Flip();  //
     friend ostream& operator<<(ostream& os, const Card& aCard);

private:
   rank m_Rank;
   suit m_Suit;
   bool m_IsFaseUp;

};
class Hand  // коллекция карт на руках
{
public:

 Hand();
 virtual ~Hand();
 void Add(Card* pCard);
 void Clear();
 int GetTotal() const;

protected:
 vector <Card*> m_Cards;
};


class GenericPlayer:public Hand
{

 friend ostream& operator<<(ostream& os ,const GenericPlayer& aGenericPlayer);
public:
 GenericPlayer(const string& name="");

 virtual ~GenericPlayer();
 virtual bool IsHitting() const=0;
 bool IsBoosted() const;
 void Bust() const;
protected:
 string m_Name;
};
class Player:public GenericPlayer
{
public:
    Player(const string& name="");
    virtual ~Player();
    virtual bool IsHitting() const;
    void Win() const;
    void Lose() const;
    void Push() const;
};
class House:public GenericPlayer
{
  public:
    House(const string& name="House");
    virtual ~House();
    virtual bool IsHitting() const;
    void FlipFirstCard();
};
class Deck: public Hand
{
public:
    void Populate();
    void Shuffle();
    void Deal (Hand& aHand);
    void AdditionalCards(GenericPlayer aGenericPlayer);
};

class Game
{
 Deck m_Deck;
 //House m_House;
 vector<Player> m_players;    //vector<Player> m_players;???
public:
 void Play();
};

#endif // BLACK_JACK_H
