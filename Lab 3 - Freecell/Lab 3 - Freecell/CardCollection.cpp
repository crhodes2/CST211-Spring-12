#include "CardCollection.h"

/****************************************************************
* Overview: Basic constructor
*    Input: None.
*   Output: m_cards is set to an empty vector of Card*
*****************************************************************/
CardCollection::CardCollection(){
	m_cards = vector<Card>(); // empty vector of card pointers
}

CardCollection::CardCollection(CardCollection const& copy)
{
	m_cards.reserve(copy.m_cards.size());

	for(vector<Card>::const_iterator i = copy.m_cards.begin(); i != copy.m_cards.end(); ++i)
	{
		m_cards.push_back(Card(*i));
	}
}

/****************************************************************
* Overview: Basic destructor
*    Input: None.
*   Output: Cleans up each card that was allocated in m_cards
*****************************************************************/
CardCollection::~CardCollection(){
	m_cards.clear();
}

/****************************************************************
* Overview: Function to add a card to the cardcollection.
*    Input: card* of the card to be added to the collection.
*   Output: card is now added to the collection (appended).
*****************************************************************/
void CardCollection::Add(Card card){
	m_cards.push_back(card);
}

/****************************************************************
* Overview: Pops a card off the end of the deck and returns a 
*			pointer to the card.
*    Input: None.
*   Output: Returns Card* of the drawn card. 
* Important Note: When this function pops a Card* out of 
*			cardcollection, its deletion must be handled elsewhere, 
*			as it no longer exists in the card collection.
*****************************************************************/
Card CardCollection::Draw(){
	Card drawnCard;
	if(this->m_cards.empty()){
		// trying to draw from an empty card collection, let it return 0, normally throw exception here
	}else{
		// next two lines are basically drawnCard = m_cards.pop();, but vectors only have .pop_back() and it doesn't return the popped element
		drawnCard = m_cards.back();
		m_cards.pop_back();
	}
	return drawnCard;
}

/****************************************************************
* Overview: The count functions count the number of cards in the 
*			collection that match the parameters. It can take a 
*			Card by constref, a suit and rank (or vice versa), 
*			or a single suit or rank and will return the count 
*			of given card/suit/rank.
*    Input: needle, Card to count. i.e. 
*			suit, suit to count. i.e. 
*			rank, rank to count.
*			invert, bool. If set to true, will return the negation of your parameters, see examples below.
*   Output: Returns an int representing the found count.
* Examples: Count(Card(Card::RANK_ACE, Card::SUIT_SPADES)) counts number of ace of spades
*			Count(Card::SUIT_SPADES) counts number of spades
*			Count(Card::RANK_QUEEN, Card::SUIT_HEARTS, true) counts number of cards that are NOT queen of hearts
*****************************************************************/
int CardCollection::Count(Card const& needle, bool invert){
	int count(0);
	for(vector<Card>::iterator i = m_cards.begin(); i != m_cards.end(); ++i){
		if(*i==needle){
			++count;
		}
	}
	if(invert){
		count = Length()-count;
	}
	return count;
}
int CardCollection::Count(Card::SUIT suit, Card::RANK rank, bool invert){
	int count(0);
	for(vector<Card>::iterator i = m_cards.begin(); i != m_cards.end(); ++i){
		if((*i).GetRank()==rank && (*i).GetSuit()==suit){
			++count;
			break;
		}
	}
	if(invert){
		count = Length()-count;
	}
	return count;
}
int CardCollection::Count(Card::RANK rank, bool invert){
	int count(0);
	for(vector<Card>::iterator i = m_cards.begin(); i!= m_cards.end(); ++i){
		if((*i).GetRank() == rank){
			++count;
		}
	}
	if(invert){
		count = Length()-count;
	}
	return count;
}
int CardCollection::Count(Card::SUIT suit, bool invert){
	int count(0);
	for(vector<Card>::iterator i = m_cards.begin(); i!= m_cards.end(); ++i){
		if((*i).GetSuit() == suit){
			++count;
		}
	}
	if(invert){
		count = Length()-count;
	}
	return count;
}

/****************************************************************
* Overview: Function to return the number of cards in collection.
*    Input: None.
*   Output: Returns number of cards in collection.
*****************************************************************/
int CardCollection::Length() const {
	return m_cards.size();
}

/****************************************************************
* Overview: Basic search and replace function. Will find search 
*			in the collection, and switch it out with replacement, 
*			preserving order of the cards.
*    Input: search and replacement, Card* of the search and 
*			replacement cards respectively.
*   Output: search's and replacement's locations are swapped.
* Important Note: This function is designed to replace cards that 
*			already exist in the collection, so it assumes that 
*			search is in the collection. If by some odd chance 
*			the search doesn't exist, no cards will be swapped.
*****************************************************************/
void CardCollection::Replace(Card& search, Card& replacement){
	Card temp;
	bool found = false;

	for(vector<Card>::iterator i = m_cards.begin(); i != m_cards.end() && !found; ++i){
		if(*i==search){
			temp = *i;
			*i = replacement;
			replacement = temp;
			found = true;
		}
	}
	if(!found)
	{
		throw Exception("Cannot replace: Card not found.");
	}
}

CardCollection const& CardCollection::operator=(CardCollection const& rhs)
{
	Purge();
	m_cards.reserve(rhs.m_cards.size());

	for(vector<Card>::const_iterator i = rhs.m_cards.begin(); i != rhs.m_cards.end(); ++i)
	{
		m_cards.push_back(Card(*i));
	}

	return *this;
}

void CardCollection::Purge()
{
	m_cards.clear();
}