#include "AlchemyGame.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <Windows.h>
#include "RandomNumberGenerator.h"

const int AlchemyGame::AVAILABLE_SYMBOL_COLORS[] = {7,9,10,11,12,15};
const char AlchemyGame::AVAILABLE_SYMBOL_CHARS[] = {127 /*del*/, 224 /*alpha*/, 228 /*sigma*/, 227 /*pi*/, 231 /*gamma*/, 230 /*mu*/};
const Symbol AlchemyGame::SYMBOL_BOMB = Symbol('X', 4 /*red*/);
const Symbol AlchemyGame::SYMBOL_WILDCARD = Symbol(219 /*ANSI block character*/, 7 /*gray*/);
const Symbol AlchemyGame::SYMBOL_BLANK = Symbol(' ', 0);
const COORD AlchemyGame::INITIAL_WILDCARD_COORD = {4,5};

/**********************************************************************	
* Purpose: Default constructor for AlchemyGame
*
* Entry: None.
*
* Exit: Sets up basic values for start of game.
*
************************************************************************/
AlchemyGame::AlchemyGame() : m_num_discards(0), m_score(0), m_num_symbols(0), m_num_colors(0){}

/**********************************************************************	
* Purpose: Copy constructor for AlchemyGame
*
* Entry: parameter: copy, a const& to another AlchemyGame to copy settings from
*
* Exit: Sets the values of the current AlchemyGame to those of the copy.
*
************************************************************************/
AlchemyGame::AlchemyGame(AlchemyGame const& copy) : m_board(copy.m_board), m_num_discards(copy.m_num_discards), m_score(copy.m_score), m_num_symbols(copy.m_num_symbols), m_num_colors(copy.m_num_colors){}

/**********************************************************************	
* Purpose: Destructor
*
* Entry: None.
*
* Exit: This function resets and cleans up after AlchemyGame.
*
************************************************************************/
AlchemyGame::~AlchemyGame(){
	m_score = 0;
	m_num_discards = 0;
	GameBoard blank_board;
	m_board = blank_board;
	m_num_colors = 0;
	m_num_symbols = 0;
	COORD blank_coord = {0,0};
	Symbol blank_symbol = AlchemyGame::SYMBOL_BLANK;
	m_current_symbol = blank_symbol;
	m_current_move = blank_coord;
}

/**********************************************************************	
* Purpose: Assignment operator for AlchemyGame
*
* Entry: rhs is a const& to the right hand side AlchemyGame
*
* Exit: The current AlchemyGame takes on the same values as the rhs.
*
************************************************************************/
AlchemyGame& AlchemyGame::operator=(AlchemyGame const& rhs){
	m_board = rhs.m_board;
	m_num_discards = rhs.m_num_discards;
	m_score = rhs.m_score;
	m_num_symbols = rhs.m_num_symbols;
	m_num_colors = rhs.m_num_colors;

	return *this;
}

/**********************************************************************	
* Purpose: This function starts the game of Alchemy. It is public and 
*			should be the only function called by the enduser
*
* Entry: None.
*
* Exit: Outputs prompts for the user to navigate menus and play game
*
************************************************************************/
void AlchemyGame::Start(){
	SetUpConsoleWindow();

	bool error = false;
	int menu_choice = -1;
	
	while(error || menu_choice != 0){
		try{
			menu_choice = MainMenu();
			ProcessMenuChoice(menu_choice);
			error = false;
		}catch(Exception e){
			cout << e << endl;
			error = true;
			system("pause");
		}
	}
}

/**********************************************************************	
* Purpose: Outputs the main menu for Alchemy. Invalid choices throws exceptions.
*
* Entry: None.
*
* Exit: returns an int representing the choice of the user
*
************************************************************************/
int AlchemyGame::MainMenu(){
	int choice = -1;

	system("cls");
	cout << "Welcome to Alchemy!" << endl;
	cout << endl;
	cout << "1) New Game" << endl;
	cout << "2) Level Select" << endl;
	cout << "0) Exit" << endl;
	cout << endl;
	cout << "Enter Menu Choice: ";
	cin >> choice;

	bool cinIsGood = cin.good();
	cin.clear();
	cin.ignore(INT_MAX,'\n');

	if (!cinIsGood || choice < 0 || choice > 2) {
		throw Exception("Invalid menu choice.");
	}
	return choice;
}

