#include "FreeCellGame.h"


FreeCellGame::FreeCellGame(void)
{
}


FreeCellGame::~FreeCellGame(void)
{
}


void FreeCellGame::Start(void)
{
	SetUpConsoleWindow();

	// display menu
	bool error = false;
	int menu_choice = -1;
	
	while(error || menu_choice != 0){
		try{
			menu_choice = MainMenu();
			ProcessMainMenuChoice(menu_choice);
			error = false;
		}catch(Exception e){
			cout << e << endl;
			error = true;
			system("pause");
		}
	}
}

void FreeCellGame::ProcessMainMenuChoice(int menu_choice)
{
	bool exit = false;

	ResetGame(); // resetting the game to defaults

	switch(static_cast<FreeCellGame::MENU_CHOICES>(menu_choice)){
		case CUSTOM_SEED:
			CustomSeed();
			break;
		case NEW_GAME:
			RandomSeed();
			break;
		case HELP:
			ShowHelp();
			break;
		case EXIT:
			exit = true;
			break;
		default:
			throw Exception("Invalid menu choice. Expecting 0, 1, 2, or 3.");
	}

	if(static_cast<FreeCellGame::MENU_CHOICES>(menu_choice) == CUSTOM_SEED || static_cast<FreeCellGame::MENU_CHOICES>(menu_choice) == NEW_GAME){
		DealDeckToPlayArea();
		MainGameLoop();
	}
}

int FreeCellGame::MainMenu()
{
	int choice = -1;

	system("cls");
	cout << "Welcome to FreeCell!" << endl;
	cout << endl;
	cout << "1) New Game" << endl;
	cout << "2) Custom Seed Game" << endl;
	cout << "3) Help" << endl;
	cout << "0) Exit" << endl;
	cout << endl;
	cout << "Enter Menu Choice: ";
	cin >> choice;

	bool cinIsGood = cin.good();
	cin.clear();
	cin.ignore(INT_MAX,'\n');

	if (!cinIsGood || choice < 0 || choice > 3) {
		throw Exception("Invalid menu choice.");
	}
	return choice;
}

void FreeCellGame::CustomSeed(void)
{
	string seed;
	system("cls");
	cout << "Please input the seed below (1 for debug config): " << endl;
	cin >> seed;

	if(atoi(seed.c_str()) == 1){
		cout << "Debug config detected..." << endl;
		seed = "001020300111213102122232031323330414243405152535061626360717273708182838091929390a1a2a3a0b1b2b3b0c1c2c3c";
	}

	// check length of seed
	if(seed.length() != 52*2)
	{
		throw Exception("Invalid seed");
	}

	// check if length is even
	if(seed.length() % 2 == 1)
	{
		throw Exception("Invalid seed");
	}
		
	// now, iterate over the seed
	Card::RANK rank;
	Card::SUIT suit;
	string temp = "";
	Card newCard;

	// remove all current cards from all areas
	m_deck.Purge();
	string::const_iterator it = seed.begin();
	while(it != seed.end()){
		temp = *it;
		suit = static_cast<Card::SUIT>(strtol(temp.c_str(), nullptr, 16));
		if(suit < 0 || suit > Card::SUIT_COUNT){
			throw Exception("Invalid seed: Invalid suit code");
		}
		it++;

		temp = *it;
		rank = static_cast<Card::RANK>(strtol(temp.c_str(), nullptr, 16));
		if(rank < 0 || rank > Card::RANK_COUNT){
			throw Exception("Invalid seed: Invalid rank code");
		}
		it++;

		newCard = Card(suit, rank);
		cout << "Pushing " << newCard << " onto deck..." << endl;
		m_deck.Add(newCard);
	}

	// now, make sure that the cards passed in equate to a valid deck, i.e. not 52 ace of spades, etc
	bool validDeck = true;
	for(int rank = 0; rank < Card::RANK_COUNT && validDeck; ++rank)
	{
		for(int suit = 0; suit < Card::SUIT_COUNT && validDeck; ++suit)
		{
			if(m_deck.Count(Card(static_cast<Card::SUIT>(suit), static_cast<Card::RANK>(rank))) != 1)
			{
				validDeck = false;
			}
		}
	}
	if(!validDeck)
	{
		throw Exception("Invalid seed: Seed is not a standard 52 card deck permutation.");
	}

	system("pause");
}

