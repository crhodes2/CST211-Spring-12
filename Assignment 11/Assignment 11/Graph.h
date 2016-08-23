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

	GraphNode<DataType, DescType, WeightType>* FindNode(DataType const& data);

	bool NodeExists(DataType const& data);
public:
	
	Graph();
	Graph(Graph<DataType, DescType, WeightType> const& copy);
	~Graph();

	Graph<DataType, DescType, WeightType> const& operator=(Graph<DataType, DescType, WeightType> const& rhs);

	void InsertNode(DataType const& data);
	virtual void InsertEdge(DataType const& from, DataType const& to, DescType const& description, WeightType const& weight);
	virtual void ForceInsertEdge(DataType const& from, DataType const& to, DescType const& description, WeightType const& weight);

	void DeleteNode(DataType const& data);
	virtual void DeleteEdge(DataType const& from, DataType const& to);
	
	void Purge();

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
* Purpose: Used to find a pointer to a given node matching data
*
* Entry: None.
*
* Exit: A pointer to the node is returned, or nullptr if not found
*
************************************************************************/
template <class DataType, class DescType, class WeightType>
GraphNode<DataType, DescType, WeightType>* Graph<DataType, DescType, WeightType>::FindNode(DataType const& data)
{
	GraphNode<DataType, DescType, WeightType>* found_node = nullptr;

	for(list<GraphNode<DataType, DescType, WeightType>>::iterator i = m_nodes.begin(); i != m_nodes.end(); ++i)
	{
		if((*i).m_data == data)
		{
			found_node = &(*i);
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
<<<<<<< .mine
	// Quote from wiki on Graph Traversal: "A Depth-first search (DFS) is a technique for traversing a finite undirected graph. DFS visits the child nodes before visiting the sibling nodes, that is, it traverses the depth of the tree before the breadth. That called DFS. Usually a stack is used in the search process."
	
	stack< GraphNode<DataType, WeightType>* > s;
=======
	stack< GraphNode<DataType, DescType, WeightType>* > s;
>>>>>>> .r308
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
<<<<<<< .mine
	// Quote from Wiki on Graph Traversal: "A Breadth-first search (BFS) is another technique for traversing a finite undirected graph. BFS visits the sibling nodes before visiting the child nodes. Usually a queue is used in the search process."
	
	// set up a queue to hold pointer to the nodes that we will traverse over
	queue< GraphNode<DataType, WeightType>* > q;
=======
	queue< GraphNode<DataType, DescType, WeightType>* > q;
>>>>>>> .r308

	// to start things off, push the front of the current node list (currently pulls the first node from the list, despite me having the start node parameter, my mistake, ignore that param)
	q.push(&m_nodes.front());

<<<<<<< .mine
	// to tell which nodes I've been to already, instead of using a processed flag, which I didn't like the concept of, I store a local vector of pointers to the nodes I've been to already
	vector< GraphNode<DataType, WeightType>* > already_visited_nodes;
=======
	vector< GraphNode<DataType, DescType, WeightType>* > already_visited_nodes;
>>>>>>> .r308

<<<<<<< .mine
	// pointer used for temporary node* storage in the loop below
	GraphNode<DataType, WeightType>* ptr = nullptr;
=======
	GraphNode<DataType, DescType, WeightType>* ptr = nullptr;
>>>>>>> .r308

	// loop until the queue has been fully expended of node*s
	while(!q.empty())
	{
		// the next two lines essentially pop the first value from the queue and into ptr. (pop() doesn't return the element stupidly enough, so you have to do this)
		ptr = q.front();
		q.pop();


		// VectorContains is just a helper function I wrote for this crap that takes a vector<T> and a T, and searches the vector for that element and returns true if found, false otherwise
		if(!VectorContains(already_visited_nodes, ptr)) // this if statement just checks that the current ptr isn't a node we've seen yet (aka processed in todd speak)
		{
			// set up an iterator for a list of edges (the data type each of my nodes has to hold the edge/arc data) and set it to the beginning of the current ptr's edges list
			list<GraphEdge<DataType, DescType, WeightType>>::iterator edge_iterator = ptr->m_edges.begin();

			// loop over all the edges in that list
			while(edge_iterator != ptr->m_edges.end())
			{
				// add the edge's "to" node, i.e. "from" node A, "to" node B, with whatever weight
				q.push((*edge_iterator).m_destination);

				// then just keep the iterator iterating over all the edges, pushing each edge's destination node to the queue of nodes to traverse through
				++edge_iterator;
			}

			// actually call the traverse function on the ptr's data, this particular function is the nonconst version, I didn't bother with const version as honestly, const for this was a royal pain in ass and I just gave up on it, I'll probably do it for Djikstra's.
			traverseFunc(ptr->m_data);

			// we just "visited" ptr, so push that ptr onto the vector of nodes we've already visited so it will prevent us traversing to it again later
			already_visited_nodes.push_back(ptr);
		}
	}
}
