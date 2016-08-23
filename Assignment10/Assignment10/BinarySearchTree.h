/************************************************************************
* Class: BinarySearchTree
*
* Purpose: This class is a binary search tree.
*
* Manager functions:	
* 	BinarySearchTree()
*	BinarySearchTree(BinarySearchTree const& copy)
*		Various constructors to set up the object with the given parameters.
*	~BinarySearchTree()
*		destructor
*	operator=()
*		Assignment operator
*
* Methods:
*	isInTree(T data)
*		returns true is data is in the tree, false otherwise
*	Insert(T data)
*		Inserts data into the tree
*	Delete(T data)
*		Deletes node in the tree matching data
*	Purge()
*		Removes all data from the tree
*	Height()
*		Gets the height of the tree
*	InOrderTraversal()
*	PreOrderTraversal()
*	PostOrderTraversal()
*	BreadthFirstTraversal()
*		Various traversal methods for the tree
*	
*************************************************************************/
#pragma once

#include "BinarySearchTreeNode.h"
#include "Exception.h"

#include <queue>
using std::queue;

#include <algorithm>
using std::max;

template <class T>
class BinarySearchTree
{
	private:
		BinarySearchTreeNode<T>* m_root;

		void Purge(BinarySearchTreeNode<T>* node);
		void Delete(T const& data, BinarySearchTreeNode<T>* & node);

		BinarySearchTreeNode<T>* FindMinimum(BinarySearchTreeNode<T>* node) const;

		unsigned Height(BinarySearchTreeNode<T>* node) const;

	public:
		BinarySearchTree(void);
		BinarySearchTree(BinarySearchTree<T> const& copy);
		~BinarySearchTree(void);

		BinarySearchTree<T> const& operator=(BinarySearchTree<T> const& rhs);

		void Insert(T const& data);
		void Delete(T const& data);
		void Purge();

		unsigned Height(void) const;
		
		void InOrderTraversal(void (*traverseFunc)(T& data));
		void PreOrderTraversal(void (*traverseFunc)(T& data));
		void PostOrderTraversal(void (*traverseFunc)(T& data));
		void BreadthFirstTraversal(void (*traverseFunc)(T& data));

		void InOrderTraversal(void (*traverseFunc)(T const& data)) const;
		void PreOrderTraversal(void (*traverseFunc)(T const& data)) const;
		void PostOrderTraversal(void (*traverseFunc)(T const& data)) const;
		void BreadthFirstTraversal(void (*traverseFunc)(T const& data)) const;

		bool isInTree(T const& data) const;
};

/**********************************************************************	
* Purpose: Various constructors for BinarySearchTree. Acceptable forms:
*		Note: "Node" used as shorthand for BinarySearchTreeNode
*		BinarySearchTree()									(default constructor)
*		BinarySearchTree(BinarySearchTree)					(copy constructor)
*
* Entry: None.
*
* Exit: An object is created with the given parameters.
*
************************************************************************/
template <class T>
BinarySearchTree<T>::BinarySearchTree(void) : m_root(nullptr)
{
	
}

template <class T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T> const& copy) : m_root(nullptr)
{
	// duplicate the entire tree
	// method of doing so is basically inserting each element while breadth-first traversing the copy
	queue< BinarySearchTreeNode<T> const* > q;
	q.push(copy.m_root);

	BinarySearchTreeNode<T> const* ptr = nullptr;

	while(!q.empty())
	{
		ptr = q.front();
		q.pop();

		Insert(ptr->m_data);
		if(ptr->m_left)
		{
			q.push(ptr->m_left);
		}
		if(ptr->m_right)
		{
			q.push(ptr->m_right);
		}
	}
}
/**********************************************************************	
* Purpose: Destructor
*
* Entry: None.
*
* Exit: Object is destroyed.
*
************************************************************************/
template <class T>
BinarySearchTree<T>::~BinarySearchTree(void)
{
	Purge();
}

