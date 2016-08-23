#include "PlayArea.h"


PlayArea::PlayArea(void)
{
	m_cards.setLength(8);
}

PlayArea::PlayArea(PlayArea const& copy)
{
	
}

PlayArea::~PlayArea(void)
{

}

PlayArea const& PlayArea::operator=(PlayArea const& rhs)
{
	m_cards = rhs.m_cards;
	return *this;
}

void PlayArea::AddCard(Card card, unsigned index)
{
	m_cards[index].Push(card);
}

Card PlayArea::PopCard(unsigned index)
{
	return m_cards[index].Pop();
}

Card PlayArea::PeekCard(unsigned index)
{
	return m_cards[index].Peek();
}

void PlayArea::Purge(void)
{
	for(int i = 0; i<8; ++i)
	{
		m_cards[i].Purge();
	}
}