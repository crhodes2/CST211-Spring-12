#pragma once

#include "FreeCellArea.h"
#include "HomeCellArea.h"
#include "PlayArea.h"

class GameTable
{
	private:
		FreeCellArea m_freeCellArea;
		HomeCellArea m_homeCellArea;
		PlayArea m_playArea;

	public:
		friend class FreeCellGame;

		GameTable(void);
		GameTable(GameTable const& copy);
		~GameTable(void);

		GameTable const& operator=(GameTable const& rhs);

		void Purge();
};