/**********************************************************************	
* Purpose: Assignment operator
*
* Entry:
*	Parameters:
*		rhs is of type BinarySearchTree (with same templated class type)
*
* Exit: Current object is a duplicate copy of the rhs. (Deep copied)
*
************************************************************************/
template <class T>
BinarySearchTree<T> const& BinarySearchTree<T>::operator=(BinarySearchTree<T> const& rhs)
{
	// unsure if this is even possible on a member function.
	// It should work in theory, but VS doesn't allow compilation, and google/stackoverflow didn't turn up much
	//rhs.BreadthFirstTraversal(&Insert<T>);

	
	// duplicate the entire tree
	// method of doing so is basically inserting each element while breadth-first traversing the rhs
	queue< BinarySearchTreeNode<T> const* > q;
	q.push(rhs.m_root);

	BinarySearchTreeNode<T> const* ptr = nullptr;

	while(!q.empty())
	{
		ptr = q.front();
		q.pop();

		Insert(ptr->m_data);
		if(ptr->m_left)
		{
			q.push(ptr->m_left);
		}
		if(ptr->m_right)
		{
			q.push(ptr->m_right);
		}
	}

	return *this;
}

/**********************************************************************	
* Purpose: Used to insert data into the tree
*
* Entry:
*	Parameters:
*		data is of type T
*
* Exit: data added to tree
*
************************************************************************/
template <class T>
void BinarySearchTree<T>::Insert(T const& data)
{
	if(m_root) // tree is not empty, add to root and let it recurse down tree if need be
	{
		m_root->Insert(data);
	}
	else // tree is empty, make the root a new node with the inserted data
	{
		m_root = new BinarySearchTreeNode<T>(nullptr, nullptr, data);
	}
}

/**********************************************************************	
* Purpose: Removes the nodes from the tree that match data. Limited to first occurence.
*
* Entry:
*	Parameters:
*		data is of type T
*
* Exit: Node is removed from tree. If data isn't found, function does nothing.
*
************************************************************************/
template <class T>
void BinarySearchTree<T>::Delete(T const& data)
{
	if(m_root)
	{
		Delete(data, m_root);
	}else{
		throw Exception("Cannot delete from empty tree");
	}
}

// helper function for above
template <class T>
void BinarySearchTree<T>::Delete(T const& data, BinarySearchTreeNode<T>* & node)
{
	if(node == nullptr)
	{
		// do nothing
	}
	else if(data < node->m_data)
	{
		Delete(data, node->m_left);
	}
	else if(data > node->m_data)
	{
		Delete(data, node->m_right);
	}
	else
	{
		BinarySearchTreeNode<T>* tempNode = nullptr;

		if(node->m_left == nullptr && node->m_right == nullptr)
		{
			delete node;
			node = nullptr;
		}
		else if(node->m_left == nullptr)
		{
			tempNode = node;
			node = node->m_right;
			delete tempNode;
		}
		else if(node->m_right == nullptr)
		{
			tempNode = node;
			node = node->m_left;
			delete tempNode;
		}
		else
		{
			tempNode = FindMinimum(node->m_right);
			node->m_data = tempNode->m_data;
			Delete(node->m_data, node->m_right);
		}
	}
}

/**********************************************************************	
* Purpose: Used to remove all data from tree
*
* Entry: None.
*
* Exit: tree is now entirely empty
*
************************************************************************/
template <class T>
void BinarySearchTree<T>::Purge()
{
	Purge(m_root);
	m_root = nullptr;
}

// helper function for above
template <class T>
void BinarySearchTree<T>::Purge(BinarySearchTreeNode<T>* node)
{
	if(node)
	{
		Purge(node->m_left);
		Purge(node->m_right);
		delete node;
	}
}

/**********************************************************************	
* Purpose: Used to determine the height of the tree
*
* Entry: None.
*
* Exit: Returns height of hte tree.
*
************************************************************************/
template <class T>
unsigned BinarySearchTree<T>::Height(void) const
{
	return Height(m_root);
}

// helper function for above
template <class T>
unsigned BinarySearchTree<T>::Height(BinarySearchTreeNode<T>* node) const
{
	unsigned height = 0;
	if(node == nullptr || (node->m_left == nullptr && node->m_right == nullptr))
	{
		height = 0; // tree has no nodes, or is a leaf node
	}
	else
	{
		height = max(Height(node->m_left), Height(node->m_right)) + 1;
	}
	return height;
}

