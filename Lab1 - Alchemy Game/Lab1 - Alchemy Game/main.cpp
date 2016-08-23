/***********************************************************
* Author:		Andrew Sparkes
* Title:		CST 211 Lab 1 - Alchemy
* Filename:		main.cpp
* Date Created:	4-8-12
* Modified:		4-8-12 : basic setup and organization
*				4-9-12 - 4-12-12 Fleshing classes out, menu 
*					design, input/output work, redid several 
*					class relationships, added 
*					randomnumbergenerator class, made board 
*					its own class, expanded responsibilities 
*					of some functions in AlchemyGame
*				4-13-12 : Swearing, testing, reorganizing, 
*					documentation, debugging
*
* Overview:
*	This program is the Popcap game, Alchemy, in console.
*
* Input:
*	Will take input from keyboard.
*
* Output:
*	Will output game menu/board to console screen.
************************************************************/
#include "AlchemyGame.h"
#include <crtdbg.h> 
#define _CRTDBG_MAP_ALLOC

int main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	AlchemyGame game;
	game.Start();

	return 0;
}
