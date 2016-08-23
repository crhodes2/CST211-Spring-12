#pragma once

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <string>
using std::string;

#include <regex>
using std::tr1::regex;
using std::tr1::cmatch;
using std::tr1::smatch;
using std::tr1::regex_match;
using std::tr1::regex_search;

#include <stack>
using std::stack; // not used for any of the game play areas, just in popping stacks of cards around, still within lab specs

#include "GameTable.h"
#include "Deck.h"
#include "Exception.h"

class FreeCellGame
{
private:
	GameTable m_table;
	Deck m_deck;

	void ProcessMainMenuChoice(int menu_choice);
	int MainMenu(void);

	void MainGameLoop(void);
	void DealDeckToPlayArea(void);

	void CustomSeed(void);
	void RandomSeed(void);

	void ResetGame(void);

	void SetUpConsoleWindow(void);

	bool GameWon(void);

	void DisplayTable(void);

	string GetInput(void);

	void ResolveMove(string move);
	bool ValidateMove(string first, string second);

	void ShowHelp();

	void PerformMove(string first, string second);

	Card GetCardByBoardCoord(string coord);
	Card GetPlayAreaCardByCoord(unsigned col, unsigned row);



public:
	FreeCellGame(void);
	~FreeCellGame(void);

	void Start(void);
	
	static enum MENU_CHOICES{EXIT, NEW_GAME, CUSTOM_SEED, HELP};
	static const unsigned CONSOLE_WIDTH = 80;
	static const unsigned CONSOLE_HEIGHT = 40;
};