/**********************************************************************	
* Purpose: Various traversal methods for the binary search tree. 
*		Includes:
*			In-order
*			Pre-order
*			Post-order
*			Breadth-First
*		As well as const flavors of each.
*		Used for traversing the tree and performing a function on each node's data.
*
* Entry:
*	Parameters:
*		traverseFunc is a function pointer to a function that takes data 
*		by & or by const& respectively.
*
* Exit: The object is traversed and the traverseFunc is called on each node's data.
*		If tree is empty, will simply output to cout saying so.
*
************************************************************************/
template <class T>
void BinarySearchTree<T>::InOrderTraversal(void (*traverseFunc)(T& data))
{
	if(m_root)
	{
		m_root->InOrderTraversal(traverseFunc);
	}
	else
	{
		cout << "Tree is currently empty." << endl;
	}
}
template <class T>
void BinarySearchTree<T>::InOrderTraversal(void (*traverseFunc)(T const& data)) const
{
	if(m_root)
	{
		m_root->InOrderTraversal(traverseFunc);
	}
	else
	{
		cout << "Tree is currently empty." << endl;
	}
}

template <class T>
void BinarySearchTree<T>::PreOrderTraversal(void (*traverseFunc)(T& data))
{
	if(m_root)
	{
		m_root->PreOrderTraversal(traverseFunc);
	}
	else
	{
		cout << "Tree is currently empty." << endl;
	}
}
template <class T>
void BinarySearchTree<T>::PreOrderTraversal(void (*traverseFunc)(T const& data)) const
{
	if(m_root)
	{
		m_root->PreOrderTraversal(traverseFunc);
	}
	else
	{
		cout << "Tree is currently empty." << endl;
	}
}

template <class T>
void BinarySearchTree<T>::PostOrderTraversal(void (*traverseFunc)(T& data))
{
	if(m_root)
	{
		m_root->PostOrderTraversal(traverseFunc);
	}
	else
	{
		cout << "Tree is currently empty." << endl;
	}
}
template <class T>
void BinarySearchTree<T>::PostOrderTraversal(void (*traverseFunc)(T const& data)) const
{
	if(m_root)
	{
		m_root->PostOrderTraversal(traverseFunc);
	}
	else
	{
		cout << "Tree is currently empty." << endl;
	}
}

template <class T>
void BinarySearchTree<T>::BreadthFirstTraversal(void (*traverseFunc)(T& data))
{
	if(m_root)
	{
		m_root->BreadthFirstTraversal(traverseFunc);
	}
	else
	{
		cout << "Tree is currently empty." << endl;
	}
}
template <class T>
void BinarySearchTree<T>::BreadthFirstTraversal(void (*traverseFunc)(T const& data)) const
{
	if(m_root)
	{
		m_root->BreadthFirstTraversal(traverseFunc);
	}
	else
	{
		cout << "Tree is currently empty." << endl;
	}
}

/**********************************************************************	
* Purpose: Used to determine if a value is in the tree.
*
* Entry:
*	Parameters:
*		data is of type T
*
* Exit: Return bool representing if the data was found in the tree.
*
************************************************************************/
template <class T>
bool BinarySearchTree<T>::isInTree(T const& data) const
{
	bool inTree = false;
	
	if(m_root)
	{
		inTree = m_root->isInTree(data);
	}

	return inTree;
}

/**********************************************************************	
* Purpose: Helper function to determine the minimal value in the subtrees of a node
*
* Entry:
*	Parameters:
*		node is of type Node*
*
* Exit: Return pointer to minimal node
*
************************************************************************/
template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::FindMinimum(BinarySearchTreeNode<T>* node) const
{
	BinarySearchTreeNode<T>* ptr = 0;

	if(node == nullptr)
	{
		ptr = nullptr;
	}
	else if(node->m_left == nullptr)
	{
		ptr = node;
	}
	else 
	{
		ptr = FindMinimum(node->m_left);
	}
	return ptr;
}