void FreeCellGame::RandomSeed(void)
{
	m_deck.Purge();
	m_deck.SingleDeck();
	m_deck.Shuffle();
}


void FreeCellGame::MainGameLoop(void)
{
	bool exit = false;
	bool winner = false;
	while(!(winner = GameWon()) && !exit)
	{
		DisplayTable();
		string move = GetInput();
		if(move == "exit" || move == "quit" || move == "menu")
		{
			exit = true;
		}
		else
		{
			try
			{
				ResolveMove(move);
			}
			catch(Exception e)
			{
				cout << e << endl;
				system("pause");
			}
		}
	}
	if(winner)
	{
		system("cls");
		cout << "You win!" << endl;
		cout << "Wooooooooooooo!" << endl;
		system("pause");
	}
}

void FreeCellGame::DealDeckToPlayArea(void)
{
	Card drawnCard;

	unsigned stack_index = 0;
	while(m_deck.Length())
	{
		drawnCard = m_deck.Draw();
		m_table.m_playArea.AddCard(drawnCard, (stack_index++)%8 );
	}
}


void FreeCellGame::ResetGame(void)
{
	// resets the game to default (in the case of starting a new game, etc)
	GameTable new_table;
	m_table = new_table;

	
	m_deck.Purge();
}

void FreeCellGame::SetUpConsoleWindow(void)
{
	HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE rHnd = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleTitle(TEXT("Lab 3 - Freecell by Andrew Sparkes"));

	// set up the window size and buffer size (for no scrollbars)
	COORD bufferSize = {FreeCellGame::CONSOLE_WIDTH, FreeCellGame::CONSOLE_HEIGHT};
	SMALL_RECT windowSize = {0, 0, bufferSize.X-1, bufferSize.Y-1};

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

bool FreeCellGame::GameWon(void)
{
	bool gameWon = true;
	
	for(int i = 0; i < 4 && gameWon; ++i)
	{
		if(m_table.m_homeCellArea.TopCard(i) != Card(static_cast<Card::SUIT>(i), Card::RANK_KING))
		{
			gameWon = false;
		}
	}

	return gameWon;
}

void FreeCellGame::DisplayTable()
{
	COORD freeCellOffset = {1,1};
	COORD homeCellOffset = {20,1};
	COORD playAreaOffset = {2,5};
	COORD commandOffset = {5,28};

	COORD cursorPos = {0,0};

	system("cls");
	HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);

	// first output the free cell area
	cursorPos = freeCellOffset;
	SetConsoleCursorPosition(wHnd, cursorPos);
	cout << "Free Cells";
	for(int i = 0; i < 4; ++i)
	{
		cursorPos.Y = freeCellOffset.Y + 1;
		SetConsoleCursorPosition(wHnd, cursorPos);
		cout << m_table.m_freeCellArea.m_cards[i];

		cursorPos.Y += 1;
		SetConsoleCursorPosition(wHnd, cursorPos);
		cout << " " << i+1 << " ";

		cursorPos.X += 4; // knock it over for the next free cell
	}

	// now output the home cell area
	cursorPos = homeCellOffset;
	SetConsoleCursorPosition(wHnd, cursorPos);
	cout << "Home Cells";
	for(int i = 0; i < 4; ++i)
	{
		cursorPos.Y = homeCellOffset.Y + 1;
		SetConsoleCursorPosition(wHnd, cursorPos);
		cout << m_table.m_homeCellArea.TopCard(i);
		cursorPos.Y += 1;
		SetConsoleCursorPosition(wHnd, cursorPos);
		cout << " " << i+1 << " ";
		cursorPos.X += 4; // knock it over for the next free cell
	}

	// now output the play area
	// first, the border with row/col labels
	cursorPos = playAreaOffset;
	cursorPos.X +=3;
	for(char c = 'A'; c < 'I'; ++c){
		SetConsoleCursorPosition(wHnd, cursorPos);
		cout << c;
		cursorPos.X += 4;
	}
	cursorPos = playAreaOffset;
	cursorPos.Y += 1;
	for(int i = 1; i < 21; ++i){
		SetConsoleCursorPosition(wHnd, cursorPos);
		cout << i;
		cursorPos.Y += 1;
		if(i==9)
		{
			cursorPos.X -= 1;
		}
	}

	// now output the stacks of cards that comprise the play area
	cursorPos = playAreaOffset;
	cursorPos.X += 2;
	cursorPos.Y += 1;
	for(int i = 0; i < 8; ++i)
	{
		// iterate over each element in the stack and output it
		// an iterator doesn't make sense for a stack, so we duplicate the stack temporarily,
		// and pop all the elements into a STL vector, then output them in reverse to preserve the order
		vector<Card> currentStack;
		currentStack.reserve(m_table.m_playArea.m_cards.getLength());

		ListBasedStack<Card> copy(m_table.m_playArea.m_cards[i]);
		while(!copy.isEmpty())
		{
			currentStack.push_back(copy.Pop());
		}
		
		for(vector<Card>::reverse_iterator it = currentStack.rbegin(); it != currentStack.rend(); ++it)
		{
			SetConsoleCursorPosition(wHnd, cursorPos);
			cout << *it;
			cursorPos.Y += 1;
		}
		currentStack.clear();
		copy.~ListBasedStack();

		cursorPos.Y = playAreaOffset.Y + 1;
		cursorPos.X += 4;
	}

	// and finally, output the command prompt
	cursorPos = commandOffset;
	SetConsoleCursorPosition(wHnd, cursorPos);
	cout << "Command:";

	cursorPos.X += 9;
	SetConsoleCursorPosition(wHnd, cursorPos);
}

