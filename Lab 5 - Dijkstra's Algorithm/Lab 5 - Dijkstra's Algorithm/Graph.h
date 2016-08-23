/************************************************************************
* Class: Graph
*
* Purpose: This class represents a directed graph structure. Note that 
*		this implementation is built around only a single edge between 
*		any two specific nodes.
*
* Manager functions:	
* 	Graph()
*	Graph(Graph const&)
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

#include "GraphNode.h"
#include "GraphEdge.h"

#include <list>
using std::list;

#include <stack>
using std::stack;

#include <queue>
using std::queue;

#include <vector>
using std::vector;

#include "VectorContains.h"
using HelperFunctions::VectorContains;



template <class DataType, class DescType, class WeightType>
class Graph
{
protected:
	list< GraphNode<DataType, DescType, WeightType> > m_nodes;

public:
	
	Graph();
	Graph(Graph<DataType, DescType, WeightType> const& copy);
	~Graph();

	Graph<DataType, DescType, WeightType> const& operator=(Graph<DataType, DescType, WeightType> const& rhs);
	
	GraphNode<DataType, DescType, WeightType>* FindNode(DataType const& data) const;
	GraphEdge<DataType, DescType, WeightType>* FindEdge(DataType const& from, DataType const& to) const;

	bool NodeExists(DataType const& data);

	void InsertNode(DataType const& data);
	virtual void InsertEdge(DataType const& from, DataType const& to, DescType const& description, WeightType const& weight);
	virtual void ForceInsertEdge(DataType const& from, DataType const& to, DescType const& description, WeightType const& weight);

	void DeleteNode(DataType const& data);
	virtual void DeleteEdge(DataType const& from, DataType const& to);
	
	void Purge();

	vector<DataType> GetListOfNodes(void) const;

	WeightType GetWeight(DataType const& from, DataType const& to) const;
	DescType GetDescription(DataType const& from, DataType const& to) const;

	void DepthFirstTraversal(void (*traverseFunc)(DataType & data));
	void DepthFirstTraversal(DataType const& start_node, void (*traverseFunc)(DataType & data));

	void BreadthFirstTraversal(void (*traverseFunc)(DataType & data));
	void BreadthFirstTraversal(DataType const& start_node, void (*traverseFunc)(DataType & data));


};

/**********************************************************************	
* Purpose: Basic constructors for Graph. Default, copy constructors.
*
* Entry: None.
*
* Exit: Object is created
*
************************************************************************/
template <class DataType, class DescType, class WeightType>
Graph<DataType, DescType, WeightType>::Graph()
{
	
}

template <class DataType, class DescType, class WeightType>
Graph<DataType, DescType, WeightType>::Graph(Graph<DataType, DescType, WeightType> const& copy)
{
	*this = copy;
}

/**********************************************************************	
* Purpose: Destructor
*
* Entry: None.
*
* Exit: Destroys object and resets to original state
*
************************************************************************/
template <class DataType, class DescType, class WeightType>
Graph<DataType, DescType, WeightType>::~Graph()
{
	Purge();
}

/**********************************************************************	
* Purpose: Assignment operator
*
* Entry: None.
*
* Exit: Current object is assigned the same values as the rhs'
*
************************************************************************/
template <class DataType, class DescType, class WeightType>
Graph<DataType, DescType, WeightType> const& Graph<DataType, DescType, WeightType>::operator=(Graph<DataType, DescType, WeightType> const& rhs)
{
	// do a traversal and insert nodes/edges into this graph
	stack< GraphNode<DataType, DescType, WeightType>* > s;
	s.push(const_cast< GraphNode<DataType, DescType, WeightType>* >(&rhs.m_nodes.front()));

	vector< GraphNode<DataType, DescType, WeightType>* > already_visited_nodes;

	GraphNode<DataType, DescType, WeightType>* ptr = nullptr;

	while(!s.empty())
	{
		ptr = s.top();
		s.pop();

		if(!VectorContains(already_visited_nodes, ptr))
		{
			// pushing the children to the stack
			list<GraphEdge<DataType, DescType, WeightType>>::iterator edge_iterator = ptr->m_edges.begin();

			while(edge_iterator != ptr->m_edges.end())
			{
				ForceInsertEdge(ptr->m_data, (*edge_iterator).m_destination->m_data, (*edge_iterator).m_description, (*edge_iterator).m_weight);
				++edge_iterator;
			}
			already_visited_nodes.push_back(ptr);
		}

	}
	return *this;
}

