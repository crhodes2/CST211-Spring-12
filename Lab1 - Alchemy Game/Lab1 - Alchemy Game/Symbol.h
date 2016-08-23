/************************************************************************
* Class: Symbol
*
* Purpose: This class represents a symbol in the game Alchemy
*
* Manager functions:	
* 	Symbol()
* 		Defaults to 0 for character and color  	
*	Symbol(char, int)
*		Sets the symbol to the given character and color (int)
*	Symbol(Symbol const& copy)
*		Copy constructor
*	operator=(Symbol const& rhs)
*		Assignment operator
*
* Methods:		
*	operator==(Symbol const& rhs)
*	operator!=(Symbol const& rhs)
*		basic comparison operators for equality/unequality
*	getCharacter()
*		Getter for character
*	getColor()
*		Getter for color
*************************************************************************/
#pragma once

class Symbol{
	private:
		char m_character;
		int m_color;
	public:
		Symbol();
		Symbol(char character, int color);
		Symbol(Symbol const& copy);

		Symbol& operator=(Symbol const& rhs);
		bool operator==(Symbol const& rhs) const;
		bool operator!=(Symbol const& rhs) const;
		char getCharacter() const;
		int getColor() const;
};