string FreeCellGame::GetInput()
{
	string input;
<<<<<<< .mine

	cin.ignore(cin.rdbuf()->in_avail());
	cin.clear();

=======
	cin.ignore(cin.rdbuf()->in_avail());
>>>>>>> .r308
	getline(cin, input);

<<<<<<< .mine
=======
	//std::cin.ignore(INT_MAX);
	//std::cin.clear();

>>>>>>> .r308
	return input;
}

void FreeCellGame::ResolveMove(string move)
{
	const char delimiter = ' ';

	cout << "Attempting to resolve move: " << move << "..." << endl;

<<<<<<< .mine
	string first_command;
	string second_command;

	string::const_iterator it = move.begin();
	unsigned delimitersFound = 0;

	while(it != move.end()){
		if(*it ==  delimiter)
		{
			++delimitersFound;
		}
		else
		{
			if(!delimitersFound)
			{
				first_command += *it;
			}
			else
			{
				second_command += *it;
			}
		}
		
		it++;
	}
	
	cout << "First command: " << first_command << "." << endl;
	cout << "Second command: " << second_command << "." << endl;

	if(first_command.substr(0,4) == "home")
	{
		throw Exception("Can't move a card from home.");
	}
	else if(first_command.substr(0,4) == "help")
	{
		ShowHelp();
	}else{
		if(ValidateMove(first_command, second_command))
		{
			PerformMove(first_command, second_command);
			system("pause");
		}else{
			throw Exception("Invalid move/command.");
		}
	}
}

