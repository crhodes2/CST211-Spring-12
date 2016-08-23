#include <iostream>
using std::cout;
using std::endl;

#include "Array/Array.h"

//#include "Exception/Exception.cpp"

int main(void)
{
	cout << "Testing Environment." << endl;
	
	Array<int> threelong(3,0);
	for(int i=0; i<3; ++i){
		threelong[i] = 10*i;
		cout << threelong[i] << endl;
	}

	Array<int> empty;

	//cout << Exception("Tits and ass") << endl;


	system("pause");
	return 0;
}