/**********************************************************************	
* Purpose: Used to find a pointer to a given edge matching data
*
* Entry: None.
*
* Exit: A pointer to the edge is returned, or nullptr if not found
*
************************************************************************/
template <class DataType, class DescType, class WeightType>
GraphEdge<DataType, DescType, WeightType>* Graph<DataType, DescType, WeightType>::FindEdge(DataType const& from, DataType const& to) const
{
	GraphEdge<DataType, DescType, WeightType>* found_edge = nullptr;

	GraphNode<DataType, DescType, WeightType>* from_node = FindNode(from);

	if(from_node)
	{
		for(list<GraphEdge<DataType, DescType, WeightType>>::const_iterator i = from_node->m_edges.begin(); i != from_node->m_edges.end(); ++i)
		{
			if((*i).m_destination->m_data == to)
			{
				found_edge = const_cast< GraphEdge<DataType, DescType, WeightType>* >( &(*i) );
			}
		}
	}
	return found_edge;
}

/**********************************************************************	
* Purpose: Used to find a pointer to a given node matching data
*
* Entry: None.
*
* Exit: A pointer to the node is returned, or nullptr if not found
*
************************************************************************/
template <class DataType, class DescType, class WeightType>
GraphNode<DataType, DescType, WeightType>* Graph<DataType, DescType, WeightType>::FindNode(DataType const& data) const
{
	GraphNode<DataType, DescType, WeightType>* found_node = nullptr;

	for(list<GraphNode<DataType, DescType, WeightType>>::const_iterator i = m_nodes.begin(); i != m_nodes.end(); ++i)
	{
		if((*i).m_data == data)
		{
			found_node = const_cast< GraphNode<DataType, DescType, WeightType>* >( &(*i) );
		}
	}

	return found_node;
}

/**********************************************************************	
* Purpose: Used to check if a node exists in the graph
*
* Entry: None.
*
* Exit: returns bool representing if node matching data is present
*
************************************************************************/
template <class DataType, class DescType, class WeightType>
bool Graph<DataType, DescType, WeightType>::NodeExists(DataType const& data)
{
	return (FindNode(data) != nullptr);
}

/**********************************************************************	
* Purpose: Inserts a node into the graph
*
* Entry: None.
*
* Exit: Node with data is added to the graph
*
************************************************************************/
template <class DataType, class DescType, class WeightType>
void Graph<DataType, DescType, WeightType>::InsertNode(DataType const& data)
{
	if(!NodeExists(data))
	{
		GraphNode<DataType, DescType, WeightType> newNode(data);
		m_nodes.push_back(newNode);
	}
	else
	{
		// node already exists
		// error, message, ignore, etc here
	}
}

/**********************************************************************	
* Purpose: Inserts an edge into the graph
*
* Entry: None.
*
* Exit: graph has an edge inserted. 
*
************************************************************************/
template <class DataType, class DescType, class WeightType>
void Graph<DataType, DescType, WeightType>::InsertEdge(DataType const& from, DataType const& to, DescType const& description, WeightType const& weight)
{
	GraphNode<DataType, DescType, WeightType>* from_pointer = FindNode(from);
	GraphNode<DataType, DescType, WeightType>* to_pointer = FindNode(to);

	if(!from_pointer)
	{
		// the source node does not exist in the graph
		throw std::exception("Source Node does not exist in graph!");
	}
	if(!to_pointer)
	{
		// the destination node does not exist in the graph
		throw std::exception("Destination Node does not exist in graph!");
	}

	GraphEdge<DataType, DescType, WeightType> newEdge(weight, description, to_pointer);

	from_pointer->m_edges.push_back(newEdge);
}

/**********************************************************************	
* Purpose: Inserts an edge into the graph
*
* Entry: None.
*
* Exit: graph has an edge inserted. Note that if either from/to don't exist,
*	they will automatically be created
*
************************************************************************/
template <class DataType, class DescType, class WeightType>
void Graph<DataType, DescType, WeightType>::ForceInsertEdge(DataType const& from, DataType const& to, DescType const& description, WeightType const& weight)
{
	GraphNode<DataType, DescType, WeightType>* from_pointer = FindNode(from);
	GraphNode<DataType, DescType, WeightType>* to_pointer = FindNode(to);

	if(!from_pointer)
	{
		// the source node does not exist in the graph
		// current implementation simply adds the node
		InsertNode(from);
		from_pointer = FindNode(from); // and set the pointer for later
	}
	if(!to_pointer)
	{
		// the destination node does not exist in the graph
		// current implementation simply adds the node
		InsertNode(to);
		to_pointer = FindNode(to); // and set the pointer for later
	}

	GraphEdge<DataType, DescType, WeightType> newEdge(weight, description, to_pointer);

	from_pointer->m_edges.push_back(newEdge);
}

