#include "HomeCellArea.h"


HomeCellArea::HomeCellArea(void)
{
	m_cards.setLength(4);
	ArrayBasedStack<Card> emptyStack(13);
	for(int i=0; i<4; ++i)
	{
		m_cards[i] = emptyStack;
	}
}

HomeCellArea::HomeCellArea(HomeCellArea const& copy)
{
	m_cards.setLength(4);
	for(int i = 0; i < 4; ++i)
	{
		m_cards[i] = copy.m_cards[i];
	}
}

HomeCellArea::~HomeCellArea(void)
{

}

HomeCellArea const& HomeCellArea::operator=(HomeCellArea const& rhs)
{
	if(this != &rhs)
	{
		for(int i = 0; i < 4; ++i)
		{
			m_cards[i] = rhs.m_cards[i];
		}
	}
	return *this;
}

void HomeCellArea::AddCard(Card card)
{
	if((m_cards[card.GetSuit()].isEmpty() && card.GetRank() == Card::RANK_ACE)
		|| m_cards[card.GetSuit()].Peek().GetRank() == static_cast<Card::RANK>(card.GetRank()-1))
	{
		m_cards[card.GetSuit()].Push(card);
	}
	else
	{
		throw Exception("Cannot place that card in the home cell area");
	}
}

void HomeCellArea::Purge(void)
{
	for(int i = 0; i < 4; ++i)
	{
		m_cards[i].Purge();
	}
}

Card HomeCellArea::TopCard(unsigned col)
{
	Card topCard;
	if(!m_cards[col].isEmpty())
	{
		topCard = m_cards[col].Peek();
	}
	return topCard;
}