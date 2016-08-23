#include "GameTable.h"


GameTable::GameTable(void)
{

}

GameTable::GameTable(GameTable const& copy) : m_freeCellArea(copy.m_freeCellArea), m_homeCellArea(copy.m_homeCellArea), m_playArea(copy.m_playArea)
{

}

GameTable::~GameTable(void)
{
	Purge();
}

GameTable const& GameTable::operator=(GameTable const& rhs)
{
	m_freeCellArea = rhs.m_freeCellArea;
	m_homeCellArea = rhs.m_homeCellArea;
	m_playArea = rhs.m_playArea;

	return *this;
}

void GameTable::Purge()
{
	m_freeCellArea.Purge();
	m_homeCellArea.Purge();
	m_playArea.Purge();
}