void FreeCellGame::ShowHelp(void)
{
	system("cls");
	cout << "---Freecell Help----------------------" << endl;
	cout << endl;
	cout << "In-game Commands:                             " << endl;
	cout << "  exit/quit: Exits to the menu" << endl;
	cout << "  help: Shows this screen" << endl;
	cout << "                          " << endl;
	cout << "Command syntax: [source] [destination]" << endl;
	cout << "If source card is in free cell, must be denoted free1, free2 etc." << endl;
	cout << "If source card is in playarea, must be denoted A1, H4, etc (indicating row/col)" << endl;
	cout << "If destination is either home or free, typing home/free suffices. See Examples" << endl;
	cout << "If destination is playarea, the column will suffice, ie. A, B, D, F, etc." << endl;
	cout << "" << endl;
	cout << "Examples:" << endl;
	cout << "  A8 free: Moves the card in column A, row 8 to a free cell" << endl;
	cout << "  free2 home: Moves card in the second free cell to its appropriate home cell" << endl;
	cout << "  C5 D: Moves the card/stack at C5 to column D" << endl;
	cout << "  B7 home: Moves the card at B7 to its appropriate home cell." << endl;
	cout << endl;
=======
	regex toHome(" home$", std::tr1::regex_constants::icase);
	regex toPlay(" ([ABCDEFGH])$", std::tr1::regex_constants::icase);
	regex toFree(" free$", std::tr1::regex_constants::icase);
	regex fromPlay("^([ABCDEFGH]{1})([0-9]{1,2}) ", std::tr1::regex_constants::icase);
	regex fromFree("^free([1234]) ", std::tr1::regex_constants::icase);

	if(!regex_search(move.begin(), move.end(), fromPlay)
		&& !regex_search(move.begin(), move.end(), fromFree))
	{
		throw Exception("Invalid source move");
	}

	if(!regex_search(move.begin(), move.end(), toPlay)
		&& !regex_search(move.begin(), move.end(), toFree)
		&& !regex_search(move.begin(), move.end(), toHome))
	{
		throw Exception("Invalid destination move");
	}

	// if we've made it to here, the moves are at least valid syntactically
	// now, determine which combination we have and attempt further resolution/ game rules
	cmatch from;
	cmatch to;

	Card card; // will make things a bit more readable later

	if(regex_search(move.c_str(), from, fromPlay) && regex_search(move.c_str(), to, toHome))
	{
		// from play to home

		// make sure card exists at play location
		// make sure it's a single card
		if(m_table.m_playArea.m_cards[strtol(from[1].str().c_str(), nullptr, 18)-10].Size() != atoi(from[2].str().c_str()))
		{
			// the move does not correspond to the top of a stack, i.e. it's multiple cards instead of a single or simply doesn't exist, disallow
			throw Exception("Card doesn't exist or multiple cards selected.");
		}
		
		card = m_table.m_playArea.m_cards[strtol(from[1].str().c_str(), nullptr, 18)-10].Peek();

		// make sure card is suitable to throw at home cell area
		if((m_table.m_homeCellArea.m_cards[card.GetSuit()].isEmpty() && card.GetRank() == Card::RANK_ACE)
			|| m_table.m_homeCellArea.m_cards[card.GetSuit()].Peek().GetRank() == static_cast<Card::RANK>(card.GetRank() - 1))
		{
			// pop it from play area to home cell area
			m_table.m_playArea.m_cards[strtol(from[1].str().c_str(),nullptr, 18)-10].Pop();
			m_table.m_homeCellArea.AddCard(card);
		}
			

	}
	else if(regex_search(move.c_str(), from, fromPlay) && regex_search(move.c_str(), to, toFree))
	{
		// from play to free

		// make sure card exists at play location
		// make sure it's a single card
		if(m_table.m_playArea.m_cards[strtol(from[1].str().c_str(), nullptr, 18)-10].Size() != atoi(from[2].str().c_str()))
		{
			// the move does not correspond to the top of a stack, i.e. it's multiple cards instead of a single or simply doesn't exist, disallow
			throw Exception("Card doesn't exist or multiple cards selected.");
		}
		
		card = m_table.m_playArea.m_cards[strtol(from[1].str().c_str(), nullptr, 18)-10].Peek();

		// if card exists, check if there is room in free area
		if(m_table.m_freeCellArea.GetRemaining())
		{
			// pop card from play area to the free area
			m_table.m_playArea.m_cards[strtol(from[1].str().c_str(), nullptr, 18)-10].Pop();
			m_table.m_freeCellArea.AddCard(card);
		}
		else
		{
			throw Exception("Not any more room in free cell area!");
		}
	}
	else if(regex_search(move.c_str(), from, fromPlay) && regex_search(move.c_str(), to, toPlay))
	{
		// from play to play
		stack<Card> cardStack;

		// make sure card exists at play location (from only)
		if(m_table.m_playArea.m_cards[strtol(from[1].str().c_str(), nullptr, 18)-10].Size() < atoi(from[2].str().c_str()))
		{
			throw Exception("Card does not exist!");
		}

		try
		{
			// if card is NOT top of stack, verify that the stack on top of it is a proper ordered/alternating stack
			while(m_table.m_playArea.m_cards[strtol(from[1].str().c_str(), nullptr, 18)-10].Size() > atoi(from[2].str().c_str()))
			{
				if(cardStack.empty()
					|| (m_table.m_playArea.m_cards[strtol(from[1].str().c_str(), nullptr, 18)-10].Peek().isRed() != cardStack.top().isRed()
					&& m_table.m_playArea.m_cards[strtol(from[1].str().c_str(), nullptr, 18)-10].Peek().GetRank() == static_cast<Card::RANK>(cardStack.top().GetRank()+1)))
				{
					cardStack.push(m_table.m_playArea.m_cards[strtol(from[1].str().c_str(), nullptr, 18)-10].Pop());
				}
				else
				{
					throw Exception("Invalid stack!");
				}

				if(cardStack.size() > m_table.m_freeCellArea.GetRemaining())
				{
					throw Exception("Can't move that many cards!");
				}
			}
					
			// make sure the from card is proper color/rank to be put on top of to stack
			if(m_table.m_playArea.m_cards[strtol(from[1].str().c_str(), nullptr, 18)-10].Peek().GetRank() == static_cast<Card::RANK>(m_table.m_playArea.m_cards[strtol(to[1].str().c_str(), nullptr, 18)-10].Peek().GetRank() - 1)
				&& m_table.m_playArea.m_cards[strtol(from[1].str().c_str(), nullptr, 18)-10].Peek().isRed() != m_table.m_playArea.m_cards[strtol(to[1].str().c_str(), nullptr, 18)-10].Peek().isRed() )
			{
				// kosher, continue
				// pop cards to where they need to be
				card = m_table.m_playArea.m_cards[strtol(from[1].str().c_str(), nullptr, 18)-10].Pop();
				cardStack.push(card);
				
				while(cardStack.size())
				{
					m_table.m_playArea.m_cards[strtol(to[1].str().c_str(), nullptr, 18)-10].Push(cardStack.top());
					cardStack.pop();
				}
			}
			else
			{
				throw Exception("Top of selected stack can't be moved to destination!");
			}


		}
		catch(Exception e)
		{
			// if anything triggers an error, put the cards back where they need to be
			while(cardStack.size())
			{
				m_table.m_playArea.m_cards[strtol(from[1].str().c_str(), nullptr, 18)-10].Push(cardStack.top());
				cardStack.pop();
			}
			throw e; // let the next catch block deal with it
		}

	}
	else if(regex_search(move.c_str(), from, fromFree) && regex_search(move.c_str(), to, toPlay))
	{
		// from free to play

		card = m_table.m_freeCellArea.PeekCard(atoi(from[1].str().c_str())-1); // remember 1based vs 0based, hence -1

		// make sure free card exists
		if(card.isBlank()) 
		{
			throw Exception("No card at free cell location");
		}

		// make sure free card is able to be placed on to stack, i.e. descending/alternating or empty stack
		if(m_table.m_playArea.m_cards[strtol(to[1].str().c_str(), nullptr, 18)-10].isEmpty()
			|| (m_table.m_playArea.m_cards[strtol(to[1].str().c_str(), nullptr, 18)-10].Peek().GetRank() == static_cast<Card::RANK>(card.GetRank() + 1)
				&& m_table.m_playArea.m_cards[strtol(to[1].str().c_str(), nullptr, 18)-10].Peek().isRed() != card.isRed())
			)
		{
			// pop card off free and into play col's stack
			m_table.m_freeCellArea.PopCard(atoi(from[1].str().c_str())-1);
			m_table.m_playArea.AddCard(card, strtol(to[1].str().c_str(), nullptr, 18)-10);
		}
	}
	else if(regex_search(move.c_str(), from, fromFree) && regex_search(move.c_str(), to, toHome))
	{
		// from free to home
		
		card = m_table.m_freeCellArea.PeekCard(atoi(from[1].str().c_str())-1); // remember 1based vs 0based, hence -1

		// make sure free card exists
		if(card.isBlank()) 
		{
			throw Exception("No card at free cell location");
		}

		// make sure it's able to be placed in home
		if((m_table.m_homeCellArea.m_cards[card.GetSuit()].isEmpty() && card.GetRank() == Card::RANK_ACE)
			|| m_table.m_homeCellArea.TopCard(card.GetSuit()).GetRank() == static_cast<Card::RANK>(card.GetRank() - 1))
		{
			// pop from free to home
			m_table.m_freeCellArea.PopCard(atoi(from[1].str().c_str())-1);
			m_table.m_homeCellArea.AddCard(card);
		}
	}
	else
	{
		throw Exception("Unknown move error");
	}
>>>>>>> .r308
	system("pause");
}

