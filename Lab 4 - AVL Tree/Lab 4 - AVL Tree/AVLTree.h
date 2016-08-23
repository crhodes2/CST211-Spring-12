#pragma once

#include "AVLTreeNode.h"
#include "Exception.h"

#include <queue>
using std::queue;

#include <stack>
using std::stack;


class NodeNotFoundException : public Exception
{
	NodeNotFoundException() : Exception("Exception: Node not found!"){}
};


template <class T>
class AVLTree
{
	private:
		AVLTreeNode<T>* m_root;

		void Purge(AVLTreeNode<T>* node);

		AVLTreeNode<T>* Insert(T const& data, AVLTreeNode<T> *& node, int & height_change);
		void Delete(T const& data, AVLTreeNode<T> *& node);
		T* Delete2(T const& data, AVLTreeNode<T> *& node, short & height_change);

		int RotateRight(AVLTreeNode<T> *& node);
		int RotateLeft(AVLTreeNode<T> *& node);

		int RotateRightLeft(AVLTreeNode<T> *& node);
		int RotateLeftRight(AVLTreeNode<T> *& node);

		int Rebalance(AVLTreeNode<T> *& node);
		void RebalanceUp(AVLTreeNode<T> *& node);

		int Height(AVLTreeNode<T>* node) const;

		AVLTreeNode<T>* FindMinimum(AVLTreeNode<T>* node) const;

		AVLTreeNode<T>* FindNode(T const& data) const;
		AVLTreeNode<T>* FindNode(T const& data, AVLTreeNode<T>* node) const;
		
		static enum BALANCES {RIGHT_TOO_HEAVY = -2, RIGHT_HEAVY = -1, BALANCED = 0, LEFT_HEAVY = 1, LEFT_TOO_HEAVY = 2};
	public:
		AVLTree(void);
		AVLTree(AVLTree<T> const& copy);
		~AVLTree(void);

		AVLTree<T> const& operator=(AVLTree<T> const& rhs);

		void Purge(void);

		void Insert(T const& data);
		void Delete(T const& data);

		int Height(void) const;

		bool isInTree(T const& data) const;

		bool isEmpty(void) const;
		
		void InOrderTraversal(void (*traverseFunc)(T& data));
		void PreOrderTraversal(void (*traverseFunc)(T& data));
		void PostOrderTraversal(void (*traverseFunc)(T& data));
		void BreadthFirstTraversal(void (*traverseFunc)(T& data));

		void InOrderTraversal(void (*traverseFunc)(T const& data)) const;
		void PreOrderTraversal(void (*traverseFunc)(T const& data)) const;
		void PostOrderTraversal(void (*traverseFunc)(T const& data)) const;
		void BreadthFirstTraversal(void (*traverseFunc)(T const& data)) const;
};

