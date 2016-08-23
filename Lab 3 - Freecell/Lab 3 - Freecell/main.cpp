/***********************************************************
* Author:		Andrew Sparkes
* Title:		CST 211 Lab 3 - Freecell
* Filename:		main.cpp
* Date Created:	4-8-12
* Modified:		6-7-12 4:58am - Fuck my life...
*
* Overview:
*	This program is the game Freecell.
*
* Input:
*	Will take input from keyboard.
*
* Output:
*	Will output game menu/board to console screen.
************************************************************/
#include "FreeCellGame.h"

#include <crtdbg.h> 
#define _CRTDBG_MAP_ALLOC

#include <iostream>

int main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	FreeCellGame game;
	game.Start();
	/*
	smatch result;
	string test = "A10";

	if(regex_search(test, result, regex("^([a-zA-Z])([1-9][0-9]?)$")))
	{
		cout << "success: col " << result[1] << ", row " << result[2] << endl;
	}else{
		cout << "fail" << endl;
	}*/
	system("pause");
	return 0;
}