/**********************************************************************	
* Purpose: Outputs and takes in choice for level select
*
* Entry: None.
*
* Exit: returns an int representing the level chosen
*
************************************************************************/
int AlchemyGame::LevelSelectMenu(){
	int choice = -1;

	system("cls");
	cout << "Level Select:" << endl;
	cout << endl;
	cout << "Simply enter a level number below (1-" << AlchemyGame::MAX_LEVEL << ")" << endl;
	cout << endl;
	cout << "Level: ";
	cin >> choice;

	bool cinIsGood = cin.good();
	cin.clear();
	cin.ignore(INT_MAX,'\n');

	if (!cinIsGood || choice < 1 || choice > AlchemyGame::MAX_LEVEL) {
		throw Exception("Invalid menu choice.");
	}
	return choice;
}

/**********************************************************************	
* Purpose: Handles the main menu selection and calls appropriate funcs
*
* Entry: parameter: choice, int representing a main menu choice
*
* Exit: Sets up the environment and calls the appropriate functions
*
************************************************************************/
void AlchemyGame::ProcessMenuChoice(int choice){
	int level = 1; // the game level to start on
	GameBoard new_board;
	switch(static_cast<AlchemyGame::MENU_CHOICES>(choice)){
		case LEVEL_SELECT:
			level = LevelSelectMenu(); // intentionally no break
		case NEW_GAME:
			// set up game, with level setting up proper # of colors/symbols
			m_num_symbols = 4+level;
			m_num_colors = 4+level;

			// make a completely new board each time there is a new game, reset game variables
			m_board = new_board;
			m_num_discards = 0;
			m_score = 0;

			// add a wildcard to start the game
			m_board.setSymbol(AlchemyGame::INITIAL_WILDCARD_COORD, AlchemyGame::SYMBOL_WILDCARD);
			m_board.setGolden(AlchemyGame::INITIAL_WILDCARD_COORD, true);

			MainGameLoop();
			break;
		case EXIT:
			break;
		default:
			throw Exception("Invalid menu choice. Expecting 0, 1 or 2.");
	}
}

/**********************************************************************	
* Purpose: The main loop controlling game behavior. Continuously generates 
*	symbols and updates the board, takes input until 3 consecutive 
*	discards, or the level is complete
*
* Entry: None.
*
* Exit: The game is displayed on the console, with prompts guiding the user
*
************************************************************************/
void AlchemyGame::MainGameLoop(){
	bool error = true;
	while(!LevelComplete() && m_num_discards < 3){
		error = true; // to start the inner loop each time a symbol is placed
		m_current_symbol = getRandomSymbol();
		while(error){
			DisplayBoard();
			//dumpboard(); // remove me
			try{
				getMove();
				ProcessMove();
				error = false;
			}catch(Exception e){
				cout << e << endl;
				system("pause");
			}
		}
	}
	if(LevelComplete()){
		cout << "You win!" << endl;
	}else{
		cout << "You fail!" << endl;
	}
	system("pause");
}