template <class T>
bool AVLTree<T>::isEmpty(void) const
{
	return (m_root == nullptr);
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::FindNode(T const& data) const
{
	return FindNode(data, m_root);
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::FindNode(T const& data, AVLTreeNode<T>* node) const
{
	AVLTreeNode<T>* found_node = nullptr;

	if(node)
	{
		if(node->m_data == data)
		{
			found_node = node;
		}
		else if(data > node->m_data)
		{
			if(node->m_right)
			{
				found_node = FindNode(data, node->m_right);
			}
		}
		else if(data < node->m_data)
		{
			if(node->m_left)
			{
				found_node = FindNode(data, node->m_left);
			}
		}
	}
	return found_node;
}

/**********************************************************************	
* Purpose: Various constructors for AVLTree. Acceptable forms:
*		Note: "Node" used as shorthand for AVLTreeNode
*		AVLTree()							(default constructor)
*		AVLTree(AVLTree)					(copy constructor)
*
* Entry: None.
*
* Exit: An object is created with the given parameters.
*
************************************************************************/
template <class T>
AVLTree<T>::AVLTree(void) : m_root(nullptr)
{
	
}

template <class T>
AVLTree<T>::AVLTree(AVLTree<T> const& copy) : m_root(nullptr)
{
	// duplicate the entire tree
	// method of doing so is basically inserting each element while breadth-first traversing the copy
	queue< AVLTreeNode<T> const* > q;
	q.push(copy.m_root);

	AVLTreeNode<T> const* ptr = nullptr;

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
AVLTree<T>::~AVLTree(void)
{
	Purge();
}

/**********************************************************************	
* Purpose: Assignment operator
*
* Entry:
*	Parameters:
*		rhs is of type AVLTree (with same templated class type)
*
* Exit: Current object is a duplicate copy of the rhs. (Deep copied)
*
************************************************************************/
template <class T>
AVLTree<T> const& AVLTree<T>::operator=(AVLTree<T> const& rhs)
{
	// duplicate the entire tree
	// method of doing so is basically inserting each element while breadth-first traversing the rhs
	queue< AVLTreeNode<T> const* > q;
	q.push(rhs.m_root);

	AVLTreeNode<T> const* ptr = nullptr;

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
void AVLTree<T>::Insert(T const& data)
{
	int height_change;
	Insert(data, m_root, height_change);
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::Insert(T const& data, AVLTreeNode<T> *& node, int & height_change)
{
	AVLTreeNode<T>* found_node = nullptr;

	if(node == nullptr)
	{
		node = new AVLTreeNode<T>(nullptr, nullptr, data);
		height_change = 1;
	}
	else
	{
		int increase = 0;
		
		if(data == node->m_data) // this node is the same as the node being inserted
		{
			// either add to left, right, or ignore duplicate data (unique keys)
			// current implementation is to ignore duplicate data, as searching the 
			// tree is implemented to only find the first node matching key
		}
		else if(data > node->m_data)
		{
			found_node = Insert(data, node->m_right, height_change);
			if (!found_node)
			{
				increase = height_change;
			}
		}
		else if(data < node->m_data)
		{
			found_node = Insert(data, node->m_left, height_change);
			if (!found_node)
			{
				increase = -height_change;
			}
		}

		//node->m_balanceFactor -= increase;

		// recalc height
		node->UpdateHeight();
		node->UpdateBalanceFactor();

		Rebalance(node);

		//height_change = (increase && node->m_balanceFactor) ? (1 - Rebalance(node)) : 0;
	}
	return found_node;
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
bool AVLTree<T>::isInTree(T const& data) const
{
	return FindNode(data, m_root) != nullptr;
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
void AVLTree<T>::Purge()
{
	Purge(m_root);
	m_root = nullptr;
}

// helper function for above
template <class T>
void AVLTree<T>::Purge(AVLTreeNode<T>* node)
{
	if(node)
	{
		Purge(node->m_left);
		Purge(node->m_right);
		delete node;
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
void AVLTree<T>::Delete(T const& data)
{
	if(m_root)
	{
		Delete(data, m_root); 
	}
}

// helper function for above
template <class T>
void AVLTree<T>::Delete(T const& data, AVLTreeNode<T> *& node)
{
	if(node == nullptr)
	{
		// do nothing
	}
	else if(data < node->m_data)
	{
		Delete(data, node->m_left);

		/*
		// we deleted a child of node, so update the balance factors all the way back up
		node->UpdateHeight();
		node->UpdateBalanceFactor();

		// now, rebalance
		if(node->m_balanceFactor == LEFT_TOO_HEAVY || node->m_balanceFactor == RIGHT_TOO_HEAVY)
		{
			Rebalance(node);
		}
		*/
	}
	else if(data > node->m_data)
	{
		Delete(data, node->m_right);

		/*
		node->UpdateHeight();
		node->UpdateBalanceFactor();

		// now, rebalance
		if(node->m_balanceFactor == LEFT_TOO_HEAVY || node->m_balanceFactor == RIGHT_TOO_HEAVY)
		{
			Rebalance(node);
		}
		*/
	}
	else
	{
		// node is the node we want to delete!
		AVLTreeNode<T>* tempNode = nullptr;

		if(node->m_left == nullptr && node->m_right == nullptr) // leaf node
		{
			delete node;
			node = nullptr;
		}
		else if(node->m_left == nullptr && node->m_right) // right child only
		{
			tempNode = node;
			node = node->m_right;
			delete tempNode;
		}
		else if(node->m_left && node->m_right == nullptr) // left child only
		{
			tempNode = node;
			node = node->m_left;
			delete tempNode;
		}
		else // two children, urgh
		{
			tempNode = FindMinimum(node->m_right);
			node->m_data = tempNode->m_data;
			Delete(tempNode->m_data, node->m_right);
		}

		if(node)
		{
			if(node->m_left)
			{
				node->m_left->UpdateHeight();
				node->m_left->UpdateBalanceFactor();
			}
			if(node->m_right)
			{
				node->m_right->UpdateHeight();
				node->m_right->UpdateBalanceFactor();
			}

			RebalanceUp(node);

			/*
			// we deleted a node, so update the balance factors all the way back up
			if(node) // if we deleted a node and it still has a subtree/children remaining
			{
			node->UpdateHeight();
			node->UpdateBalanceFactor();

			// now, rebalance
			if(node->m_balanceFactor == LEFT_TOO_HEAVY || node->m_balanceFactor == RIGHT_TOO_HEAVY)
			{
			Rebalance(node);
			}
			}
			*/
		}
	}
}

// try 2
template <class T>
T* AVLTree<T>::Delete2(T const& data, AVLTreeNode<T> *& node, short & height_change)
{
	T* found_node = nullptr;
	if(node == nullptr)
	{
		height_change = false;
		found_node = nullptr;
	}
	else
	{
		short decrease = 0;

		if(node->m_data != data)
		{
			if(data > node->m_data)
			{
				found_node = Delete2(data, node->m_right, height_change);
			}
			else
			{
				found_node = Delete2(data, node->m_left, height_change);
			}
			if(found_node)
			{
				//decrease = result * height_change; // result is root->Compare(key, cmp) in other implementation
			}
		}
		else
		{
			//found_node = node->m_data; // TEMP REMOVED

			// now, we know node contains the data node we're gonna delete
			// go through 3 cases
			// - 0 children (leaf node)
			// - 1 child
			// - 2 children

			if(node->m_left == nullptr && node->m_right == nullptr)
			{
				// case 1: no children
				delete node;
				node = nullptr;
				height_change = 1;
			}
			else if(node->m_left == nullptr || node->m_right == nullptr)
			{
				// case 2: one child
				AVLTreeNode<T>* temp = node;
				node = (node->m_left)? node->m_left : node->m_right;
				height_change = 1;
				temp->m_left = temp->m_right = nullptr; // shouldn't be needed in current implementation
				delete temp;
			}
			else
			{
				// case 3: two children
				//node->m_data = Delete2(data, node->m_right, decrease); // TEMP REMOVED
			}
		}

		node->m_balanceFactor -= decrease;

		// begin rebalancing
		if(decrease)
		{
			if(node->m_balanceFactor)
			{
				height_change = Rebalance(node);
			}
			else
			{
				height_change = 1;
			}
		}
		else
		{
			height_change = 0;
		}
	}
	return found_node;
}

template <class T>
int AVLTree<T>::Height(void) const
{
	return Height(m_root);
}

// follows the heavy part of the tree right to the bottom and counts how far down that is
template <class T>
int AVLTree<T>::Height(AVLTreeNode<T>* node) const
{
	int height = -1;
	if(node)
	{
		if(node->m_balanceFactor == LEFT_HEAVY)
		{
			height = 1 + Height(node->m_left);
		}
		else
		{
			height = 1 + Height(node->m_right);
		}
	}
	return height;
}

template <class T>
int AVLTree<T>::RotateRight(AVLTreeNode<T> *& node)
{
	AVLTreeNode<T>* root = node;
	AVLTreeNode<T>* child = node->m_right;
	AVLTreeNode<T>* T2 = node->m_right->m_left;

	node = child; // the new root is the old child
	child->m_left = root; // the new root's opposite side is the old root
	root->m_right = T2; // T2 swaps sides from old child's left to new child's right

	// if the opposite subtree is balanced, a RR will not change tree height
	int height_change = (node->m_left->m_balanceFactor == 0)? 0 : 1;

	root->m_balanceFactor = -(++node->m_balanceFactor);

	return height_change;
}

template <class T>
int AVLTree<T>::RotateLeft(AVLTreeNode<T> *& node)
{
	AVLTreeNode<T>* root = node;
	AVLTreeNode<T>* child = node->m_left;
	AVLTreeNode<T>* T2 = node->m_left->m_right;

	node = child; // the new root is the old child
	child->m_right = root; // the new root's opposite side is the old root
	root->m_left = T2; // T2 swaps sides from old child's right to new child's left

	int height_change = (node->m_right->m_balanceFactor == 0)? 0 : 1;

	root->m_balanceFactor = -(--node->m_balanceFactor);

	return height_change;
}

template <class T>
int AVLTree<T>::RotateRightLeft(AVLTreeNode<T> *& node)
{
	RotateLeft(node->m_right);
	RotateRight(node);
	return 1; // double rotations always change the height of the tree
}

template <class T>
int AVLTree<T>::RotateLeftRight(AVLTreeNode<T> *& node)
{
	RotateRight(node->m_left);
	RotateLeft(node);
	return 1; // double rotations always change the height of the tree
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
AVLTreeNode<T>* AVLTree<T>::FindMinimum(AVLTreeNode<T>* node) const
{
	AVLTreeNode<T>* ptr = nullptr;

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

template <class T>
int AVLTree<T>::Rebalance(AVLTreeNode<T> *& node)
{
	int height_change = 0;

	if(node->m_balanceFactor == LEFT_TOO_HEAVY || node->m_balanceFactor == RIGHT_TOO_HEAVY)
	{
		// tree is unbalanced, rotate and fix it.
		cout << "Rebalancing tree..." << endl;

		// node is the root of the problem (-2/2 bal factor)
		if(node->m_balanceFactor == LEFT_TOO_HEAVY)
		{
			// positive value indicates we are currently left heavy
			if(node->m_left->m_balanceFactor == LEFT_HEAVY)
			{
				// subtree is also left heavy => LL
				cout << "Performing LL rotation..." << endl;
				height_change = RotateLeft(node);
			}
			else
			{
				// subtree is right heavy => LR
				cout << "Performing LR rotation..." << endl;
				height_change = RotateLeftRight(node);

				node->m_left->UpdateHeight();
				node->m_left->UpdateBalanceFactor();
			}

			node->m_right->UpdateHeight();
			node->m_right->UpdateBalanceFactor();
		}
		else
		{
			// otherwise, we are right heavy
			if(node->m_right->m_balanceFactor == LEFT_HEAVY)
			{
				// subtree is left heavy => RL
				cout << "Performing RL rotation..." << endl;
				height_change = RotateRightLeft(node);

				node->m_right->UpdateHeight();
				node->m_right->UpdateBalanceFactor();
			}
			else
			{
				// subtree is right heavy => RR
				cout << "Performing RR rotation..." << endl;
				height_change = RotateRight(node);
			}
			node->m_left->UpdateHeight();
			node->m_left->UpdateBalanceFactor();
		}
		node->UpdateHeight();
		node->UpdateBalanceFactor();
	}

	return height_change;
}

template <class T>
void AVLTree<T>::RebalanceUp(AVLTreeNode<T> *& node)
{
	stack< AVLTreeNode<T>* > nodesToUpdate;

	AVLTreeNode<T>* ptr = m_root;

	while(ptr && ptr != node)
	{
		nodesToUpdate.push(ptr);

		if(node->m_data < ptr->m_data)
		{
			ptr = ptr->m_left;
		}
		else
		{
			ptr = ptr->m_right;
		}
	}

	// now that we have a path from the top of the tree to this node,
	// follow that path back up the tree, updating heights/balfactors and balancing as needed
	while(nodesToUpdate.size())
	{
		ptr = nodesToUpdate.top();
		nodesToUpdate.pop();

		ptr->UpdateHeight();
		ptr->UpdateBalanceFactor();

		if(node->m_balanceFactor == LEFT_TOO_HEAVY || node->m_balanceFactor == RIGHT_TOO_HEAVY)
			Rebalance(ptr);
	}
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
void AVLTree<T>::InOrderTraversal(void (*traverseFunc)(T& data))
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
void AVLTree<T>::InOrderTraversal(void (*traverseFunc)(T const& data)) const
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
void AVLTree<T>::PreOrderTraversal(void (*traverseFunc)(T& data))
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
void AVLTree<T>::PreOrderTraversal(void (*traverseFunc)(T const& data)) const
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
void AVLTree<T>::PostOrderTraversal(void (*traverseFunc)(T& data))
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
void AVLTree<T>::PostOrderTraversal(void (*traverseFunc)(T const& data)) const
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
void AVLTree<T>::BreadthFirstTraversal(void (*traverseFunc)(T& data))
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
void AVLTree<T>::BreadthFirstTraversal(void (*traverseFunc)(T const& data)) const
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