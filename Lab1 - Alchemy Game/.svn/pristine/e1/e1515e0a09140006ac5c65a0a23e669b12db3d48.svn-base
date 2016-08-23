/************************************************************************
* Class: GameBoard
*
* Purpose: This class represents an Alchemy Game Board
*
* Manager functions:	
* 	GameBoard()
* 		The default size pulled from AlchemyGame settings	
*	GameBoard(GameBoard const& copy)
*		Creates gameboard with copied settings from copy
*	operator=(GameBoard const& rhs)
*		Sets current settings to those of rhs
*
* Methods:		
*	setGolden(int row, int col, bool is_golden)
*	setGolden(COORD coord, bool is_golden)
*	getGolden(int row, int col)
*	getGolden(COORD coord)
*	setSymbol(int row, int col, Symbol const& symbol);
*	setSymbol(COORD coord, Symbol const& symbol);
*	getSymbol(int row, int col);
*	getSymbol(COORD coord);
*		simple getters and setters for symbol and is_golden
*************************************************************************/
#pragma once
#include "Symbol.h"
#include "Array2D.h"
#include <Windows.h>

class GameBoard{
	private:
		Array2D<Symbol> m_board_symbols;
		Array2D<bool> m_board_golden;
	public:
		GameBoard();
		GameBoard(GameBoard const& board);

		GameBoard& operator=(GameBoard const& rhs);
	
		void setGolden(int row, int col, bool is_golden);
		void setGolden(COORD coord, bool is_golden);
		bool getGolden(int row, int col);
		bool getGolden(COORD coord);
	
		void setSymbol(int row, int col, Symbol const& symbol);
		void setSymbol(COORD coord, Symbol const& symbol);
		Symbol const& getSymbol(int row, int col);
		Symbol const& getSymbol(COORD coord);
};