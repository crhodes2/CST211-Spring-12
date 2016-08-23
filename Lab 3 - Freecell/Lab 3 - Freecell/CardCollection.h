#pragma once

#include "Card.h"
#include "Exception.h"
#include <vector>
using std::vector;

class CardCollection
{
	protected:
		std::vector<Card> m_cards;

	public:
		CardCollection(void);
		CardCollection(CardCollection const& copy);
		~CardCollection(void);

		CardCollection const& operator=(CardCollection const& rhs);

		void Purge(void);

		void Add(Card card);
		Card Draw(void);

		void Replace(Card& search, Card& replacement);

		int Count(Card const& needle, bool invert = false);
		int Count(Card::SUIT suit, Card::RANK rank, bool invert = false);
		int Count(Card::RANK rank, bool invert = false);
		int Count(Card::SUIT suit, bool invert = false);

		int Length() const;
};