bool FreeCellGame::ValidateMove(string first, string second)
{
	bool valid = true;
	// debug fix here
	return valid;

	bool fromFree = false;
	bool fromHome = false;
	bool fromPlay = false;
	bool toFree = false;
	bool toHome = false;
	bool toPlay = false;
	
	// begin bastardized regex
	if(regex_match(first, regex("^free[1-4]$")))
	{
		fromFree = true;
	}
	else if(regex_match(first, regex("^home[1-4]$")))
	{
		fromHome = true;
	}
	else if(regex_match(first, regex("^[a-zA-Z][1-9][0-9]?$")))
	{
		fromPlay = true;
	}

	if(regex_match(second, regex("^free$")))
	{
		toFree = true;
	}
	else if(regex_match(second, regex("^home$")))
	{
		toHome = true;
	}
	else if(regex_match(second, regex("^[a-zA-Z]$")))
	{
		toPlay = true;
	}

	// broken into separate ifs solely for readability of invalidating conditions
	if( !(fromHome || fromFree || fromPlay) && !(toHome || toFree || toPlay) )
	{
		// we don't even have a full valid move, as one/both the pieces are invalid
		valid = false;
	}
	else if(fromHome) // can't move cards from home cells
	{
		valid = false;
	}
	else if(fromFree && toFree) // can't move free to free
	{
		valid = false;
	}
	else if(toFree && m_table.m_freeCellArea.GetRemaining() == 0) // can't move cards to free cells if they're full already
	{
		valid = false;
	}

	// if we've made it to here, at least the syntax and bounds of the move are valid, as well as basic sanity checking

	if(valid){

		// generic regex variables that will be used later
		smatch result;

		// variables representing card positions
		// from play
		string fromCol;
		string fromRow;
		// from free
		string fromFreeIndex;
		// to play
		string toCol;

		if(fromPlay){
			// get from coords
			if(!regex_search(first, result, regex("^([a-zA-Z])([1-9][0-9]?)$"))){
				throw Exception("catastrophic regex failure");
			}

			int row = atoi(result[2].str().c_str());
			int col = tolower(result[1].str().c_str()[0])-96; // hacky method of getting the single letter string converted to an int
			
			if(row <= m_table.m_playArea.m_cards[col].Size() ) // have to make sure the row won't cause an exception
			{
				if(GetPlayAreaCardByCoord(col, row).isBlank()) // make sure there is a card in the source position
				{
					throw Exception("There is no card in the specified play area");
				}
			}
			if(toPlay)
			{
				// handle coordinates
				// determine source card
				// check that card against top of dest stack
				// make sure cards below source card are alternating and descending
			}
			else if(toFree)
			{
				// make sure single card
			}
			else if(toHome)
			{
				if(GetCardByBoardCoord(first) != m_table.m_playArea.m_cards[col].Peek()) // make sure single card (if the top of the stack is the given card, we're kosher)
				{
					throw Exception("Trying to move a stack to home cells is not allowed");
				}
				// make sure card in proper stack is one lower than the current source card
			}
		}
		else if(fromFree)
		{
			// make sure there is a card in the source location
			if(GetCardByBoardCoord(first).isBlank())
			{
				throw Exception("Source free cell is blank.");
			}

			if(toPlay)
			{
				// make sure top card on whichever column is one higher rank and opposite color
			}
			else if(toHome)
			{
				// make sure card in proper stack is one lower than the current source card
			}

		}
	}


	return valid;
}

