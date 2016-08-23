#include "FreeCellArea.h"


FreeCellArea::FreeCellArea(void) : m_length(0)
	: m_numCards(0)
{
	m_cards.setLength(4);
	m_cards.setStartIndex(0);
}

<<<<<<< .mine
FreeCellArea::FreeCellArea(FreeCellArea const& copy) : m_cards(copy.m_cards), m_length(copy.m_length)
=======
FreeCellArea::FreeCellArea(FreeCellArea const& copy)
	: m_cards(copy.m_cards), m_numCards(copy.m_numCards)
>>>>>>> .r308
{

}

FreeCellArea::~FreeCellArea(void)
{
	Purge();
}

FreeCellArea const& FreeCellArea::operator=(FreeCellArea const& rhs)
{
	if(this != &rhs)
	{
		m_cards = rhs.m_cards;
		m_numCards = rhs.m_numCards;
	}
	m_length = rhs.m_length;
	return *this;
}

void FreeCellArea::AddCard(Card card)
{
	if( !GetRemaining() )
	{
		throw Exception("Cannot add card to Free Cell Area. It is full.");
	}

<<<<<<< .mine
	m_cards[m_length-1] = card;
	--m_length;
=======
	m_cards[m_numCards++] = card;
>>>>>>> .r308
}

Card FreeCellArea::PopCard()
{
<<<<<<< .mine
	if( m_cards[m_length-1].isBlank() )
=======
	if(!m_numCards)
>>>>>>> .r308
	{
		throw Exception("Can't pop from empty free cell area.");
	}
	Card poppedCard = m_cards[index];
	for(unsigned i = index; index < m_numCards-1; ++i)
	{
		m_cards[index] = m_cards[index+1];
	}
	m_cards[m_numCards-1] = Card(); // blank out the last card
	m_numCards--;

<<<<<<< .mine
	Card returnedCard = m_cards[m_length-1];
	m_cards[m_length-1] = Card(); // blank card in its place
	--m_length;
	return returnedCard;
=======
	return poppedCard;
>>>>>>> .r308
}

<<<<<<< .mine
Card FreeCellArea::PeekCard()
=======
Card FreeCellArea::PeekCard(unsigned index)
>>>>>>> .r308
{
<<<<<<< .mine
	return m_cards[m_length-1];
}

// 1 - 4
Card FreeCellArea::GetCardAt(unsigned index)
{
	if(index > m_length)
=======
	if(!m_numCards)
>>>>>>> .r308
	{
<<<<<<< .mine
		throw Exception("Cannot get card at requested index; index out of range");
	}
	return m_cards[index-1];
}

Card FreeCellArea::RemoveCardAt(unsigned index)
{
	Card returnedCard;

	if(index > m_length)
	{
		throw Exception("Cannot remove card at requested index; index out of bounds");
	}

	returnedCard = m_cards[index-1];
	m_cards[index-1] = Card();

	// now, so as to not break the functionality entirely, shift the cards up so that they are a contiguous block
	if(m_length > 1)
	{
		// basically bubbling the blank card from previous removal back to the end
		Card temp;
		for(unsigned i = 1; i < m_length; ++i)
		{
			if(m_cards[i-1].isBlank())
			{
				temp = m_cards[i-1];
				m_cards[i-1] = m_cards[i];
				m_cards[i] = temp;
			}
		}
=======
		throw Exception("Can't pop from empty free cell area.");
>>>>>>> .r308
	}
<<<<<<< .mine
	--m_length;

	return returnedCard;
=======
	Card poppedCard = m_cards[index];

	return poppedCard;
>>>>>>> .r308
}

<<<<<<< .mine
unsigned FreeCellArea::GetLength() const
{
	return m_length;
}

=======
unsigned FreeCellArea::GetNum() const
{
	return m_numCards;
}

>>>>>>> .r308
unsigned FreeCellArea::GetRemaining() const
{
<<<<<<< .mine
	return 4-m_length;
=======
	return 4-m_numCards;
>>>>>>> .r308
}

void FreeCellArea::Clear()
{
	for(int i=0; i<4; ++i)
	{
		m_cards[i] = Card(); //set each card to blank card
	}
	m_length = 0;
}

void FreeCellArea::Purge()
{
	m_cards.Purge();
	m_length = 0;
}