/**********************************************************************	
* Purpose: Displays the game board on the console
*
* Entry: None.
*
* Exit: The board is output to console
*
************************************************************************/
void AlchemyGame::DisplayBoard(){
	system("cls");

	HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);

	// the offset below horizontally centers the board
	COORD offset = {(AlchemyGame::GAME_WIDTH-2-AlchemyGame::BOARD_WIDTH)/2, 3};

	// make a 1d array representing the console buffer (to avoid updating each character and getting the screen flicker)
	CHAR_INFO consoleBuffer[AlchemyGame::GAME_WIDTH * AlchemyGame::GAME_HEIGHT];

	// first, filling the whole screen with blank as default
	for(int y = 0; y < GAME_WIDTH; ++y){
		for(int x = 0; x < GAME_HEIGHT; ++x){
			consoleBuffer[x + y*GAME_HEIGHT].Char.AsciiChar = ' ';
			consoleBuffer[x + y*GAME_HEIGHT].Attributes = 0;
		}
	}

	CHAR_INFO symbol; // temp symbol struct to make code more readable below
	for(int r = 0; r <= AlchemyGame::BOARD_HEIGHT + 1; ++r){
		for(int c = 0; c <= AlchemyGame::BOARD_WIDTH + 1; ++c){
			if(r>0 && r<AlchemyGame::BOARD_HEIGHT+1 && c>0 && c<AlchemyGame::BOARD_WIDTH+1){
				// set the actual character representation of the symbol
				symbol.Char.AsciiChar = m_board.getSymbol(r,c).getCharacter();
			
				// set the color of the symbol
				symbol.Attributes = m_board.getSymbol(r,c).getColor();
			
				// if the piece needs to be golden background, or the value of the golden bg in, else default background color
				if(m_board.getGolden(r,c)){
					symbol.Attributes |= AlchemyGame::GOLDEN_BACKGROUND_COLOR << 4;
				}else{
					symbol.Attributes |= AlchemyGame::BOARD_BACKGROUND_COLOR << 4;
				}

				consoleBuffer[offset.X + c + (r + offset.Y)*AlchemyGame::GAME_WIDTH] = symbol;
			}else{
				// output a border showing the row/col
				consoleBuffer[offset.X + c + (r + offset.Y)*AlchemyGame::GAME_WIDTH].Attributes = AlchemyGame::BORDER_TEXT_COLOR;
				if(r==0 && c==0){
					// top left corner
				}else if(r==0 && c==AlchemyGame::BOARD_WIDTH+1){
					// top right corner
				}else if(r==AlchemyGame::BOARD_HEIGHT+1 && c==0){
					// bottom left corner
				}else if(r==AlchemyGame::BOARD_HEIGHT+1 && c==AlchemyGame::BOARD_WIDTH+1){
					// bottom right corner
				}else if(r==0 || r==AlchemyGame::BOARD_HEIGHT+1){
					// top and bottom of board, output the current col
					consoleBuffer[offset.X + c + (r + offset.Y)*GAME_WIDTH].Char.AsciiChar = c+'0';
				}else if(c==0 || c==AlchemyGame::BOARD_WIDTH+1){
					// left and right of the board, output current row
					consoleBuffer[offset.X + c + (r + offset.Y)*GAME_WIDTH].Char.AsciiChar = r+'0';
				}
				
			}
		}
	}
	
	// setting up parameters to pass along to console functions
	COORD charBuffSize = {AlchemyGame::GAME_WIDTH, AlchemyGame::GAME_HEIGHT};
	COORD characterPosition = {0, 0};
	SMALL_RECT writeArea = {0, 0, AlchemyGame::GAME_WIDTH-1, AlchemyGame::GAME_HEIGHT-1};

	// output the console buffer to the screen
	WriteConsoleOutputA(wHnd, consoleBuffer, charBuffSize, characterPosition, &writeArea);

	DisplayBoardInfo();
}

/**********************************************************************	
* Purpose: Outputs additional information to console such as score, 
*	discard count, and current symbol
*
* Entry: None. Designed to be called in, or with DisplayBoard()
*
* Exit: Above information is output to the console
*
************************************************************************/
void AlchemyGame::DisplayBoardInfo(){
	HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);

	// now, output game information besides the board, namely score, current symbol, and brief instructions
	COORD cursorPos = {0,0};
	cursorPos.X = 2;
	cursorPos.Y = 1;
	SetConsoleCursorPosition(wHnd, cursorPos);
	cout << "Alchemy by Andrew Sparkes";
	cursorPos.Y = 4;
	SetConsoleCursorPosition(wHnd, cursorPos);
	cout << "Current Score:";
	cursorPos.Y = 5;
	SetConsoleCursorPosition(wHnd, cursorPos);
	cout << "   " << m_score;
	cursorPos.Y = 7;
	SetConsoleCursorPosition(wHnd, cursorPos);
	cout << "# of Discards:";
	cursorPos.Y = 8;
	SetConsoleCursorPosition(wHnd, cursorPos);
	cout << "   " << m_num_discards;
	cursorPos.Y = 10;
	SetConsoleCursorPosition(wHnd, cursorPos);
	cout << "Enter (0,0) to";
	cursorPos.Y = 11;
	SetConsoleCursorPosition(wHnd, cursorPos);
	cout << "discard";

	// output current symbol 
	cursorPos.X = (AlchemyGame::GAME_WIDTH-10)/2;
	cursorPos.Y = AlchemyGame::BOARD_HEIGHT+6;
	SetConsoleCursorPosition(wHnd, cursorPos);
	cursorPos.X += 8;
	cout << "Symbol: ";
	
	// much work to spit out a single colored symbol at specified position
	COORD charBuffSize = {1, 1};
	CHAR_INFO symbol;
	symbol.Char.AsciiChar = m_current_symbol.getCharacter();
	symbol.Attributes = m_current_symbol.getColor();
	COORD characterPosition = {0, 0};
	SMALL_RECT writeArea = {cursorPos.X, cursorPos.Y, cursorPos.X, cursorPos.Y};
	WriteConsoleOutputA(wHnd, &symbol, charBuffSize, characterPosition, &writeArea);
}

