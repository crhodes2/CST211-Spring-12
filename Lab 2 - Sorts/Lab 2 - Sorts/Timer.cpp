#include "Timer.h"

/**********************************************************************	
* Purpose: Converts the current time to miliseconds and returns a double
*
* Entry: time, LARGE_INTEGER to convert into miliseconds
*
* Exit: Returns double of time in ms.
*
************************************************************************/
double Timer::_toMS(LARGE_INTEGER time){
	return 1000.0 * ((double) time.QuadPart / (double) m_freq.QuadPart); 
}

/**********************************************************************	
* Purpose: Timer default constructor, zeros out all timers and sets 
*		clock frequency
*
* Entry: None.
*
* Exit: zero'd out Timer with frequency set.
*
************************************************************************/
Timer::Timer(){
	m_start.QuadPart = 0;
	m_end.QuadPart = 0;
	QueryPerformanceFrequency(&m_freq);
}

/**********************************************************************	
* Purpose: Records the start of the timer
*
* Entry: None.
*
* Exit: Start timer is set.
*
************************************************************************/
void Timer::Start(){
	QueryPerformanceCounter(&m_start);
}

/**********************************************************************	
* Purpose: Records the end of the timer
*
* Entry: None.
*
* Exit: End timer is set.
*
************************************************************************/
void Timer::Stop(){
	QueryPerformanceCounter(&m_end);
}

/**********************************************************************	
* Purpose: Resets the current timer
*
* Entry: None.
*
* Exit: start and end times are zero'd.
*
************************************************************************/
void Timer::Reset(){
	m_start.QuadPart = 0;
	m_end.QuadPart = 0;
}

/**********************************************************************	
* Purpose: Returns the miliseconds between start and stop
*
* Entry: None.
*
* Exit: Returns double representing miliseconds of duration.
*
************************************************************************/
double Timer::getTime(){
	LARGE_INTEGER duration;
	duration.QuadPart = m_end.QuadPart - m_start.QuadPart;
	return _toMS(duration);
}