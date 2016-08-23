#pragma once

#include "CardCollection.h"

#include <algorithm>
#include <ctime>
#include <cstdlib>

class Deck : public CardCollection{
	private:
	protected:
	public:
		Deck();
		~Deck();

		using CardCollection::operator=;

		void SingleDeck(void);
		void Shuffle(void);
};