/**********************************************************************	
* Purpose: Utility function to get a coordinate input from user
*
* Entry: None.
*
* Exit: populates m_current_move with the user's requested move
*
************************************************************************/
void AlchemyGame::getMove(){
	bool cinIsGood; // flag used to determine if invalid input was thrown to cin

	HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD move = {0,0}; // the coordinates of the player's move
	COORD cursorPos; // the cursor position, used to place the row/col prompts in the correct place
	int input; // temp variable used to hold value of player's inputted row/col

	// set the cursor below the game board
	cursorPos.X = (AlchemyGame::GAME_WIDTH-10)/2;
	cursorPos.Y = AlchemyGame::BOARD_HEIGHT+7;
	SetConsoleCursorPosition(wHnd, cursorPos);
	cout << "Row: ";
	cin >> input;

	cinIsGood = cin.good();
	cin.clear();
	cin.ignore(INT_MAX,'\n');

	if (!cinIsGood || input < 0 || input > AlchemyGame::BOARD_HEIGHT){
		throw Exception("Invalid row choice.");
	}else{
		move.Y = input;
	}

	// set the cursor below the game board, and below the row prompt
	cursorPos.X = (AlchemyGame::GAME_WIDTH-10)/2;
	cursorPos.Y = AlchemyGame::BOARD_HEIGHT+8;
	SetConsoleCursorPosition(wHnd, cursorPos);
	cout << "Col: ";
	cin >> input;

	cinIsGood = cin.good();
	cin.clear();
	cin.ignore(INT_MAX,'\n');

	if (!cinIsGood || input < 0 || input > AlchemyGame::BOARD_WIDTH) {
		throw Exception("Invalid col choice.");
	}else{
		move.X = input;
	}
	
	m_current_move = move;
}

/**********************************************************************	
* Purpose: This function processes the given move, determines if it is a 
*	bomb, discard, or normal symbol, and acts accordingly
*
* Entry: None.
*
* Exit: The symbol is handled appropriately, or exception thrown if any
*	errors occured with current move.
*
************************************************************************/
void AlchemyGame::ProcessMove(){
	COORD discard = {0,0}; // if user inputs coord 0,0, interpret as a discard move

	if(m_current_move.X == discard.X && m_current_move.Y == discard.Y){
		++m_num_discards;
	}else if(m_current_symbol == AlchemyGame::SYMBOL_BOMB){
		// bomb
		if(m_board.getSymbol(m_current_move) != AlchemyGame::SYMBOL_BLANK){
			// not blank, so safe to remove it (set it to blank)
			m_board.setSymbol(m_current_move, AlchemyGame::SYMBOL_BLANK);
		}else{
			throw Exception("No symbol at inputted bomb location.");
		}
		m_num_discards = 0;
	}else{
		// normal symbol or wildcard, both have same process
		PlaceSymbol();
		CheckRowCol();
		m_num_discards = 0;
	}
}

/**********************************************************************	
* Purpose: This function places the current symbol on the board at
*	the current move position. It also sets the board to golden as well.
*
* Entry: None.
*
* Exit: Assuming the move is valid, symbol and golden are updated, as 
*	well as score, else exception is thrown
*
************************************************************************/
void AlchemyGame::PlaceSymbol(){
	if(isValidMove()){
		m_board.setSymbol(m_current_move.Y, m_current_move.X, m_current_symbol);
		m_board.setGolden(m_current_move.Y, m_current_move.X, true);
		addToScore();
	}else{
		throw Exception("Invalid move");
	}
}

