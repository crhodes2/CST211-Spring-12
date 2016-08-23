#include "Deck.h"


Deck::Deck()
{

}

Deck::~Deck()
{

}

void Deck::SingleDeck()
{
	Purge();
	m_cards.reserve(52);
	for(int suit = 0; suit < Card::SUIT_COUNT; ++suit){
		for(int rank = 0; rank < Card::RANK_COUNT; ++rank){
			m_cards.push_back(Card(static_cast<Card::SUIT>(suit), static_cast<Card::RANK>(rank)));
		}
	}
}

unsigned RandomNum(int n)
{
	static bool seeded = false;
	if(!seeded)
	{
		srand(static_cast<unsigned>(time(0)));
		seeded = true;
	}
	return rand() % n;
}


void Deck::Shuffle()
{
	std::random_shuffle(m_cards.begin(), m_cards.end(), RandomNum);
}