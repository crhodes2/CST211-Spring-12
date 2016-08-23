/***********************************************************
* Author:		Andrew Sparkes
* Title:		CST 211 Assignment 1
* Filename:		main.cpp
* Date Created:	4-2-12
* Modified:		4-3-12 : rewrote large chunks of both classes
*				4-4-12 : wrote/rewrote most of documentation
*						 Added more to driver program
*
* Overview:
*	This program is a driver demonstrating the basic 
*	capabilities of the Exception class and the 1D Array class.
*
* Input:
*	None.
*
* Output:
*	Will output a basic test of both classes, demonstrating 
*	each class' methods.
************************************************************/
#include <crtdbg.h> 
#include <iostream>
using std::cout;
using std::endl;
#include "Array.h"
#include "Exception.h"

#define _CRTDBG_MAP_ALLOC

int main(){
   _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
   
   cout << "Testing exception class basics..." << endl;
   Exception e1;
   Exception e2("Test Error Message");
   Exception e3;
   e3 = e1;
   Exception e4 = e2;
   Exception e5(e1);
   e5.setMessage("Something else");

   cout << e1 << endl; // default message
   cout << e2 << endl; // test message
   cout << e3 << endl; // default message
   cout << e4 << endl; // test message
   cout << e5 << endl; // something else
   cout << e3.getMessage() << endl; // default message
   

   system("pause");
   system("cls");

   cout << "Testing Array class basics" << endl;

   Array<int> a1;
   cout << "Length of 0arg <int> Array: " << a1.getLength() << endl;
   cout << "Starting index of 0arg <int> Array: " << a1.getStartIndex() << endl;

   
   Array<char*> a2(3,1);
   cout << "Length of 2arg <char*> Array (length 3, index 1): " << a2.getLength() << endl;
   cout << "Starting index of 2arg <char*> Array (length 3, index 1): " << a2.getStartIndex() << endl;

   Array<char*> a3(4,10);
   a3[10] = "first element";
   a3[11] = "second element";
   a3[12] = "third element";
   a3[13] = "fourth and final element";
   cout << "Length of 2arg <char*> Array (length 4, index 10): " << a3.getLength() << endl;
   cout << "Starting index of 2arg <char*> Array (length 4, index 10): " << a3.getStartIndex() << endl;
   cout << "Now, testing start_index and length for above array..." << endl;
   for(int i=a3.getStartIndex(); i<a3.getStartIndex() + a3.getLength(); ++i){
	   cout << "a3[" << i << "] = " << a3[i] << endl;
   }

   cout << "Now, testing above array after changing its starting index to 5" << endl;
   a3.setStartIndex(5);
   for(int i=a3.getStartIndex(); i<a3.getStartIndex() + a3.getLength(); ++i){
	   cout << "a3[" << i << "] = " << a3[i] << endl;
   }

   cout << "Now, resizing above array to length 2" << endl;
   a3.setLength(2);
   for(int i=a3.getStartIndex(); i<a3.getStartIndex() + a3.getLength(); ++i){
	   cout << "a3[" << i << "] = " << a3[i] << endl;
   }

   cout << "Now, resizing above array to length 3" << endl;
   a3.setLength(3);
   a3[7] = "added element (final)";
   for(int i=a3.getStartIndex(); i<a3.getStartIndex() + a3.getLength(); ++i){
	   cout << "a3[" << i << "] = " << a3[i] << endl;
   }

   cout << "Now, resizing above array to length -6" << endl;
   try{
	   a3.setLength(-6);
   }catch (Exception e){
	   cout << "Exception! " << e.getMessage() << endl;
   }
   for(int i=a3.getStartIndex(); i<a3.getStartIndex() + a3.getLength(); ++i){
	   cout << "a3[" << i << "] = " << a3[i] << endl;
   }

   cout << "And now, making another array and assigning it the above array:" << endl;
   Array<char*> a4;
   a4 = a3;
   for(int i=a3.getStartIndex(); i<a3.getStartIndex() + a3.getLength(); ++i){
	   cout << "a4[" << i << "] = " << a3[i] << endl;
   }

   cout << "Now, trying to access a4[55]..." << endl;
   try{
	   cout << "a4[55] = " << a4[55] << endl; 
   }catch (Exception e){
	   cout << "Exception! " << e.getMessage() << endl;
   }

   cout << "Now, trying to access a4[1]..." << endl;
   try{
	   cout << "a4[1] = " << a4[1] << endl; 
   }catch (Exception e){
	   cout << "Exception! " << e.getMessage() << endl;
   }


   system("pause");
   return 0;
}