/**********************************************************************	
* Purpose: Deletes a node and any edges to it from the graph
*
* Entry: None.
*
* Exit: Node and edges to node are removed
*
************************************************************************/
template <class DataType, class DescType, class WeightType>
void Graph<DataType, DescType, WeightType>::DeleteNode(DataType const& data)
{
	typedef list< GraphNode<DataType, DescType, WeightType> >::iterator NodeIterator;
	typedef list< GraphEdge<DataType, DescType, WeightType> >::iterator EdgeIterator;

	NodeIterator node_to_delete;
	vector< EdgeIterator > edges_to_delete;

	if(NodeExists(data))
	{
		for(NodeIterator node_iterator = m_nodes.begin(); node_iterator != m_nodes.end(); ++node_iterator)
		{
			edges_to_delete.clear();

			for(EdgeIterator edge_iterator = (*node_iterator).m_edges.begin(); edge_iterator != (*node_iterator).m_edges.end(); ++edge_iterator)
			{
				if( (*edge_iterator).m_destination->m_data == data)
				{
					// one of the edges is to the node being deleted, add it to the list of things to kill
					edges_to_delete.push_back(edge_iterator);
				}
			}

			// we have a list of edges to clean up for this current node, do so now:
			for(vector<EdgeIterator>::iterator e = edges_to_delete.begin(); e != edges_to_delete.end(); ++e)
			{
				(*node_iterator).m_edges.erase(*e);
			}

			// then check if we have iterated to this node, and if so, add it to the kill list
			if((*node_iterator).m_data == data)
			{
				node_to_delete = node_iterator;
			}
		}

		// now kill the node itself
		m_nodes.erase(node_to_delete);
	}
	else
	{
		// node doesn't exist to begin with
		// throw error, message, etc here
	}
}

/**********************************************************************	
* Purpose: Deletes an edge from teh graph
*
* Entry: None.
*
* Exit: The edge is deleted
*
************************************************************************/
template <class DataType, class DescType, class WeightType>
void Graph<DataType, DescType, WeightType>::DeleteEdge(DataType const& from, DataType const& to)
{
	typedef list<GraphNode<DataType, DescType, WeightType>>::iterator NodeIterator;
	typedef list<GraphEdge<DataType, DescType, WeightType>>::iterator EdgeIterator;

	GraphNode<DataType, DescType, WeightType>* from_node = FindNode(from);

	EdgeIterator edge_to_delete;

	if(from_node)
	{
		bool found_edge = false;

		for(EdgeIterator edge_iterator = from_node->m_edges.begin(); edge_iterator != from_node->m_edges.end() && !found_edge; ++edge_iterator)
		{
			if( (*edge_iterator).m_destination->m_data == to)
			{
				// one of the edges is to the node being deleted, remove it
				edge_to_delete = edge_iterator;
				found_edge = true;
			}

		}

		if(!found_edge)
		{
			// edge appears to have not existed
			// throw error, etc here
		}
		else // but if it does exist, nuke it
		{
			from_node->m_edges.erase(edge_to_delete);
		}
	}
	else
	{
		// source node not found
		// throw error, etc here
	}
}

/**********************************************************************	
* Purpose: Purges the graph of all data
*
* Entry: None.
*
* Exit: Current object is wiped clean
*
************************************************************************/
template <class DataType, class DescType, class WeightType>
void Graph<DataType, DescType, WeightType>::Purge()
{
	m_nodes.clear();
}

/**********************************************************************	
* Purpose: Returns a vector of the named nodes that the graph contains
*
* Entry: None.
*
* Exit: returns a vector of the nodes in the graph.
*
************************************************************************/
template <class DataType, class DescType, class WeightType>
vector<DataType> Graph<DataType, DescType, WeightType>::GetListOfNodes(void) const
{
	vector<DataType> vec;

	for(list< GraphNode<DataType, DescType, WeightType> >::const_iterator i = m_nodes.begin(); i != m_nodes.end(); ++i)
	{
		vec.push_back((*i).m_data);
	}
	
	return vec;
}


