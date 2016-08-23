#pragma once

#include "Graph.h"

template <class DataType, class DescType, class WeightType>
class UndirectedGraph : public Graph<DataType, DescType, WeightType>
{
private:

public:
	UndirectedGraph();
	UndirectedGraph(UndirectedGraph<DataType, DescType, WeightType> const& copy);
	~UndirectedGraph();

	using Graph<DataType, DescType, WeightType>::operator=;
	
	void InsertEdge(DataType const& from, DataType const& to, DescType const& description, WeightType const& weight);
	void ForceInsertEdge(DataType const& from, DataType const& to, DescType const& description, WeightType const& weight);

	void DeleteEdge(DataType const& from, DataType const& to);
};

template <class DataType, class DescType, class WeightType>
UndirectedGraph<DataType, DescType, WeightType>::UndirectedGraph()
	: Graph()
{

}

template <class DataType, class DescType, class WeightType>
UndirectedGraph<DataType, DescType, WeightType>::UndirectedGraph(UndirectedGraph<DataType, DescType, WeightType> const& copy)
	: Graph(copy)
{

}

template <class DataType, class DescType, class WeightType>
UndirectedGraph<DataType, DescType, WeightType>::~UndirectedGraph()
{
	// a UndirectedGraph has no data that needs to be cleaned up besides that already cleaned up in Graph destructor
}

template <class DataType, class DescType, class WeightType>
void UndirectedGraph<DataType, DescType, WeightType>::InsertEdge(DataType const& from, DataType const& to, DescType const& description, WeightType const& weight)
{
	Graph<DataType, DescType, WeightType>::InsertEdge(from, to, description, weight);
	Graph<DataType, DescType, WeightType>::InsertEdge(to, from, description, weight);
}

template <class DataType, class DescType, class WeightType>
void UndirectedGraph<DataType, DescType, WeightType>::ForceInsertEdge(DataType const& from, DataType const& to, DescType const& description, WeightType const& weight)
{
	Graph<DataType, DescType, WeightType>::ForceInsertEdge(from, to, description, weight);
	Graph<DataType, DescType, WeightType>::ForceInsertEdge(to, from, description, weight);
}

template <class DataType, class DescType, class WeightType>
void UndirectedGraph<DataType, DescType, WeightType>::DeleteEdge(DataType const& from, DataType const& to)
{
	Graph<DataType, DescType, WeightType>::DeleteEdge(from, to);
	Graph<DataType, DescType, WeightType>::DeleteEdge(to, from);
}