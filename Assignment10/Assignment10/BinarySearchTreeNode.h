/************************************************************************
* Class: BinarySearchTreeNode
*
* Purpose: This class is a node of a binary search tree.
*
* Manager functions:	
* 	BinarySearchTreeNode()
*	BinarySearchTreeNode(Node* left, Node* right, T data)
*	BinarySearchTreeNode(T data)
*	BinarySearchTreeNode(Node const& copy)
*		Various constructors to set up the object with the given parameters.
*	~BinarySearchTreeNode()
*		destructor
*	operator=()
*		Assignment operator
*
* Methods:
*	GetData()
*		Returns node's data
*	isInTree(T data)
*		returns true is data is in the tree, false otherwise
*	Insert(T data)
*		Inserts data into the tree
*	InOrderTraversal()
*	PreOrderTraversal()
*	PostOrderTraversal()
*	BreadthFirstTraversal()
*		Various traversal methods for hte tree
*	
*************************************************************************/
#pragma once

#include <queue>
using std::queue;

template <class T>
class BinarySearchTreeNode
{
	private:
		BinarySearchTreeNode<T>* m_left;
		BinarySearchTreeNode<T>* m_right;

		T m_data;

		BinarySearchTreeNode();
		BinarySearchTreeNode(BinarySearchTreeNode<T>* left, BinarySearchTreeNode<T>* right, const T &data);
		BinarySearchTreeNode(const T &data);
		BinarySearchTreeNode(const BinarySearchTreeNode<T> &copy);
		
		BinarySearchTreeNode<T> const& operator=(BinarySearchTreeNode<T> const& rhs);

		void Insert(const T &data);

		const T & GetData(void) const;

		bool isInTree(const T &data) const;
		
		void InOrderTraversal(void (*traverseFunc)(T& data));
		void PreOrderTraversal(void (*traverseFunc)(T& data));
		void PostOrderTraversal(void (*traverseFunc)(T& data));
		void BreadthFirstTraversal(void (*traverseFunc)(T& data));

		void InOrderTraversal(void (*traverseFunc)(T const& data)) const;
		void PreOrderTraversal(void (*traverseFunc)(T const& data)) const;
		void PostOrderTraversal(void (*traverseFunc)(T const& data)) const;
		void BreadthFirstTraversal(void (*traverseFunc)(T const& data)) const;

		~BinarySearchTreeNode();

	public:
		template <class T> friend class BinarySearchTree;	
};

/**********************************************************************	
* Purpose: Various constructors for BinarySearchTreeNodes. Acceptable forms:
*		Note: "Node" used as shorthand for BinarySearchTreeNode
*		BinarySearchTreeNode()									(default constructor)
*		BinarySearchTreeNode(T data)							(1arg constructor)
*		BinarySearchTreeNode(Node* left, Node* right, T data)	(3arg constructor)
*		BinarySearchTreeNode(Node)								(copy constructor)
*
* Entry:
*	Parameters:
*		data is of type T
*		left, right, are of type BinarySearchTreeNode*
*
* Exit: An object is created with the given parameters.
*
************************************************************************/
template <class T>
BinarySearchTreeNode<T>::BinarySearchTreeNode(void) : m_data(T()), m_left(nullptr), m_right(nullptr)
{

}

template <class T>
BinarySearchTreeNode<T>::BinarySearchTreeNode(T const& data) : m_data(data), m_left(nullptr), m_right(nullptr)
{

}

template <class T>
BinarySearchTreeNode<T>::BinarySearchTreeNode(BinarySearchTreeNode<T>* left, BinarySearchTreeNode<T>* right, T const& data) :  m_data(data), m_left(left), m_right(right)
{

}

template <class T>
BinarySearchTreeNode<T>::BinarySearchTreeNode(BinarySearchTreeNode<T> const& copy) : m_data(copy.m_data), m_left(copy.m_left), m_right(copy.m_right)
{

}

/**********************************************************************	
* Purpose: Assignment operator
*
* Entry: None.
*
* Exit: Current object is assigned the same values as the rhs'. Note: INTENTIONAL SHALLOW COPY
*
************************************************************************/
template <class T>
BinarySearchTreeNode<T> const& BinarySearchTreeNode<T>::operator=(BinarySearchTreeNode<T> const& rhs)
{
	m_data = rhs.m_data;
	m_left = rhs.m_left;
	m_right = rhs.m_right;
	return *this;
}

/**********************************************************************	
* Purpose: Destructor
*		Note: Intentionally does not clean up any children nodes. 
*			That is handled entirely in the tree class.
*
* Entry: None.
*
* Exit: Object is destructed
*
************************************************************************/
template <class T>
BinarySearchTreeNode<T>::~BinarySearchTreeNode(void)
{

}

