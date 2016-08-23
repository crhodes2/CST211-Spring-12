#pragma once

#include <algorithm>
using std::max;

#include <queue>
using std::queue;

template <class T>
class AVLTreeNode
{
private:
	T m_data;

	AVLTreeNode<T>* m_left;
	AVLTreeNode<T>* m_right;

	short int m_balanceFactor;
	unsigned m_height;

	AVLTreeNode();
	AVLTreeNode(AVLTreeNode<T>* left, AVLTreeNode<T>* right, T const& data);
	AVLTreeNode(AVLTreeNode<T> const& copy);
	~AVLTreeNode();

	AVLTreeNode<T> const& operator=(AVLTreeNode<T> const& rhs);

	void UpdateHeight(void);
	void UpdateBalanceFactor(void);
		
	void InOrderTraversal(void (*traverseFunc)(T& data));
	void PreOrderTraversal(void (*traverseFunc)(T& data));
	void PostOrderTraversal(void (*traverseFunc)(T& data));
	void BreadthFirstTraversal(void (*traverseFunc)(T& data));

	void InOrderTraversal(void (*traverseFunc)(T const& data)) const;
	void PreOrderTraversal(void (*traverseFunc)(T const& data)) const;
	void PostOrderTraversal(void (*traverseFunc)(T const& data)) const;
	void BreadthFirstTraversal(void (*traverseFunc)(T const& data)) const;

public:
	template <class T> friend class AVLTree;
};

template <class T>
AVLTreeNode<T>::AVLTreeNode() : m_left(nullptr), m_right(nullptr), m_balanceFactor(0), m_height(0), m_data(T())
{

}

template <class T>
AVLTreeNode<T>::AVLTreeNode(AVLTreeNode<T>* left, AVLTreeNode<T>* right, T const& data) : m_left(left), m_right(right), m_data(data), m_balanceFactor(0), m_height(0)
{
	if(m_right && m_left)
	{
		m_height = max(m_right->m_height, m_left->m_height);

		m_balanceFactor = m_left->m_height - m_right->m_height;
	}
	else if(m_right && !m_left)
	{
		m_height = m_right->m_height;
	}
	else if(!m_right && m_left)
	{
		m_height = m_left->m_height;
	}

	if(m_left || m_right)
		++m_height;
}

// shallow copy
template <class T>
AVLTreeNode<T>::AVLTreeNode(AVLTreeNode<T> const& copy) : m_left(copy.m_left), m_right(copy.m_right), m_height(copy.m_height), m_data(copy.m_data), m_balanceFactor(copy.m_balanceFactor)
{

}

// blank destructor, this behavior is handled by the tree, not the individual nodes
template <class T>
AVLTreeNode<T>::~AVLTreeNode()
{

}

// shallow copy
template <class T>
AVLTreeNode<T> const& AVLTreeNode<T>::operator=(AVLTreeNode<T> const& rhs)
{
	m_left = rhs.m_left;
	m_right = rhs.m_right;
	m_data = rhs.m_data;
	m_height = rhs.m_height;
	m_balanceFactor = rhs.m_balanceFactor;

	return *this;
}

/**********************************************************************	
* Purpose: Various traversal methods for the avl tree. 
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
void AVLTreeNode<T>::InOrderTraversal(void (*traverseFunc)(T& data))
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
void AVLTreeNode<T>::InOrderTraversal(void (*traverseFunc)(T const& data)) const
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
void AVLTreeNode<T>::PreOrderTraversal(void (*traverseFunc)(T& data))
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
void AVLTreeNode<T>::PreOrderTraversal(void (*traverseFunc)(T const& data)) const
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
void AVLTreeNode<T>::PostOrderTraversal(void (*traverseFunc)(T& data))
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
void AVLTreeNode<T>::PostOrderTraversal(void (*traverseFunc)(T const& data)) const
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
void AVLTreeNode<T>::BreadthFirstTraversal(void (*traverseFunc)(T& data))
{
	queue< AVLTreeNode<T>* > q;
	q.push(this);

	AVLTreeNode<T>* ptr = nullptr;

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
void AVLTreeNode<T>::BreadthFirstTraversal(void (*traverseFunc)(T const& data)) const
{
	queue< AVLTreeNode<T> const* > q;
	q.push(this);

	AVLTreeNode<T> const* ptr = nullptr;

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
void AVLTreeNode<T>::UpdateHeight(void)
{
	if(m_right && m_left)
	{
		m_height = max(m_right->m_height, m_left->m_height);
	}
	else if(m_right && !m_left)
	{
		m_height = m_right->m_height;
	}
	else if(!m_right && m_left)
	{
		m_height = m_left->m_height;
	}
	else
	{
		m_height = 0;
	}

	if(m_left || m_right)
		++m_height;
}

template <class T>
void AVLTreeNode<T>::UpdateBalanceFactor(void)
{
	if(m_right && m_left)
	{
		m_balanceFactor = m_left->m_height - m_right->m_height;
	}
	else if(m_right && !m_left)
	{
		m_balanceFactor = (m_right->m_height > 0)? -2 : -1;
	}
	else if(!m_right && m_left)
	{
		m_balanceFactor = (m_left->m_height > 0)? 2 : 1;
	}
	else
	{
		m_balanceFactor = 0;
	}
}