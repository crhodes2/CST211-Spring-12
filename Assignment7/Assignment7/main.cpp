/***********************************************************
* Author:		Andrew Sparkes
* Title:		CST 211 Assignment 7
* Filename:		main.cpp
* Date Created:	4-29-12
* Modified:		4-30-12 : documentation, small tweaks
*
* Overview:
*	This program is a driver demonstrating the basic 
*	capabilities of list-based stack class.
*
* Input:
*	None.
*
* Output:
*	Will output a basic test of the list-based stack class.
************************************************************/
#include <iostream>
using std::cout;
using std::endl;

#include <crtdbg.h> 
#define _CRTDBG_MAP_ALLOC

#include "Stack.h"
#include "Exception.h"

int main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	Stack<int> stk;

	stk.Push(123);
	cout << stk.Peek() << endl;

	stk.Push(456);
	cout << stk.Peek() << endl;

	stk.Push(789);
	cout << stk.Peek() << endl;
	
	
	cout << stk.Pop() << endl;
	cout << stk.Pop() << endl;
	cout << stk.Pop() << endl;
	try{
		cout << stk.Pop() << endl;
	}catch(Exception e){
		cout << e << endl;
	}
	
	cout << stk.Size() << endl;
	stk.Push(1);
	cout << stk.Size() << endl;
	stk.Push(2);
	cout << stk.Size() << endl;
	stk.Push(3);
	cout << stk.Size() << endl;

	stk.Pop();
	cout << stk.Size() << endl;
	stk.Push(555);
	cout << stk.Size() << endl;

	
	cout << stk.Peek() << endl;

	system("pause");
	return 0;
}