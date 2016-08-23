#pragma once

#include "Card.h"
#include "Array.h"
#include "Exception.h"

class FreeCellArea
{
	private:
		Array<Card> m_cards;
<<<<<<< .mine
		unsigned m_length;
=======
		unsigned m_numCards;
>>>>>>> .r308

	public:
		friend class FreeCellGame;

		FreeCellArea(void);
		FreeCellArea(FreeCellArea const& copy);
		~FreeCellArea(void);

		FreeCellArea const& operator=(FreeCellArea const& rhs);

		unsigned GetNum(void) const;
		unsigned GetRemaining(void) const;

<<<<<<< .mine
		void AddCard(Card card);
		Card PopCard();
		Card PeekCard();
=======
		void AddCard(Card card);
		Card PopCard(unsigned index);
>>>>>>> .r308
		Card PeekCard(unsigned index);

		Card GetCardAt(unsigned index);
		Card RemoveCardAt(unsigned index);

		void Clear();

		void Purge();
};

