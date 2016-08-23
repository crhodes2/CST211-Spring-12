/***********************************************************
* Author:		Andrew Sparkes
* Title:		CST 211 Assignment 6
* Filename:		main.cpp
* Date Created:	4-29-12
* Modified:		4-30-12 : documentation, small tweaks
*
* Overview:
*	This program is a driver demonstrating the basic 
*	capabilities of array-based stack class.
*
* Input:
*	None.
*
* Output:
*	Will output a basic test of the array-based stack class.
************************************************************/
#include "Stack.h"

#include <iostream>
using std::cout;
using std::endl;

#include <crtdbg.h> 
#define _CRTDBG_MAP_ALLOC

int main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Stack<int> stk(3);

	// push 3 values on to the stack, filling it
	stk.Push(123);
	cout << stk.Peek() << endl;

	stk.Push(456);
	cout << stk.Peek() << endl;

	stk.Push(789);
	cout << stk.Peek() << endl;

	// try to push another onto the stack, should result in overflow
	try{
		stk.Push(10000);
		cout << stk.Peek() << endl;
	}catch(Exception e){
		cout << e << endl;
	}
	
	// pop all the values off the stack, leaving it empty
	cout << stk.Pop() << endl;
	cout << stk.Pop() << endl;
	cout << stk.Pop() << endl;

	// then try to pop off the empty stack
	try{
		cout << stk.Pop() << endl;
	}catch(Exception e){
		cout << e << endl;
	}
	
	// output current size of stack
	cout << stk.Size() << endl;

	// push some values onto stack and watch the size increase
	stk.Push(1);
	cout << stk.Size() << endl;
	stk.Push(2);
	cout << stk.Size() << endl;
	stk.Push(3);
	cout << stk.Size() << endl;


	// stack size should be 3 now
	// pop the top value off and push another on and watch the size
	stk.Pop();
	cout << stk.Size() << endl;
	stk.Push(555);
	cout << stk.Size() << endl;

	// take a peek at top of stack, should be 555
	cout << stk.Peek() << endl;


	system("pause");
	return 0;
}