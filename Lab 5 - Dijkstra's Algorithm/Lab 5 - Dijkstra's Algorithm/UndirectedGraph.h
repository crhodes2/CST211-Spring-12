/************************************************************************
* Class: UndirectedGraph
*
* Purpose: This class represents a undirected graph structure. Note that 
*		this implementation is built around only a single edge between 
*		any two specific nodes.
*
* Important note: See documentation for Graph.h, as this is essentially a 
*	minimal wrapper for it, that transforms it into a graph instead of digraph.
*
* Manager functions:	
* 	UndirectedGraph()
*	UndirectedGraph(UndirectedGraph const&)
*		Constructors
*	operator=
*		Assignment operator
*
* Methods:
*	InsertNode(DataType const&)
*		Inserts data into the tree
*	InsertEdge(DataType const&, DataType const&, DescType const&, WeightType const&)
*		Inserts an edge into the graph with source, destination, weight
*	ForceInsertEdge(DataType const&, DataType const&, DescType const&, WeightType const&)
*		Inserts an edge like above, but if source/dest node is not found, added automatically
*	DeleteNode(DataType const&)
*		Deletes node that matches data
*	DeleteEdge(DataType const&, DataType const&)
*		Deletes edge that matches data
*	GetWeight(DataType const&, DataType const&)
*		Gets the weight of a specified edge
*	GetDescription(DataType const&, DataType const&)
*		Gets the description of a specified edge
*	Purge()
*		Clear the graph
*	DepthFirstTraversal()
*	BreadthFirstTraversal()
*		Various traversal methods for the tree (starting at first node inserted, 
		can be called with other starting nodes though)
*	
*************************************************************************/
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