/**********************************************************************	
* Purpose: Determines if the current move and current symbol are valid
*	given other symbols nearby.
*
* Entry: None.
*
* Exit: returns a bool representing if the move is indeed valid.
*
************************************************************************/
bool AlchemyGame::isValidMove(){
	bool valid = false, valid_left = false, valid_right = false, valid_top = false, valid_bottom = false;

	if(m_board.getSymbol(m_current_move) == AlchemyGame::SYMBOL_BLANK){
		
		// if the current move lies on any of hte board boundaries, treat anything over the boundary the same as a blank
		Symbol top;
		if(m_current_move.Y == 1){
			top = AlchemyGame::SYMBOL_BLANK;
		}else{
			top = m_board.getSymbol(m_current_move.Y-1, m_current_move.X);
		}
		Symbol left;
		if(m_current_move.X == 1){
			left = AlchemyGame::SYMBOL_BLANK;
		}else{
			left = m_board.getSymbol(m_current_move.Y,m_current_move.X-1);
		}
		Symbol right;
		if(m_current_move.X == AlchemyGame::BOARD_WIDTH){
			right = AlchemyGame::SYMBOL_BLANK;
		}else{
			right = m_board.getSymbol(m_current_move.Y,m_current_move.X+1);
		}
		Symbol bottom;
		if(m_current_move.Y == AlchemyGame::BOARD_HEIGHT){
			bottom = AlchemyGame::SYMBOL_BLANK;
		}else{
			bottom = m_board.getSymbol(m_current_move.Y+1, m_current_move.X);
		}

		bool matching_edge = false;
		if(m_current_symbol == AlchemyGame::SYMBOL_WILDCARD){
			// wildcard, valid for any place adjacent to any symbol
			// by its nature, it's valid placed next to any symbol, blank or otherwise
			valid_left = valid_right = valid_top = valid_bottom = true;

			// check all 4 sides, if any have a symbol, the wildcard is a valid symbol for given position
			if(left != AlchemyGame::SYMBOL_BLANK || right != AlchemyGame::SYMBOL_BLANK || top != AlchemyGame::SYMBOL_BLANK || bottom != AlchemyGame::SYMBOL_BLANK){
				matching_edge = true;
			}
		}else{
			// check left
			if(left == AlchemyGame::SYMBOL_BLANK){
				valid_left = true;
			}else if(m_current_move.X == 1
				|| left == AlchemyGame::SYMBOL_WILDCARD
				|| left.getCharacter() == m_current_symbol.getCharacter()
				|| left.getColor() == m_current_symbol.getColor()){
				valid_left = true;
				matching_edge = true;
			}

			// check right
			if(right == AlchemyGame::SYMBOL_BLANK){
				valid_right = true;
			}else if(m_current_move.X == AlchemyGame::BOARD_WIDTH 
				|| right == AlchemyGame::SYMBOL_WILDCARD 
				|| right.getCharacter() == m_current_symbol.getCharacter() 
				|| right.getColor() == m_current_symbol.getColor()){
				valid_right = true;
				matching_edge = true;
			}

			// check top
			if(top == AlchemyGame::SYMBOL_BLANK){
				valid_top = true;
			}else if(m_current_move.Y == 1
				|| top == AlchemyGame::SYMBOL_WILDCARD 
				|| top.getCharacter() == m_current_symbol.getCharacter() 
				|| top.getColor() == m_current_symbol.getColor()){
				valid_top = true;
				matching_edge = true;
			}

			// check bottom
			if(bottom == AlchemyGame::SYMBOL_BLANK){
				valid_bottom = true;
			}else if(m_current_move.Y == AlchemyGame::BOARD_HEIGHT 
				|| bottom == AlchemyGame::SYMBOL_WILDCARD 
				|| bottom.getCharacter() == m_current_symbol.getCharacter() 
				|| bottom.getColor() == m_current_symbol.getColor()){
				valid_bottom = true;
				matching_edge = true;
			}
		}
		valid = matching_edge && valid_left && valid_right && valid_top && valid_bottom;
	}else{
		// There is already a symbol at that location
		valid = false;
	}
	
	return valid;
}

