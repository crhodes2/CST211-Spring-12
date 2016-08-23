#pragma once

template <class DataType, class DescType, class WeightType>
class GraphNode;

template <class DataType, class DescType, class WeightType>
class GraphEdge
{
private:
	WeightType m_weight;
	DescType m_description;
	GraphNode<DataType, DescType, WeightType>* m_destination;

public:
	template <class DataType, class DescType, class WeightType> friend class Graph;
	template <class DataType, class DescType, class WeightType> friend class UndirectedGraph;

	GraphEdge();
	GraphEdge(WeightType const& weight, DescType const& description, GraphNode<DataType, DescType, WeightType>* destination);
	GraphEdge(GraphEdge<DataType, DescType, WeightType> const& copy);
	~GraphEdge();

	GraphEdge<DataType, DescType, WeightType> const& operator=(GraphEdge<DataType, DescType, WeightType> const& rhs);
};

template <class DataType, class DescType, class WeightType>
GraphEdge<DataType, DescType, WeightType>::GraphEdge()
	: m_weight(0), m_description(DescType()), m_destination(nullptr)
{

}

template <class DataType, class DescType, class WeightType>
GraphEdge<DataType, DescType, WeightType>::GraphEdge(WeightType const& weight, DescType const& description, GraphNode<DataType, DescType, WeightType>* destination)
	: m_weight(weight), m_description(description), m_destination(destination)
{

}

template <class DataType, class DescType, class WeightType>
GraphEdge<DataType, DescType, WeightType>::GraphEdge(GraphEdge<DataType, DescType, WeightType> const& copy)
{
	*this = copy;
}

template <class DataType, class DescType, class WeightType>
GraphEdge<DataType, DescType, WeightType>::~GraphEdge()
{
	m_weight = WeightType();
	m_description = DescType();
	m_destination = nullptr;
}

template <class DataType, class DescType, class WeightType>
GraphEdge<DataType, DescType, WeightType> const& GraphEdge<DataType, DescType, WeightType>::operator=(GraphEdge<DataType, DescType, WeightType> const& rhs)
{
	if(this != &rhs)
	{
		m_weight = rhs.m_weight;
		m_description = rhs.m_description;
		m_destination = rhs.m_destination;
	}
	return *this;
}