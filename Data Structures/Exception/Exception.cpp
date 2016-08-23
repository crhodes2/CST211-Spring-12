#include "Exception.h" // exception.cpp is in the same directory, so it picks up the .h fine as well

/**********************************************************************	
* ostream& operator<<(ostream& stream, Exception const& except)
* Purpose: This function allows exceptions to be used with cout.
*
* Entry: 
*	Params:
*		stream: The ostream object to output the exception message to.
*		except: The Exception to output.
*
* Exit: The exception's message is output to the stream, and the modified 
*		stream is returned for chaining.
************************************************************************/
std::ostream& operator<<(std::ostream& stream, Exception const& except){
	return stream << except.m_msg;
}

/**********************************************************************	
* Exception()
* Purpose: This function is the default constructor for the Exception class.
*
* Entry:
*		None.
*
* Exit: Constructs an Exception with a message of "Generic Exception".
************************************************************************/
Exception::Exception() : m_msg(0){
	setMessage("Generic Exception");
}

/**********************************************************************	
* Exception(char* msg)
* Purpose: This function is the 1-arg constructor for the Exception class.
*
* Entry:
*	Params:
*		msg: (char*) The exception message.
*
* Exit: Constructs an Exception with the given message.
************************************************************************/
Exception::Exception(char* msg) : m_msg(0){
	setMessage(msg);
}

/**********************************************************************	
* Exception(Exception const& copy)
* Purpose: This function is the copy constructor for the Exception class.
*
* Entry:
*	Params:
*		copy: (Exception) The Exception to copy from.
*
* Exit: Constructs an Exception that is a deep copy of the passed in Exception.
************************************************************************/
Exception::Exception(Exception const& copy) : m_msg(0){
	setMessage(copy.m_msg);
}

/**********************************************************************	
* ~Exception()
* Purpose: This function is the destructor for the Exception class. It 
*		frees the memory allocated for the message.
*
* Entry:
*		None.
*
* Exit: Resets the exception to default and frees up allocated memory.
************************************************************************/
Exception::~Exception(){
	if(m_msg){
		delete m_msg;
		m_msg = 0;
	}
}

/**********************************************************************	
* Exception& operator=(Exception const& rhs)
* Purpose: This function is the assignment operator for the Exception class.
*
* Entry:
*	Params:
*		rhs: (Exception) The right hand side of the assignment.
*
* Exit: The left hand Exception is assigned the values of the right hand 
*		Exception and the left hand Exception is returned by reference.
************************************************************************/
Exception& Exception::operator=(Exception const& rhs){
	// check for self assignment
	if(this != &rhs){
		int len = strlen(rhs.m_msg);
		// check if m_msg and rhs.m_msg are diff length, and if so, delete and resize
		if(len!=strlen(m_msg)){
			delete m_msg;
			m_msg = new char[len+1];
		}
		strcpy(m_msg, rhs.m_msg);
	}
	return *this;
}

/**********************************************************************	
* const char* getMessage()
* Purpose: This function returns the message for the exception.
*
* Entry:
*		None.
*
* Exit: Returns the exception message (const char*).
************************************************************************/
const char* Exception::getMessage(){
	return m_msg;
}

/**********************************************************************	
* setMessage(char* msg)
* Purpose: This function sets the exception message.
*
* Entry:
*	Params:
*		msg: (char*) The exception message.
*
* Exit: The exception's message is set to the passed in message.
************************************************************************/
void Exception::setMessage(char* msg){
	int len = strlen(msg);

	// if m_msg is uninitialized, or different length than new msg
	if(!m_msg || len!=strlen(m_msg)){
		delete m_msg;
		m_msg = new char[len+1];
	}
	strcpy(m_msg, msg);
}