void FreeCellGame::PerformMove(string first, string second)
{
	smatch firstresult;
	smatch secondresult;
	bool fromPlay = false;
	bool fromFree = false;
	bool toPlay = false;
	bool toFree = false;
	bool toHome = false;
	int fromRow = 0;
	int fromCol = 0;
	int fromIndex = 0;
	int toCol = 0;

	if(regex_search(first, firstresult, regex("^([a-zA-Z])([1-9][0-9]?)$")))
	{
		fromPlay = true;
		fromRow = atoi(firstresult[2].str().c_str());
		fromCol = tolower(firstresult[1].str().c_str()[0])-96; // hacky method of getting the single letter string converted to an int
		fromCol -= 1; // remember, the array is 0based. 
	}
	else if(regex_search(first, firstresult, regex("^free([1-4])$")))
	{
		fromFree = true;
		fromIndex = atoi(firstresult[1].str().c_str());
	}

	if(regex_search(second, secondresult, regex("^([a-zA-Z])$")))
	{
		toPlay = true;
		toCol = atoi(secondresult[1].str().c_str());
	}
	else if(regex_search(second, secondresult, regex("^free$")))
	{
		toFree = true;
	}
	else if(regex_search(second, secondresult, regex("^home$")))
	{
		toHome = true;
	}

	// now that we know source and destination, handle the move appropriately
	
	if(fromPlay && toPlay)
	{
		// popping all the cards below the stack onto free cells
		int count = 0;
		while(m_table.m_playArea.m_cards[fromCol].Peek() != GetPlayAreaCardByCoord(fromCol, fromRow))
		{
			m_table.m_freeCellArea.AddCard(m_table.m_playArea.m_cards[fromCol].Pop());
			++count;
		}

		// move the source card over
		m_table.m_playArea.m_cards[toCol].Push(m_table.m_playArea.m_cards[fromCol].Pop());

		// and finally move the rest of the stack over
		while(count)
		{
			m_table.m_playArea.m_cards[toCol].Push(m_table.m_freeCellArea.PopCard());
			--count;
		}
	}
	else if(fromPlay && toFree)
	{
		m_table.m_freeCellArea.AddCard(m_table.m_playArea.m_cards[fromCol].Pop()); // need to fix freecellarea::addcard first
	}
	else if(fromPlay && toHome)
	{
		Card tempCard = m_table.m_playArea.m_cards[fromCol].Pop(); // pop the top card off to be pushed to proper spot in home cells
		// remember that this is only applicable for a single card, not a stack

		// push that card into the proper homecell
		m_table.m_homeCellArea.m_cards[tempCard.GetSuit()].Push(tempCard);
	}
	else if(fromFree && toPlay)
	{
		m_table.m_playArea.m_cards[toCol].Push(m_table.m_freeCellArea.PopCard());
	}
	else if(fromFree && toHome)
	{
		Card tempCard = m_table.m_freeCellArea.PopCard(); // pop the card off the freecell area

		// push that card into the proper homecell
		m_table.m_homeCellArea.m_cards[tempCard.GetSuit()].Push(tempCard);
	}
}

