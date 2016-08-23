/************************************************************************
* Class: HashTable
*
* Purpose: This class represents a hash table. It can support any data types, 
*	so long as a hashing function for the key type is provided.
*
* Manager functions:	
* 	HashTable()
*	HashTable(const HashTable &)
*	!HashTable()
*	operator=(const HashTable &)
*		Traditional constructors/destructors/op=
*
* Methods:
*	operator[]
*		Bracket operator for retrieval/assignment
*	Rehash()
*		After reseting the hash function, this will rehash all the data into new buckets
*	setHash()
*		Set a new hashing function for the table.
*	Hash()
*		Will use the currently set hash to hash its argument
*	defaultHash()
*		A simple default hashing function provided for string/int types
*	setNumBuckets()
*		Sets number of buckets
*	getNumBuckets()
*		Retrieves number of buckets being used currently.
*	Purge()
*		Eliminates all elements of the table.
*	DumpHashTable()
*		Outputs a summary of the hash table to console
*	
*************************************************************************/
#pragma once

#include <list>
using std::list;

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <algorithm>
using std::sort;

using std::pair;

template <class KeyType, class DataType>
class HashTable
{
private:
	vector<list<pair<KeyType, DataType>>> m_buckets;
	unsigned m_numBuckets;

	unsigned (*m_hashFunc)(const KeyType &key);

	void Rehash(void);
public:
	HashTable(unsigned num_buckets = 25);
	HashTable(const HashTable<KeyType, DataType> &copy);
	~HashTable();

	const HashTable<KeyType, DataType> & operator=(const HashTable<KeyType, DataType> &rhs);

	DataType& operator[](const KeyType &key);
	const DataType & operator[](const KeyType &key) const;

	void setHash(unsigned (*hashFunc)(const KeyType &key));
	unsigned Hash(const KeyType &key) const;

	static unsigned defaultHash(const string &key);
	static unsigned defaultHash(const int &key);

	void setNumBuckets(unsigned num_buckets);
	unsigned getNumBuckets(void);

	void Purge(void);

	void DumpHashTable(void) const;
};

/**********************************************************************	
* Purpose: Will rehash every k-v pair in the hash table
*
* Entry: None.
*
* Exit: The hash table will be fully rehashed.
*
************************************************************************/
template <class KeyType, class DataType>
void HashTable<KeyType, DataType>::Rehash(void)
{
	HashTable<KeyType, DataType> newHashTable(m_numBuckets);
	newHashTable.m_hashFunc = m_hashFunc;

	for(unsigned i = 0; i < m_buckets.size(); ++i)
	{
		for(list<pair<KeyType, DataType>>::const_iterator j = m_buckets.at(i).begin(); j != m_buckets.at(i).end(); ++j)
		{
			newHashTable[(*j).first] = (*j).second;
		}
	}

	(*this) = newHashTable;
}

/**********************************************************************	
* Purpose: Basic constructors, default, copy, and destructor
*
* Entry: None.
*
* Exit: The object will be created/initialized or destructed.
*
************************************************************************/
template <class KeyType, class DataType>
HashTable<KeyType, DataType>::HashTable(unsigned num_buckets = 25)
	: m_numBuckets(num_buckets)
{
	m_buckets.reserve(num_buckets);
	m_buckets.assign(m_numBuckets, list<pair<KeyType, DataType>>());
}

template <class KeyType, class DataType>
HashTable<KeyType, DataType>::HashTable(const HashTable<KeyType, DataType> &copy)
	: m_numBuckets(copy.m_numBuckets), m_buckets(copy.m_buckets), m_hashFunc(copy.m_hashFunc)
{

}

template <class KeyType, class DataType>
HashTable<KeyType, DataType>::~HashTable()
{
	Purge();
	m_numBuckets = 0;
	m_hashFunc = nullptr;
}

/**********************************************************************	
* Purpose: Assignment operator
*
* Entry: None.
*
* Exit: The hash table takes on the exact structure and elements of rhs.
*
************************************************************************/
template <class KeyType, class DataType>
const HashTable<KeyType, DataType> & HashTable<KeyType, DataType>::operator=(const HashTable<KeyType, DataType> &rhs)
{
	if(this != &rhs)
	{
		Purge();
		m_numBuckets = rhs.m_numBuckets;
		m_buckets = rhs.m_buckets; // God do I love STL containers
		m_hashFunc = rhs.m_hashFunc;
	}
	return *this;
}

