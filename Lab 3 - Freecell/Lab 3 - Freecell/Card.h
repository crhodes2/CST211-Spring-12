#pragma once

#include <iostream>
using std::ostream;

#include <Windows.h>

class Card
{
	friend ostream& operator<<(ostream& stream, Card const& card);
	public:
		static enum SUIT{SUIT_DIAMONDS, SUIT_CLUBS, SUIT_HEARTS, SUIT_SPADES, SUIT_COUNT, SUIT_BLANK};
		static enum RANK{RANK_ACE, RANK_DEUCE, RANK_THREE, RANK_FOUR, RANK_FIVE, RANK_SIX, RANK_SEVEN, RANK_EIGHT, RANK_NINE, RANK_TEN, RANK_JACK, RANK_QUEEN, RANK_KING, RANK_COUNT, RANK_BLANK};
		
		Card(void);
		Card(SUIT suit, RANK rank);
		Card(Card const& copy);
		~Card(void);

		Card const& operator=(Card const& rhs);

		bool operator==(Card const& right) const;
		bool operator!=(Card const& right) const;

		bool isBlank(void) const;

		// These funcs return const char* versions of the card, not raw data member values
		const char* Card::Rank(void) const;
		const char* Card::Suit(void) const;

		SUIT GetSuit(void) const;
		RANK GetRank(void) const;

		bool isRed() const;

		static const char* suits[];
		static const char* ranks[];
		static const char* short_suits[];
		static const char* short_ranks[];


	private:
		SUIT m_suit;
		RANK m_rank;
	protected:
};