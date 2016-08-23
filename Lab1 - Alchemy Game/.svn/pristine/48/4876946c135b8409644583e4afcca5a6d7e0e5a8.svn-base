#include "GameBoard.h"
#include "AlchemyGame.h"

/**********************************************************************	
* Purpose: default constructor for gameboard
*
* Entry: none
*
* Exit: Generates a blank gameboard full of blank cells
*
************************************************************************/
GameBoard::GameBoard(){
	// set up blank gameboard
	m_board_golden.setColumn(AlchemyGame::BOARD_WIDTH);
	m_board_golden.setRow(AlchemyGame::BOARD_HEIGHT);
	
	m_board_symbols.setColumn(AlchemyGame::BOARD_WIDTH);
	m_board_symbols.setRow(AlchemyGame::BOARD_HEIGHT);

	for(int r=0; r<AlchemyGame::BOARD_HEIGHT; ++r){
		for(int c=0; c<AlchemyGame::BOARD_WIDTH; ++c){
			m_board_symbols[r][c] = AlchemyGame::SYMBOL_BLANK;
			m_board_golden[r][c] = false;
		}
	}
}
/**********************************************************************	
* Purpose: Copy constructor
*
* Entry: parameter: copy, const& to the GameBoard to copy from
*
* Exit: Current GameBoard has copied settings from copy.
*
************************************************************************/
GameBoard::GameBoard(GameBoard const& copy) : m_board_symbols(copy.m_board_symbols), m_board_golden(copy.m_board_golden){}

/**********************************************************************	
* Purpose: Assignment operator
*
* Entry: parameter: rhs, const& to right hand gameboard
*
* Exit: current gameboard was deep copied from right hand gameboard
*
************************************************************************/
GameBoard& GameBoard::operator=(GameBoard const& rhs){
	m_board_symbols = rhs.m_board_symbols;
	m_board_golden = rhs.m_board_golden;
	return *this;
}

/**********************************************************************	
* Purpose: getter for if the given cell is golden or not
*
* Entry: parameters: row, col (ints) or coord (COORD) representing gameboard location
*
* Exit: returns bool representing if that cell is golden
*
************************************************************************/
bool GameBoard::getGolden(int row, int col){
	return m_board_golden[row-1][col-1];
}
bool GameBoard::getGolden(COORD coord){
	return m_board_golden[coord.Y-1][coord.X-1];
}

/**********************************************************************	
* Purpose: setter for golden
*
* Entry: parameters: row, col (ints) or coord (COORD) representing gameboard location
*				is_golden (bool) the bool to set the cell's state to
*
* Exit: The cell is set to is_golden
*
************************************************************************/
void GameBoard::setGolden(int row, int col, bool is_golden){
	m_board_golden[row-1][col-1] = is_golden;
}
void GameBoard::setGolden(COORD coord, bool is_golden){
	m_board_golden[coord.Y-1][coord.X-1] = is_golden;
}

/**********************************************************************	
* Purpose: setter for symbol in a cell
*
* Entry: parameters: row, col (ints) or coord (COORD) representing gameboard location
*				symbol (const& Symbol) symbol to set in the given cell
*
* Exit: the given cell is set to the given symbol
*
************************************************************************/
void GameBoard::setSymbol(int row, int col, Symbol const& symbol){
	m_board_symbols[row-1][col-1] = symbol;
}
void GameBoard::setSymbol(COORD coord, Symbol const& symbol){
	m_board_symbols[coord.Y-1][coord.X-1] = symbol;
}

/**********************************************************************	
* Purpose: getter for a cell's symbol
*
* Entry: parameters: row, col (ints) or coord (COORD) representing gameboard location
*
* Exit: returns symbol of the symbol at given location
*
************************************************************************/
Symbol const& GameBoard::getSymbol(int row, int col){
	return m_board_symbols[row-1][col-1];
}
Symbol const& GameBoard::getSymbol(COORD coord){
	return m_board_symbols[coord.Y-1][coord.X-1];
}