/**********************************************************************	
* Purpose: This function calculates the score for the given move
*
* Entry: Designed to be called AFTER verifying the move is valid with
*	isValidMove()
*
* Exit: This function increments the score by however much the current 
*	move was worth
*
************************************************************************/
void AlchemyGame::addToScore(){
	int score = 0;

	// if the current move lies on any of hte board boundaries, treat anything over the boundary the same as a blank
	Symbol top;
	if(m_current_move.Y == 1){
		top = AlchemyGame::SYMBOL_BLANK;
	}else{
		top = m_board.getSymbol(m_current_move.Y-1, m_current_move.X);
	}
	Symbol left;
	if(m_current_move.X == 1){
		left = AlchemyGame::SYMBOL_BLANK;
	}else{
		left = m_board.getSymbol(m_current_move.Y,m_current_move.X-1);
	}
	Symbol right;
	if(m_current_move.X == AlchemyGame::BOARD_WIDTH){
		right = AlchemyGame::SYMBOL_BLANK;
	}else{
		right = m_board.getSymbol(m_current_move.Y,m_current_move.X+1);
	}
	Symbol bottom;
	if(m_current_move.Y == AlchemyGame::BOARD_HEIGHT){
		bottom = AlchemyGame::SYMBOL_BLANK;
	}else{
		bottom = m_board.getSymbol(m_current_move.Y+1, m_current_move.X);
	}

	bool matching_edge = false;
	if(m_current_symbol == AlchemyGame::SYMBOL_WILDCARD){
		// wildcard, valid for any place adjacent to any symbol
		if(left != AlchemyGame::SYMBOL_BLANK){
			score += 5;
		}
		if(right != AlchemyGame::SYMBOL_BLANK){
			score += 5;
		}
		if(top != AlchemyGame::SYMBOL_BLANK){
			score += 5;
		}
		if(bottom != AlchemyGame::SYMBOL_BLANK){
			score += 5;
		}
	}else{
		// check left
		if(left == AlchemyGame::SYMBOL_WILDCARD
			|| left.getCharacter() == m_current_symbol.getCharacter()
			|| left.getColor() == m_current_symbol.getColor()){
			score += 5;
		}

		// check right
		if(right == AlchemyGame::SYMBOL_WILDCARD 
			|| right.getCharacter() == m_current_symbol.getCharacter() 
			|| right.getColor() == m_current_symbol.getColor()){
			score += 5;
		}

		// check top
		if(top == AlchemyGame::SYMBOL_WILDCARD 
			|| top.getCharacter() == m_current_symbol.getCharacter() 
			|| top.getColor() == m_current_symbol.getColor()){
			score += 5;
		}

		// check bottom
		if(bottom == AlchemyGame::SYMBOL_WILDCARD 
			|| bottom.getCharacter() == m_current_symbol.getCharacter() 
			|| bottom.getColor() == m_current_symbol.getColor()){
			score += 5;
		}
	}
	m_score += score;
}

/**********************************************************************	
* Purpose: This function checks if the background is entirely gold (completed)
*
* Entry: None.
*
* Exit: Returns a bool representing the level's completion status.
*
************************************************************************/
bool AlchemyGame::LevelComplete(){
	bool level_completed = true;
	for(int r = 1; r <= AlchemyGame::BOARD_HEIGHT; ++r){
		for(int c = 1; c <= AlchemyGame::BOARD_WIDTH; ++c){
			if(!m_board.getGolden(r,c)){
				level_completed = false;
				break;
			}
		}
		if(!level_completed){
			break;
		}
	}
	return level_completed;
}

