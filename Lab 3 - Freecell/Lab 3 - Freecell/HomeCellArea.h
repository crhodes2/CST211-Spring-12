#pragma once

#include "Card.h"
#include "Array.h"
#include "ArrayBasedStack.h"

class HomeCellArea
{
	private:
		Array<ArrayBasedStack<Card>> m_cards;

	public:
		friend class FreeCellGame;

		HomeCellArea(void);
		HomeCellArea(HomeCellArea const& copy);
		~HomeCellArea(void);

		HomeCellArea const& operator=(HomeCellArea const& rhs);

		void AddCard(Card card);

		void Purge(void);

		Card TopCard(unsigned col);
};

