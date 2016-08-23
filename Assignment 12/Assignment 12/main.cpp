#include <iostream>
using std::cout;
using std::endl;

#include <crtdbg.h> 
#define _CRTDBG_MAP_ALLOC

#include "HashTable.h"
#include <string>
using std::string;

unsigned StringHash(const string &str);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	unsigned length = 12; // hardcoded data length, purely for demo purposes

	string stringKeys[] = {"First", "Second", "Third",
							"Fourth", "Fifth", "Sixth",
							"Seventh", "Eighth", "Ninth",
							"Tenth", "Eleventh", "Dozenth"};

	int numberKeys[] = {1,6,8,
						3,36,73,
						4463,634,273,
						22,5265,12};

	string stringData[] = {"Mouse", "Keyboard", "Monitor",
							"Tentacle", "Iguana", "Tornado",
							"Marsupial", "Blargon", "Ninja",
							"Llama", "Cayenne Pepper", "Bulldozer"};

	cout << "First, making a hashtable with integer keys and string data, with 10 buckets..." << endl;
	cout << "We also set the hash function to one of the default provided ones, but any will do." << endl;
	HashTable<int, string> intHashTable(10);
	intHashTable.setHash(HashTable<int, string>::defaultHash);
	

	cout << "Now inserting..." << endl;
	for(unsigned i = 0; i < length; ++i)
	{
		cout << "Inserting Key: " << numberKeys[i] << ", Data: " << stringData[i] << " (into bucket " << (HashTable<int, string>::defaultHash(numberKeys[i]) % intHashTable.getNumBuckets()) << ")" << endl;
		intHashTable[numberKeys[i]] = stringData[i];
	}

	intHashTable.DumpHashTable();

	cout << "-----------------------------------------------------------" << endl;

	cout << "Now, making a hashtable with string keys and string data, with 10 buckets..." << endl;
	cout << "We also set the hash function to one of the default provided ones, but any will do." << endl;
	HashTable<string, string> stringHashTable(10);
	stringHashTable.setHash(HashTable<string, string>::defaultHash);
	
	
	cout << "Now inserting..." << endl;
	for(unsigned i = 0; i < length; ++i)
	{
		cout << "Inserting Key: " << stringKeys[i] << ", Data: " << stringData[i] << " (into bucket " << (stringHashTable.Hash(stringKeys[i]) % stringHashTable.getNumBuckets()) << ")" << endl;
		stringHashTable[stringKeys[i]] = stringData[i];
	}

	stringHashTable.DumpHashTable();

	cout << "Now, setting a different hash function." << endl;
	stringHashTable.setHash(StringHash);
	stringHashTable.DumpHashTable();

	cout << "And to show the different buckets working again, we purge and add more elements" << endl;
	stringHashTable.Purge();

	cout << "Now inserting again, after changing the hash..." << endl;
	for(unsigned i = 0; i < length; ++i)
	{
		cout << "Inserting Key: " << stringKeys[i] << ", Data: " << stringData[i] << " (into bucket " << (stringHashTable.Hash(stringKeys[i]) % stringHashTable.getNumBuckets()) << ")" << endl;
		stringHashTable[stringKeys[i]] = stringData[i];
	}

	cout << "Testing copy constructor: " << endl;
	HashTable<string, string> stringHashTableCopy(stringHashTable);
	stringHashTableCopy.DumpHashTable();

	cout << "Testing op=" << endl;
	HashTable<string, string> stringHashTableEquals;
	stringHashTableEquals = stringHashTable;
	stringHashTableEquals.DumpHashTable();

	system("pause");
	return 0;
}

unsigned StringHash(const string &str)
{
	return (unsigned) str.size();
}