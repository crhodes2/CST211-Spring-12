
#include <iostream>
using std::endl;
using std::cout;

#include "dllTest/TestFunc.h"
//#include "NormalHeaderTest\TestHeader.h"
//#include "NormalHeaderTest\AnotherTestHeader.h"

int main(){
	/*Array<int> t(3,0);
	t[0] = 1;
	t[1] = 4;
	t[2] = 9;
	for(int i=0; i<3; i++){
		cout << t[i] << endl;
	}*/
	testclass::test();
	testfunction();
	//TestHeader::test();
	//AnotherTestHeader::test();

	system("pause");
	return 0;
}