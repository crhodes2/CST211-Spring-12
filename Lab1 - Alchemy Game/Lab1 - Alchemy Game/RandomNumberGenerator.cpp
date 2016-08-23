#include "RandomNumberGenerator.h"
#include <random>
#include <time.h>

bool RandomNumberGenerator::seeded = false;

/**********************************************************************	
* Purpose: Generates a random number (int) between lower and upper
*
* Entry: parameters: lower, upper (ints), representing the inclusive
*	bounds for the random number
*
* Exit: returns random number in given range
*
************************************************************************/
int RandomNumberGenerator::generate(int lower = 0, int upper = 100){
	if(!seeded){
		srand(time(NULL));
		seeded = true;
	}
	return rand()%(upper-lower+1); 
}