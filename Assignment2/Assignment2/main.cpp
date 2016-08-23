/***********************************************************
* Author:		Andrew Sparkes
* Title:		CST 211 Assignment 2
* Filename:		main.cpp
* Date Created:	4-3-12
* Modified:		4-4-12 : rewrote large chunks of both classes
*				4-5-12 : wrote/rewrote most of documentation
*						 Added more to driver program
*
* Overview:
*	This program is a driver demonstrating the basic 
*	capabilities of 2D Array class.
*
* Input:
*	None.
*
* Output:
*	Will output a basic test of the Array2D class.
************************************************************/
#include "Array2D.h"
#include <iostream>
using std::cout;
using std::endl;
#include <crtdbg.h> 

#define _CRTDBG_MAP_ALLOC

template <class T>
void PrintArray(Array2D<T>& array);
template <class T>
void PrintArray(Array2D<T> const& array);

int main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Array2D<int> a1(2,3);
	a1[0][0] = 1;
	a1[1][0] = 7;
	a1[0][1] = 3;
	a1[1][1] = 44;
	a1[0][2] = 5;
	a1[1][2] = 25;

	PrintArray(a1);

	const Array2D<int> a2(a1);
	// The next line will stop the program from compiling due to a2 being const
	//a2[0][0] = 5;
	PrintArray(a2);

	Array2D<char*> a3(1,2);
	a3[0][0] = "First row/First col";
	a3[0][1] = "First row/Last col";
	PrintArray(a3);

	Array2D<char*> a4;
	a4 = a3;
	PrintArray(a4);

	Array2D<char*> a5(a4);
	PrintArray(a5);

	a5.setColumn(3);
	a5[0][2] = "Additional column in first row!";
	PrintArray(a5);

	a5.setColumn(2);
	PrintArray(a5);

	try{
		a5.setColumn(-5);
	}catch(Exception e){
		cout << "Exception: " << e << endl;
	}

	try{
		cout << a5[1][66] << endl;
	}catch(Exception e){
		cout << "Exception: " << e << endl;
	}



	system("pause");
	return 0;
}

template <class T>
void PrintArray(Array2D<T>& array){
	int rows = array.getRow();
	int cols = array.getColumn();

	cout << "Outputting array of dimensions " << rows << "x" << cols << endl;

	for(int r=0; r<rows; ++r){
		for(int c=0; c<cols; ++c){
			cout << array[r][c] << "\t";
		}
		cout << endl;
	}
}

template <class T>
void PrintArray(Array2D<T> const& array){
	int rows = array.getRow();
	int cols = array.getColumn();

	cout << "Outputting const array of dimensions " << rows << "x" << cols << endl;

	for(int r=0; r<rows; ++r){
		for(int c=0; c<cols; ++c){
			cout << array[r][c] << "\t";
		}
		cout << endl;
	}
}