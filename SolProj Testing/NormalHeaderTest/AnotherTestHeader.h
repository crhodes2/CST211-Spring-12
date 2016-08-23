#pragma once
#include <iostream>
#include "TestHeader.h"

class AnotherTestHeader{
public:
	static void test(){
		TestHeader::test();
		std::cout << "AnotherTestHeader" << std::endl;
	}
};