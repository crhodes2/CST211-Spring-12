#pragma once

#include <numeric>
using std::accumulate;

#include <iostream>
using std::cout;
using std::endl;


// this is a glorified struct, with a couple helper functions bolted on
template <class DataType, class DescType, class WeightType>
class GraphPath
{
public:
	vector<DataType> m_nodePath;
	vector<DescType> m_edgePath;
	vector<WeightType> m_weightPath;

	GraphPath(DataType const& start_node);
	GraphPath(GraphPath const& copy);
	~GraphPath();

	GraphPath const& operator=(GraphPath const& rhs);

	void AddEdge(DataType const& dest, DescType const& desc, WeightType const& weight);

	void Display(void);
};

template <class DataType, class DescType, class WeightType>
GraphPath<DataType, DescType, WeightType>::GraphPath(DataType const& start_node)
{
	m_nodePath.push_back(start_node);
}

template <class DataType, class DescType, class WeightType>
GraphPath<DataType, DescType, WeightType>::GraphPath(GraphPath const& copy)
{
	*this = copy;
}

template <class DataType, class DescType, class WeightType>
GraphPath<DataType, DescType, WeightType>::~GraphPath()
{
	m_nodePath.clear();
	m_edgePath.clear();
	m_weightPath.clear();
}

template <class DataType, class DescType, class WeightType>
GraphPath<DataType, DescType, WeightType> const& GraphPath<DataType, DescType, WeightType>::operator=(GraphPath const& rhs)
{
	m_nodePath = rhs.m_nodePath;
	m_edgePath = rhs.m_edgePath;
	m_weightPath = rhs.m_weightPath;

	return *this;
}

template <class DataType, class DescType, class WeightType>
void GraphPath<DataType, DescType, WeightType>::AddEdge(DataType const& dest, DescType const& desc, WeightType const& weight)
{
	m_nodePath.push_back(dest);
	m_edgePath.push_back(desc);
	m_weightPath.push_back(weight);
}

template <class DataType, class DescType, class WeightType>
void GraphPath<DataType, DescType, WeightType>::Display(void)
{
	cout << "Outputting path from " << *(m_nodePath.begin()) << " to " << *(m_nodePath.rbegin()) << "..." << endl;
	cout << "Starting at '" << *m_nodePath.begin() << "'..." << endl;
	for(size_t i = 0; i < m_nodePath.size()-1; ++i)
	{
		cout << "Take '" << m_edgePath[i] << "' to '" << m_nodePath[i+1] << "'." << endl; 
	}
	cout << "Total Length: " << accumulate(m_weightPath.begin(), m_weightPath.end(), WeightType()) << endl;
}