/**********************************************************************	
* Purpose: Used to find the weight of a given edge
*
* Entry: to and from are of type DataType, will throw exception if edge not found
*
* Exit: Returns weight of the edge, or exception as said above
*
************************************************************************/
template <class DataType, class DescType, class WeightType>
WeightType Graph<DataType, DescType, WeightType>::GetWeight(DataType const& from, DataType const& to) const
{
	GraphEdge<DataType, DescType, WeightType>* edge = FindEdge(from, to);

	if(!edge)
	{
		throw exception("Edge not found!");
	}

	return edge->m_weight;
}

/**********************************************************************	
* Purpose: Used to get a description of an edge
*
* Entry: to, from are of type DataType, if the edge is not found, exception thrown
*
* Exit: Returns description of hte edge, or if not found, exception
*
************************************************************************/
template <class DataType, class DescType, class WeightType>
DescType Graph<DataType, DescType, WeightType>::GetDescription(DataType const& from, DataType const& to) const
{
	GraphEdge<DataType, DescType, WeightType>* edge = FindEdge(from, to);

	if(!edge)
	{
		throw exception("Edge not found!");
	}

	return edge->m_description;
}

/**********************************************************************	
* Purpose: Several traversal methods
*
* Entry: None.
*
* Exit: Object is traversed and traversefunc is called on each node's data.
*		Note: A different starting node can be passed to each traversal
*
************************************************************************/
template <class DataType, class DescType, class WeightType>
void Graph<DataType, DescType, WeightType>::DepthFirstTraversal(void (*traverseFunc)(DataType & data))
{
	if(m_nodes.size())
	{
		DepthFirstTraversal(m_nodes.front().m_data, traverseFunc);
	}
	else
	{
		// empty graph
	}
}
	
template <class DataType, class DescType, class WeightType>
void Graph<DataType, DescType, WeightType>::DepthFirstTraversal(DataType const& start_node, void (*traverseFunc)(DataType& data))
{
	stack< GraphNode<DataType, DescType, WeightType>* > s;
	s.push(&m_nodes.front());

	vector< GraphNode<DataType, DescType, WeightType>* > already_visited_nodes;

	GraphNode<DataType, DescType, WeightType>* ptr = nullptr;

	while(!s.empty())
	{
		ptr = s.top();
		s.pop();


		if(!VectorContains(already_visited_nodes, ptr))
		{
			// pushing the children to the stack
			list<GraphEdge<DataType, DescType, WeightType>>::iterator edge_iterator = ptr->m_edges.begin();

			while(edge_iterator != ptr->m_edges.end())
			{
				s.push((*edge_iterator).m_destination);
				++edge_iterator;
			}
			traverseFunc(ptr->m_data);
			already_visited_nodes.push_back(ptr);
		}

	}

}

template <class DataType, class DescType, class WeightType>
void Graph<DataType, DescType, WeightType>::BreadthFirstTraversal(void (*traverseFunc)(DataType & data))
{
	if(m_nodes.size())
	{
		BreadthFirstTraversal(m_nodes.front().m_data, traverseFunc);
	}
	else
	{
		// empty graph
	}
}

template <class DataType, class DescType, class WeightType>
void Graph<DataType, DescType, WeightType>::BreadthFirstTraversal(DataType const& start_node, void (*traverseFunc)(DataType & data))
{
	queue< GraphNode<DataType, DescType, WeightType>* > q;
	q.push(&m_nodes.front());

	vector< GraphNode<DataType, DescType, WeightType>* > already_visited_nodes;

	GraphNode<DataType, DescType, WeightType>* ptr = nullptr;

	while(!q.empty())
	{
		ptr = q.front();
		q.pop();


		if(!VectorContains(already_visited_nodes, ptr))
		{
			// pushing the children to the stack
			list<GraphEdge<DataType, DescType, WeightType>>::iterator edge_iterator = ptr->m_edges.begin();

			while(edge_iterator != ptr->m_edges.end())
			{
				q.push((*edge_iterator).m_destination);
				++edge_iterator;
			}
			traverseFunc(ptr->m_data);
			already_visited_nodes.push_back(ptr);
		}

	}
}
