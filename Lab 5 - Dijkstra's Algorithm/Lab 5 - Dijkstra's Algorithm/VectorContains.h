/**********************************************************************	
* Purpose: Returns bool if the requested data is in the vector.
*
* Entry: vec is a templated vector, data is of the same type as the template param.
*
* Exit: bool is returned representing if the data is found in the vector
*
************************************************************************/
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