/**********************************************************************	
* Purpose: Used to insert data into the tree, only used by tree class
*
* Entry:
*	Parameters:
*		data is of type T
*
* Exit: Tree now contains data.
*
************************************************************************/
template <class T>
void BinarySearchTreeNode<T>::Insert(T const& data)
{
	if(data == m_data) // this node is the same as the node being inserted
	{
		// either add to left, right, or ignore duplicate data (unique keys)
		// current implementation is to ignore duplicate data, as searching the 
		// tree is implemented to only find the first node matching key
	}
	else if(data > m_data)
	{
		if(m_right)
		{
			m_right->Insert(data);
		}
		else
		{
			m_right = new BinarySearchTreeNode<T>(nullptr, nullptr, data);
		}
	}
	else
	{
		if(m_left)
		{
			m_left->Insert(data);
		}
		else
		{
			m_left = new BinarySearchTreeNode<T>(nullptr, nullptr, data);
		}
	}
}

/**********************************************************************	
* Purpose: Returns node's data
*
************************************************************************/
template <class T>
T BinarySearchTreeNode<T>::GetData(void) const
{
	return m_data;
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
bool BinarySearchTreeNode<T>::isInTree(T const& data) const
{
	bool inTree = false;
	if(m_data == data)
	{
		inTree = true;
	}
	else if(data > m_data)
	{
		if(m_right)
		{
			inTree = m_right->isInTree(data);
		}
	}
	else if(data < m_data)
	{
		if(m_left)
		{
			inTree = m_left->isInTree(data);
		}
	}
	return inTree;
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
*		These are all built assuming the current node is the root of the tree, 
*		and traverses through all children of current node.
*
* Entry:
*	Parameters:
*		traverseFunc is a function pointer to a function that takes data 
*		by & or by const& respectively.
*
* Exit: The object is traversed and the traverseFunc is called on each node's data.
*
************************************************************************/
template <class T>
void BinarySearchTreeNode<T>::InOrderTraversal(void (*traverseFunc)(T& data))
{
	if(m_left)
	{
		m_left->InOrderTraversal(traverseFunc);
	}
	
	traverseFunc(m_data);

	if(m_right)
	{
		m_right->InOrderTraversal(traverseFunc);
	}
}
template <class T>
void BinarySearchTreeNode<T>::InOrderTraversal(void (*traverseFunc)(T const& data)) const
{
	if(m_left)
	{
		m_left->InOrderTraversal(traverseFunc);
	}
	
	traverseFunc(m_data);

	if(m_right)
	{
		m_right->InOrderTraversal(traverseFunc);
	}
}

template <class T>
void BinarySearchTreeNode<T>::PreOrderTraversal(void (*traverseFunc)(T& data))
{
	traverseFunc(m_data);

	if(m_left)
	{
		m_left->PreOrderTraversal(traverseFunc);
	}

	if(m_right)
	{
		m_right->PreOrderTraversal(traverseFunc);
	}
}
template <class T>
void BinarySearchTreeNode<T>::PreOrderTraversal(void (*traverseFunc)(T const& data)) const
{
	traverseFunc(m_data);

	if(m_left)
	{
		m_left->PreOrderTraversal(traverseFunc);
	}

	if(m_right)
	{
		m_right->PreOrderTraversal(traverseFunc);
	}
}

template <class T>
void BinarySearchTreeNode<T>::PostOrderTraversal(void (*traverseFunc)(T& data))
{
	if(m_left)
	{
		m_left->PostOrderTraversal(traverseFunc);
	}

	if(m_right)
	{
		m_right->PostOrderTraversal(traverseFunc);
	}

	traverseFunc(m_data);
}
template <class T>
void BinarySearchTreeNode<T>::PostOrderTraversal(void (*traverseFunc)(T const& data)) const
{
	if(m_left)
	{
		m_left->PostOrderTraversal(traverseFunc);
	}

	if(m_right)
	{
		m_right->PostOrderTraversal(traverseFunc);
	}

	traverseFunc(m_data);
}

template <class T>
void BinarySearchTreeNode<T>::BreadthFirstTraversal(void (*traverseFunc)(T& data))
{
	queue< BinarySearchTreeNode<T>* > q;
	q.push(this);

	BinarySearchTreeNode<T>* ptr = nullptr;

	while(!q.empty())
	{
		ptr = q.front();
		q.pop();

		traverseFunc(ptr->m_data);
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
template <class T>
void BinarySearchTreeNode<T>::BreadthFirstTraversal(void (*traverseFunc)(T const& data)) const
{
	queue< BinarySearchTreeNode<T> const* > q;
	q.push(this);

	BinarySearchTreeNode<T> const* ptr = nullptr;

	while(!q.empty())
	{
		ptr = q.front();
		q.pop();

		traverseFunc(ptr->m_data);
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