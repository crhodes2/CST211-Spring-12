#include "Symbol.h"

/**********************************************************************	
* Purpose: default constructor
*
* Entry: none.
*
* Exit: Sets up a symbol with default character/color of 0
*
************************************************************************/
Symbol::Symbol() : m_character(0), m_color(0){}

/**********************************************************************	
* Purpose: Used to construct a symbol with given character/color
*
* Entry: parameters: (char) character, (int) color, character is a ANSI 
*	decimal character, color is a console colortable index (0-255)
*
* Exit: constructs a symbol with given parameters
*
************************************************************************/
Symbol::Symbol(char character, int color) : m_character(character), m_color(color){}

/**********************************************************************	
* Purpose: Copy constructor
*
* Entry: copy (const& Symbol), the symbol to copy from
*
* Exit:  generates a symbol with same settings as copy
*
************************************************************************/
Symbol::Symbol(Symbol const& copy) : m_character(copy.m_character), m_color(copy.m_color){}

/**********************************************************************	
* Purpose: == and != comparison operators for symbols
*
* Entry: parameters: rhs (const& Symbol) the right hand of the operator
*
* Exit: returns bool representing if the symbols are equal/not equal
*
************************************************************************/
bool Symbol::operator==(Symbol const& rhs) const{
	bool equal = false;
	if(m_character == rhs.m_character && m_color == rhs.m_color){
		equal = true;
	}
	return equal;
}
bool Symbol::operator!=(Symbol const& rhs) const{
	bool not_equal = false;
	if(m_character != rhs.m_character || m_color != rhs.m_color){
		not_equal = true;
	}
	return not_equal;
}

/**********************************************************************	
* Purpose: Assignment operator
*
* Entry: rhs (const& Symbol) the right hand side of the assignment
*
* Exit: current symbol takes on the values of the right hand symbol.
*
************************************************************************/
Symbol& Symbol::operator=(Symbol const& rhs){
	m_character = rhs.m_character;
	m_color = rhs.m_color;

	return *this;
}

/**********************************************************************	
* Purpose: getter for character
*
* Entry: None.
*
* Exit: returns (char) character
*
************************************************************************/
char Symbol::getCharacter() const{
	return m_character;
}

/**********************************************************************	
* Purpose: getter for color
*
* Entry: None.
*
* Exit: returns color (int)
*
************************************************************************/
int Symbol::getColor() const{
	return m_color;
}