/**********************************************************************	
* Purpose: Bracket operators. Used to retreive addresses of data for assignment/retrieval
*
* Entry: None. (If key does not exist, it will be created! Be wary of 
*	outputting hashtable["KeyThatDoesn'tExist"] to cout or similar, as 
*	it will cause that key to be initialized to default DataType(). Note:
*	STL map works same way)
*
* Exit: Returns the data by reference or const ref, depending on which flavor was called.
*
************************************************************************/
template <class KeyType, class DataType>
DataType& HashTable<KeyType, DataType>::operator[](const KeyType &key)
{
	DataType* data_ptr = nullptr;
	
	unsigned index = m_hashFunc(key) % m_numBuckets;

	for(list<pair<KeyType, DataType>>::iterator i = m_buckets[index].begin(); i != m_buckets[index].end() && !data_ptr; ++i)
	{
		if((*i).first == key)
		{
			data_ptr = &((*i).second);	
		}
	}
	if(!data_ptr)
	{
		m_buckets.at(index).push_back(pair<KeyType, DataType>(key, DataType()));
		data_ptr = &m_buckets.at(index).back().second;
	}
	return *data_ptr;
}

template <class KeyType, class DataType>
const DataType & HashTable<KeyType, DataType>::operator[](const KeyType &key) const
{
	DataType* data_ptr = nullptr;
	
	unsigned index = m_hashFunc(key) % m_numBuckets;

	for(list<pair<KeyType, DataType>>::iterator i = m_buckets[index].begin(); i != m_buckets[index].end() && !data_ptr; ++i)
	{
		if((*i).first == key)
		{
			data_ptr = &((*i).second);	
		}
	}
	if(!data_ptr)
	{
		throw exception("Key not found!");
	}
	return *data_ptr;
}

/**********************************************************************	
* Purpose: Used to set a new hashing function
*
* Entry: None.
*
* Exit: Automatically rehashes the table immediately after setting new hash.
*
************************************************************************/
template <class KeyType, class DataType>
void HashTable<KeyType, DataType>::setHash(unsigned (*hashFunc)(const KeyType &key))
{
	m_hashFunc = hashFunc;
	Rehash();
}

/**********************************************************************	
* Purpose: Utility function to call the current hash func on a key.
*
* Entry: None.
*
* Exit: returns unsigned result from hash function on key.
*
************************************************************************/
template <class KeyType, class DataType>
unsigned HashTable<KeyType, DataType>::Hash(const KeyType &key) const
{
	return m_hashFunc(key);
}

/**********************************************************************	
* Purpose: Two default hash functions are available to the user. One for strings, one for int types.
*
* Entry: None.
*
* Exit: Performs some minimal hashing function and returns an unsigned result.
*
************************************************************************/
template <class KeyType, class DataType>
unsigned HashTable<KeyType, DataType>::defaultHash(const string &key)
{
	unsigned total = 0;
	for(string::const_iterator i = key.begin(); i != key.end(); ++i)
	{
		total += char(*i);
	}
	return total;
}

template <class KeyType, class DataType>
unsigned HashTable<KeyType, DataType>::defaultHash(const int &key)
{
	return ((unsigned) key);
}

/**********************************************************************	
* Purpose: setter/getter for the number of buckets used by the hash table.
*
* Entry: None.
*
* Exit: Returns number of buckets, or for the setter, it sets number of buckets and immediately rehashes.
*
************************************************************************/
template <class KeyType, class DataType>
void HashTable<KeyType, DataType>::setNumBuckets(unsigned num_buckets)
{
	m_numBuckets = num_buckets;
	Rehash();
}

template <class KeyType, class DataType>
unsigned HashTable<KeyType, DataType>::getNumBuckets(void)
{
	return m_numBuckets;
}

/**********************************************************************	
* Purpose: Purges all data from the table.
*
* Entry: None.
*
* Exit: Table is reset to factory settings.
*
************************************************************************/
template <class KeyType, class DataType>
void HashTable<KeyType, DataType>::Purge(void)
{
	m_buckets.clear();
	m_buckets.reserve(m_numBuckets);
	m_buckets.assign(m_numBuckets, list<pair<KeyType, DataType>>());
}

/**********************************************************************	
* Purpose: Dumps the data in the hash table to console.
*
* Entry: None.
*
* Exit: K-V pairs are output to console (and their bucket number), sorted on the key.
*
************************************************************************/
template <class KeyType, class DataType>
void HashTable<KeyType, DataType>::DumpHashTable(void) const
{
	vector<pair<KeyType, DataType>> dump;
	for(unsigned i = 0; i < m_buckets.size(); ++i)
	{
		for(list<pair<KeyType, DataType>>::const_iterator j = m_buckets.at(i).begin(); j != m_buckets.at(i).end(); ++j)
		{
			dump.push_back(*j);
		}
	}

	sort(dump.begin(), dump.end());

	cout << "Beginning Hash Table Dump..." << endl;
	for(vector<pair<KeyType, DataType>>::const_iterator i = dump.begin(); i != dump.end(); ++i)
	{
		cout << "[" << (*i).first << "]: " << (*i).second << " (bucket: " << (Hash((*i).first) % m_numBuckets) << ")" << endl;
	}
}