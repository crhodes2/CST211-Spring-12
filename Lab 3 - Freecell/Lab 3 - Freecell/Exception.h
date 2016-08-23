/************************************************************************
* Class: Exception
*
* Purpose: This class represents a simple exception consisting of a 
*		single string.
*
* Manager functions:	
* 	Exception()
*		Sets exception message to "Generic Exception".
*	Exception(char* msg)
*		Sets exception message to msg.
*	Exception(Exception const& copy)
*		Copy constructor
*	~Exception()
*		Destructor. Cleans up message.
*
* Methods:		
*	operator=(Exception const& rhs)
*		Overloaded operator= for assignment.
*	getMessage()
*		Returns the current exception message.
*	setMessage(char* msg)
*		Sets the current exception message to msg.
*************************************************************************/
#pragma once
#include <iostream>

class Exception{
		friend std::ostream& operator<<(std::ostream& stream, Exception const& except);

	private:
		char* m_msg;

	public:
		Exception();
		Exception(char* msg);
		Exception(Exception const& copy);
		~Exception();

		Exception& operator=(Exception const& rhs);
		const char* getMessage();
		void setMessage(char* msg);

};