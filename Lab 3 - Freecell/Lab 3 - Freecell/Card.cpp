#include "Card.h"

ostream& operator<<(ostream& stream, Card const& card);

const char* Card::suits[] = {"Diamonds","Clubs","Hearts","Spades", "BLANK"};
const char* Card::ranks[] = {"Ace","Deuce","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King","BLANK"};
const char* Card::short_suits[] = {"\4", "\5", "\3", "\6", "BLANK"};
const char* Card::short_ranks[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K", "BLANK"};

bool Card::isRed() const
{
	return m_suit == SUIT_DIAMONDS || m_suit == SUIT_HEARTS;
}

const char* Card::Rank() const
{
	return Card::short_ranks[m_rank];
}

const char* Card::Suit() const
{
	return Card::short_suits[m_suit];
}


Card::Card() : m_suit(SUIT_BLANK), m_rank(RANK_BLANK)
{
	
}

Card::Card(Card const& copy) : m_suit(copy.m_suit), m_rank(copy.m_rank)
{
	
}

Card const& Card::operator=(Card const& rhs)
{
	m_suit = rhs.m_suit;
	m_rank = rhs.m_rank;
	return *this;
}

Card::Card(SUIT suit, RANK rank) : m_rank(rank), m_suit(suit)
{
	
}

Card::~Card(void)
{
	m_suit = SUIT_BLANK;
	m_rank = RANK_BLANK;
}


ostream& operator<<(ostream& stream, Card const& card){
	if(!card.isBlank()){
		// first, figure out the color of the card
		int color = 1;
		switch(card.m_suit)
		{
			case Card::SUIT_DIAMONDS:
			case Card::SUIT_HEARTS:
				color = 12; // red color
				break;
			case Card::SUIT_CLUBS:
			case Card::SUIT_SPADES:
				color = 7; // gray color
		}

		HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

		// first get current console settings
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hstdout, &csbi);

		SetConsoleTextAttribute(hstdout, color);
		stream << Card::short_suits[card.m_suit] << Card::short_ranks[card.m_rank];

		// return settings to what they were
		SetConsoleTextAttribute(hstdout, csbi.wAttributes);
	}
	return stream;
}

bool Card::operator==(Card const& right) const{
	return (m_rank==right.m_rank && m_suit==right.m_suit);
}

bool Card::operator!=(Card const& right) const{
	return (m_rank!=right.m_rank || m_suit!=right.m_suit);
}

Card::SUIT Card::GetSuit() const
{
	return m_suit;
}

Card::RANK Card::GetRank() const
{
	return m_rank;
}

bool Card::isBlank() const
{
	return *this == Card(SUIT_BLANK, RANK_BLANK);
}