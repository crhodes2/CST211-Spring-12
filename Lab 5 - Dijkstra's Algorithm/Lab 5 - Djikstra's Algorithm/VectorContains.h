#pragma once
#include <vector>
using std::vector;

namespace HelperFunctions
{
	template <class T>
	bool VectorContains(vector<T> vec, T const& data);

	template <class T>
	bool VectorContains(vector<T> vec, T const& data)
	{
		vector<T>::iterator i = find(vec.begin(), vec.end(), data);
		return (i != vec.end());
	}
};