/**********************************************************************	
* Purpose: Utility function to set up the console title, font size and window size.
*
* Entry: None.
*
* Exit: Console has larger font size, fixed window size, custom title
*
************************************************************************/
void AlchemyGame::SetUpConsoleWindow(){
	HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE rHnd = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleTitle(TEXT("Lab 1 - Alchemy by Andrew Sparkes"));

	// set up the window size and buffer size (for no scrollbars)
	SMALL_RECT windowSize = {0, 0, AlchemyGame::GAME_WIDTH-1, AlchemyGame::GAME_HEIGHT-1};
	COORD bufferSize = {AlchemyGame::GAME_WIDTH, AlchemyGame::GAME_HEIGHT};

	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	SetConsoleScreenBufferSize(wHnd, bufferSize);

	// now, set the font size bigger so you don't need a microscope to play the game
	CONSOLE_FONT_INFOEX CurrentFontInfoEx;
	CurrentFontInfoEx.cbSize = sizeof(CONSOLE_FONT_INFOEX); // required so GetCurrentConsoleFontEx doesn't choke
	GetCurrentConsoleFontEx(wHnd, false, &CurrentFontInfoEx);
	CurrentFontInfoEx.dwFontSize.X = 12;
	CurrentFontInfoEx.dwFontSize.Y = 16;
	SetCurrentConsoleFontEx(wHnd, false, &CurrentFontInfoEx);
}

/**********************************************************************	
* Purpose: This function generates a random symbol using the probability 
*	logic described in it
*
* Entry: None.
*
* Exit: A random symbol is returned
*
************************************************************************/
Symbol AlchemyGame::getRandomSymbol(){
	Symbol randomSymbol;

	// chance out of 10000, 1% would be 100, allows tuning down to nearest hundredth of a percent
	int chance_of_special = 500;

	// if the user rolls a special, the below determines which special. 
	// If both weights are the same, both have a 50/50. 
	// i.e. if bomb_weight = 3 and wildcard_weight = 1, the player will roll a bomb 3x more often than a wildcard
	int bomb_weight = 5;
	int wildcard_weight = 5;


	int first_rng_roll = RandomNumberGenerator::generate(1,10000);
	if(first_rng_roll <= chance_of_special){
		// user rolled a special, determine which
		int second_rng_roll = RandomNumberGenerator::generate(1,bomb_weight+wildcard_weight);
		if(second_rng_roll <= bomb_weight){
			// user rolled a bomb
			randomSymbol = AlchemyGame::SYMBOL_BOMB;
		}else{
			// user rolled a wildcard
			randomSymbol = AlchemyGame::SYMBOL_WILDCARD;
		}
	}else{
		// user rolled a normal symbol
		int color = AlchemyGame::AVAILABLE_SYMBOL_COLORS[RandomNumberGenerator::generate(0,m_num_colors-1)];
		char character = AlchemyGame::AVAILABLE_SYMBOL_CHARS[RandomNumberGenerator::generate(0,m_num_symbols-1)];
		randomSymbol = Symbol(character, color);
	}
	return randomSymbol;
}

/**********************************************************************	
* Purpose: This function checks to see if a row or col on the current 
*	move has been completed, and if so, remove that whole col/row
*
* Entry: Designed to be called right after a call to PlaceSymbol()
*
* Exit: If appropriate, the row/col is blank'd out, retaining its gold state.
*
************************************************************************/
void AlchemyGame::CheckRowCol(){
	// check if the current col/row are complete, and if so, blank them out
	bool row_complete = true;
	bool col_complete = true;

	// first row
	for(int i = 1; i <= AlchemyGame::BOARD_WIDTH && row_complete; ++i){
		if(m_board.getSymbol(m_current_move.Y, i) == AlchemyGame::SYMBOL_BLANK){
			row_complete = false;
		}
	}

	// then col
	for(int i = 1; i <= AlchemyGame::BOARD_HEIGHT && col_complete; ++i){
		if(m_board.getSymbol(i, m_current_move.X) == AlchemyGame::SYMBOL_BLANK){
			col_complete = false;
		}
	}

	if(row_complete){
		for(int i = 1; i <= AlchemyGame::BOARD_WIDTH; ++i){
			m_board.setSymbol(m_current_move.Y, i, AlchemyGame::SYMBOL_BLANK);
		}
	}

	if(col_complete){
		for(int i = 1; i <= AlchemyGame::BOARD_HEIGHT; ++i){
			m_board.setSymbol(i, m_current_move.X, AlchemyGame::SYMBOL_BLANK);
		}
	}
}