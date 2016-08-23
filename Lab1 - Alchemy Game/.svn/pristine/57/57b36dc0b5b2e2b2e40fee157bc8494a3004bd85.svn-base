/************************************************************************
* Class: AlchemyGame
*
* Purpose: This class represents the game of Alchemy
*
* Manager functions:	
* 	AlchemyGame()
* 		Sets up basic game environment	
*	AlchemyGame(AlchemyGame const& copy)
*		Creates AlchemyGame with copied settings from copy
*	operator=(AlchemyGame const& rhs)
*		Sets current settings to those of rhs
*	~AlchemyGame()
*		Cleans up and resets AlchemyGame
*
* Methods:		
*	
*	Start()	
*		Begins the game
*	MainGameLoop()
*		Controls the basic flow of generating symbols and letting user make moves until game finishes
*	DisplayBoard()
*		Displays the gameboard and associated info
*	DisplayBoardInfo()
*		Displays game related info such as score, number of discards
*	getMove()
*		Simpe function to simplify getting coordinate input from user
*	CheckRowCol()
*		Performs a check on the current row/col to determine if it has been completed, 
*		and if so, remove all symbols in that row/col
*	isValidMove()
*		Determines if a move is valid for the given symbol
*	addToScore()
*		Calculates score of last move and adds it to total score
*	getRandomSymbol()
*		Generates a random symbol based on the rules defined within it
*	ProcessMove()
*		Helper function to process what the user wishes to do and handles it
*	PlaceSymbol()
*		Places a symbol on the game board and makes the cell under it golden
*	LevelComplete()
*		Determines if the level is complete
*	MainMenu()
*		Displays the main menu and a prompt for selection
*	ProcessMenuChoice(int choice)
*		Handles the menu choice and calls the appropriate functions
*	LevelSelectMenu()
*		Displays a basic level select menu allowing user to select level
*	SetUpConsoleWindow()
*		Utility function to set console title, font size and window size
*************************************************************************/
#pragma once

#include "Exception.h"
#include "Array2D.h"
#include "GameBoard.h"
#include <Windows.h>

class AlchemyGame{
	private:
		// game variables
		GameBoard m_board;
		int m_score;
		int m_num_discards;
		int m_num_symbols;
		int m_num_colors;

		// symbol/move variables
		Symbol m_current_symbol;
		COORD m_current_move;

		// game flow related
		void MainGameLoop();

		// input output	related
		void DisplayBoard();
		void DisplayBoardInfo();
		void getMove();

		// game logic related
		void CheckRowCol();
		bool isValidMove();
		void addToScore();
		Symbol getRandomSymbol();
		void ProcessMove();
		void PlaceSymbol();
		bool LevelComplete();

		// menu related
		static enum MENU_CHOICES{EXIT, NEW_GAME, LEVEL_SELECT};
		int MainMenu();
		void ProcessMenuChoice(int choice);
		int LevelSelectMenu();

		// utility/etc
		void SetUpConsoleWindow();

	public:
		AlchemyGame();
		AlchemyGame(AlchemyGame const& copy);
		~AlchemyGame();
		AlchemyGame& operator=(AlchemyGame const& rhs);

		void Start();

		// game settings
		static const int BOARD_WIDTH = 9;
		static const int BOARD_HEIGHT = 8;
		static const COORD INITIAL_WILDCARD_COORD;
	
		// symbol settings
		static const char AVAILABLE_SYMBOL_CHARS[];
		static const Symbol SYMBOL_BOMB;
		static const Symbol SYMBOL_WILDCARD;
		static const Symbol SYMBOL_BLANK;

		// color settings
		static const int BOARD_BACKGROUND_COLOR = 8;
		static const int GOLDEN_BACKGROUND_COLOR = 14;
		static const int AVAILABLE_SYMBOL_COLORS[];
		static const int BORDER_TEXT_COLOR = 2;

		// level settings
		static const int MAX_LEVEL = 2;

		// console settings
		static const int GAME_WIDTH = 50;
		static const int GAME_HEIGHT = 20;
};