Card FreeCellGame::GetCardByBoardCoord(string coord)
{
	Card cardToReturn;
	smatch result;
	
	if(regex_search(coord, result, regex("^free([1-4])$")))
	{
		int index = atoi(result[1].str().c_str());
		if(index > m_table.m_freeCellArea.GetLength())
		{
			throw Exception("Free cell index out of bounds");
		}
		cardToReturn = m_table.m_freeCellArea.GetCardAt(index);
	}
	else if(regex_search(coord, result, regex("^([a-zA-Z])([1-9][0-9]?)$")))
	{
		int row = atoi(result[2].str().c_str());

		// determining column takes a bit more, as they are lettered on the game board
		int col = tolower(result[1].str().c_str()[0])-96; // hacky method of getting the single letter string converted to an int

		cardToReturn = GetPlayAreaCardByCoord(col, row);
	}
	else
	{
		throw Exception("Invalid coord passed to GetCardByBoardCoord()");
	}

	return cardToReturn;
}

Card FreeCellGame::GetPlayAreaCardByCoord(unsigned col, unsigned row)
{
	Card cardToReturn;
	
	// the stack is copy.size() long, and we want the row'th entry in the stack, so we pop elements off til it is at the right index and then peek
	if(row > m_table.m_playArea.m_cards[col].Size()){
		throw Exception("Invalid row access in GetCardByBoardCoord()");
	}
		
	// now, because we're using a stack when we honestly shouldn't be, 
	// we have to get creative to access elements w/o fucking it up
	ListBasedStack<Card> copy(m_table.m_playArea.m_cards[col]);
	while(copy.Size() > row)
	{
		copy.Pop(); // popping elements off into never never land until we find the one we want
	}
	cardToReturn = copy.Peek();
}