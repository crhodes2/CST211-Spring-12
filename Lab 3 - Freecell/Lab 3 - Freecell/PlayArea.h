#pragma once

#include "Card.h"
#include "Array.h"
#include "ListBasedStack.h"

class PlayArea
{
private:
	Array<ListBasedStack<Card>> m_cards;

public:
	friend class FreeCellGame;
	
	PlayArea(void);
	PlayArea(PlayArea const& copy);
	~PlayArea(void);

	PlayArea const& operator=(PlayArea const& rhs);

	void AddCard(Card card, unsigned col);
	Card PopCard(unsigned col);
	Card PeekCard(unsigned index);

	void Purge();
};

