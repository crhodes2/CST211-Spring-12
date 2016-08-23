/************************************************************************
* Class: Array
*
* Purpose: This class represents a simple timer. Start it before a function 
*		call, stop it after, and then use getTime() to retrieve the difference 
*		in time (in ms) between the start and stop times.
*
* Manager functions:	
* 	Timer()
*		Basic constructor for Timer, zeros out start, stop, sets frequency
*
* Methods:		
*	Start()
*		Starts the timer.
*	Stop()
*		Stops the timer.
*	Reset()
*		Resets the timer.
*	getTime()
*		Retrieves the difference between start, stop times.
*	_toMS()
*		Helper function to convert to miliseconds
*************************************************************************/
#pragma once
#include <Windows.h>

class Timer{
private:
	LARGE_INTEGER m_start;
	LARGE_INTEGER m_end;
	LARGE_INTEGER m_freq;
	double _toMS(LARGE_INTEGER time);
public:
	Timer();
	void Start();
	void Stop();
	void Reset();
	double getTime();
};