#pragma once

#include "AVLNode.h"
#include <algorithm>
using std::max;
#include <queue>
using std::queue;

template <class KeyType, class DataType>
class AVLTree
{
private:
	AVLNode<KeyType, DataType>* m_root;

	static enum BALANCES {RIGHT_TOO_HEAVY = -2, RIGHT_HEAVY = -1, BALANCED = 0, LEFT_HEAVY = 1, LEFT_TOO_HEAVY = 2};

	static void ForceHeightUpdate(AVLNode<KeyType, DataType>* root);
	static void ForceBalanceFactorUpdate(AVLNode<KeyType, DataType>* root);

	static unsigned Height(AVLNode<KeyType, DataType>* root);

	static void RotateR(AVLNode<KeyType, DataType> *& root); // aka single right
	static void RotateL(AVLNode<KeyType, DataType> *& root); // aka single left
	static void RotateRL(AVLNode<KeyType, DataType> *& root); // aka double right
	static void RotateLR(AVLNode<KeyType, DataType> *& root); // aka double left
	
	bool Insert(KeyType const& key, DataType const& data, AVLNode<KeyType, DataType> *& node);

	bool Delete(KeyType const& key, AVLNode<KeyType, DataType> *& node);

	bool VerifyAVLTree(AVLNode<KeyType, DataType>* root) const;

public:
	AVLTree();
	AVLTree(AVLTree<KeyType, DataType> const& copy);
	~AVLTree();

	AVLTree<KeyType, DataType> const& operator=(AVLTree<KeyType, DataType> const& rhs);

	bool VerifyAVLTree() const;

	bool isEmpty() const;

	bool Insert(KeyType const& key, DataType const& data); // public facing insert

	bool Delete(KeyType const& key); // public facing delete
	
	void Purge();

	int Height() const;

	void BreadthFirstTraversal(void (*traverseFunc)(DataType& data));
	void BreadthFirstTraversal(void (*traverseFunc)(DataType const& data)) const;
};

template <class KeyType, class DataType>
AVLTree<KeyType, DataType>::AVLTree() 
	: m_root(nullptr)
{
	
}

template <class KeyType, class DataType>
AVLTree<KeyType, DataType>::AVLTree(AVLTree<KeyType, DataType> const& copy)
	: m_root(nullptr)
{
	*this = copy;
}

template <class KeyType, class DataType>
AVLTree<KeyType, DataType>::~AVLTree()
{
	delete m_root;
}

template <class KeyType, class DataType>
AVLTree<KeyType, DataType> const& AVLTree<KeyType, DataType>::operator=(AVLTree<KeyType, DataType> const& rhs)
{
	queue< AVLNode<KeyType, DataType>* > q;
	q.push(rhs.m_root);

	AVLNode<KeyType, DataType>* ptr = nullptr;

	while(!q.empty())
	{
		ptr = q.front();
		q.pop();

		Insert(ptr->getKey(), ptr->getData(), m_root);
		if(ptr->getLeft())
		{
			q.push(ptr->getLeft());
		}
		if(ptr->getRight())
		{
			q.push(ptr->getRight());
		}
	}
	return *this;
}

template <class KeyType, class DataType>
bool AVLTree<KeyType, DataType>::VerifyAVLTree() const
{
	return VerifyAVLTree(m_root);
}

template <class KeyType, class DataType>
bool AVLTree<KeyType, DataType>::VerifyAVLTree(AVLNode<KeyType, DataType>* root) const
{
	bool isAVLTree = true;

	if(root)
	{
		isAVLTree &= VerifyAVLTree(root->getLeft());
		isAVLTree &= VerifyAVLTree(root->getRight());
		
		if( root->getBalanceFactor() != Height(root->getLeft()) - Height(root->getRight()) // if the balance factor is incorrect
			|| (root->getBalanceFactor() != LEFT_HEAVY && root->getBalanceFactor() != RIGHT_HEAVY && root->getBalanceFactor() != BALANCED)) // or if the balance factor is not left/right heavy or balanced
		{
			// then we don't have a AVL tree
			isAVLTree = false;
		}
	}
	return isAVLTree;
}

template <class KeyType, class DataType>
bool AVLTree<KeyType, DataType>::isEmpty() const
{
	return (m_root == nullptr);
}

template <class KeyType, class DataType>
bool AVLTree<KeyType, DataType>::Insert(KeyType const& key, DataType const& data)
{
	return Insert(key, data, m_root);
}

template <class KeyType, class DataType>
bool AVLTree<KeyType, DataType>::Insert(KeyType const& key, DataType const& data, AVLNode<KeyType, DataType> *& node)
{
	bool height_changed = false;
	if(node)
	{
		if(key < node->getKey()) // key lower than current node's key, insert before node
		{
			if(node->getLeft())
			{
				height_changed = Insert(key, data, node->getLeft());
			}
			else
			{
				node->setLeft(new AVLNode<KeyType, DataType>(nullptr, nullptr, key, data));
				height_changed = true;
			}
		}
		else if(key > node->getKey()) // key greater than current node's key, insert after node
		{
			if(node->getRight())
			{
				height_changed = Insert(key, data, node->getRight());
			}
			else
			{
				node->setRight(new AVLNode<KeyType, DataType>(nullptr, nullptr, key, data));
				height_changed = true;
			}
		}
		else // same key as current node's key
		{
			// current behavior requires unique keys for each node
		}
	}
	else // inserting into a nullptr node, likely inserting into an empty tree
	{
		node = new AVLNode<KeyType, DataType>(nullptr, nullptr, key, data);
		height_changed = true;
	}

	if(height_changed)
	{
		ForceBalanceFactorUpdate(node); //update the balance factor for the current node
		ForceHeightUpdate(node);
		
		if(node->getBalanceFactor() == LEFT_TOO_HEAVY)
		{
			if(node->getLeft()->getBalanceFactor() == LEFT_HEAVY)
			{
				// we need to perform a LL rotation
				RotateL(node);
			}
			else
			{
				// we need to perform a LR rotation
				RotateLR(node);
			}
		}
		else if(node->getBalanceFactor() == RIGHT_TOO_HEAVY)
		{
			if(node->getRight()->getBalanceFactor() == LEFT_HEAVY)
			{
				// we need to perform a RL rotation
				RotateRL(node);
			}
			else
			{
				// we need to perform a RR rotation
				RotateR(node);
			}
		}
	}

	return height_changed;
}

template <class KeyType, class DataType>
bool AVLTree<KeyType, DataType>::Delete(KeyType const& key)
{
	return Delete(key, m_root);
}

template <class KeyType, class DataType>
bool AVLTree<KeyType, DataType>::Delete(KeyType const& key, AVLNode<KeyType, DataType> *& node)
{
	bool height_changed = false;
	if(node)
	{
		if(key < node->getKey()) // key lower than current node's key, insert before node
		{
			if(node->getLeft())
			{
				height_changed = Delete(key, node->getLeft());
			}
			else
			{
				// node not found
			}
		}
		else if(key > node->getKey()) // key greater than current node's key, insert after node
		{
			if(node->getRight())
			{
				height_changed = Delete(key, node->getRight());
			}
			else
			{
				// node not found
			}
		}
		else // same key as current node's key
		{
			// now we've found the node we want to delete, determine what kind of node it is, leaf or one/two child
			AVLNode<KeyType, DataType>* tmp = nullptr; // temp pointer used below
			
			if(node->getLeft() && node->getRight()) // two children, urgh
			{
				// first, find the predecessor of the current node, i.e. the smallest (left-est) value in the right subtree
				tmp = node->getRight();
				while(tmp->getLeft())
				{
					tmp = tmp->getLeft();
				}

				// now, set the current node equal to the predecessor found above
				node->setData(tmp->getData());
				node->setKey(tmp->getKey());

				// and now finally go through and delete the (old) predecessor value from the right subtree
				Delete(node->getData(), node->getRight());
			}
			else if(node->getLeft() && !node->getRight()) // left child only
			{
				tmp = node;
				node = node->getLeft();
				tmp->setLeft(nullptr); // set children to null pointers so it doesn't recursively delete children
				tmp->setRight(nullptr);
				delete tmp;
			}
			else if(!node->getLeft() && node->getRight()) // right child only
			{
				tmp = node;
				node = node->getRight();
				tmp->setLeft(nullptr); // set children to null pointers so it doesn't recursively delete children
				tmp->setRight(nullptr);
				delete tmp;
			}
			else // leaf node
			{
				node->setLeft(nullptr); // set children to null pointers so it doesn't recursively delete children
				node->setRight(nullptr);
				delete node;
				node = nullptr;
			}
			height_changed = true; // any of the four cases above can change height of tree, so check and rebalance after
		}
	}

	if(height_changed && node)
	{
		ForceBalanceFactorUpdate(node); //update the balance factor for the current node
		ForceHeightUpdate(node);

		if(node->getBalanceFactor() == LEFT_TOO_HEAVY)
		{
			if(node->getLeft()->getBalanceFactor() == LEFT_HEAVY || node->getLeft()->getBalanceFactor() == BALANCED)
			{
				// we need to perform a LL rotation
				RotateL(node);
			}
			else
			{
				// we need to perform a LR rotation
				RotateLR(node);
			}
		}
		else if(node->getBalanceFactor() == RIGHT_TOO_HEAVY)
		{
			if(node->getRight()->getBalanceFactor() == LEFT_HEAVY || node->getRight()->getBalanceFactor() == BALANCED)
			{
				// we need to perform a RL rotation
				RotateRL(node);
			}
			else
			{
				// we need to perform a RR rotation
				RotateR(node);
			}
		}
	}

	return height_changed;
}

template <class KeyType, class DataType>
void AVLTree<KeyType, DataType>::Purge()
{
	delete m_root;
	m_root = nullptr;
}

template <class KeyType, class DataType>
int AVLTree<KeyType, DataType>::Height() const
{
	return Height(m_root);
}

template <class KeyType, class DataType>
void AVLTree<KeyType, DataType>::BreadthFirstTraversal(void (*traverseFunc)(DataType& data))
{
	if(m_root)
	{
		queue< AVLNode<KeyType, DataType>* > q;
		q.push(m_root);

		AVLNode<KeyType, DataType>* ptr = nullptr;

		while(!q.empty())
		{
			ptr = q.front();
			q.pop();

			traverseFunc(ptr->getData());
			if(ptr->getLeft())
			{
				q.push(ptr->getLeft());
			}
			if(ptr->getRight())
			{
				q.push(ptr->getRight());
			}
		}
	}
}

template <class KeyType, class DataType>
void AVLTree<KeyType, DataType>::BreadthFirstTraversal(void (*traverseFunc)(DataType const& data)) const
{
	if(m_root)
	{
		queue< AVLNode<KeyType, DataType> const* > q;
		q.push(m_root);

		AVLNode<KeyType, DataType> const* ptr = nullptr;

		while(!q.empty())
		{
			ptr = q.front();
			q.pop();

			traverseFunc(ptr->getData());
			if(ptr->getLeft())
			{
				q.push(ptr->getLeft());
			}
			if(ptr->getRight())
			{
				q.push(ptr->getRight());
			}
		}
	}
}

template <class KeyType, class DataType>
void AVLTree<KeyType, DataType>::ForceHeightUpdate(AVLNode<KeyType, DataType>* root)
{
	if(root->getLeft())
	{
		ForceHeightUpdate(root->getLeft());
	}
	if(root->getRight())
	{
		ForceHeightUpdate(root->getRight());
	}

	if(root->getLeft() && root->getRight()) // has two children, max(left.height, right.height) + 1
	{
		root->setHeight(max(root->getLeft()->getHeight(), root->getRight()->getHeight()) + 1);
	}
	else if(root->getLeft() && !root->getRight()) // has one child, child.height + 1
	{
		root->setHeight(root->getLeft()->getHeight() + 1);
	}
	else if(!root->getLeft() && root->getRight()) // has one child, child.height + 1
	{
		root->setHeight(root->getRight()->getHeight() + 1);
	}
	else // no children, 0 height
	{
		root->setHeight(0);
	}
}

template <class KeyType, class DataType>
void AVLTree<KeyType, DataType>::ForceBalanceFactorUpdate(AVLNode<KeyType, DataType>* root)
{
	int left_height = -1;
	int right_height = -1;


	if(root->getLeft())
	{
		left_height = Height(root->getLeft());
	}
	if(root->getRight())
	{
		right_height = Height(root->getRight());
	}

	root->setBalanceFactor( left_height - right_height );

}

template <class KeyType, class DataType>	
unsigned AVLTree<KeyType, DataType>::Height(AVLNode<KeyType, DataType>* root)
{
	int height = -1;

	if(root){
		int left_height = -1;
		int right_height = -1;

		if(root->getLeft())
		{
			left_height = Height(root->getLeft());
		}

		if(root->getRight())
		{
			right_height = Height(root->getRight());
		}
		height = max(left_height, right_height) + 1;
	}
	return height;
}

template <class KeyType, class DataType>
void AVLTree<KeyType, DataType>::RotateR(AVLNode<KeyType, DataType> *& root)
{
	AVLNode<KeyType, DataType>* child = root->getRight();
	AVLNode<KeyType, DataType>* oldRoot = root;
	AVLNode<KeyType, DataType>* T2 = root->getRight()->getLeft();

	root = child;
	child->setLeft(oldRoot);
	oldRoot->setRight(T2);

	ForceBalanceFactorUpdate(root);
	ForceBalanceFactorUpdate(root->getLeft());
	ForceHeightUpdate(root);
}

template <class KeyType, class DataType>
void AVLTree<KeyType, DataType>::RotateL(AVLNode<KeyType, DataType> *& root)
{
	AVLNode<KeyType, DataType>* child = root->getLeft();
	AVLNode<KeyType, DataType>* oldRoot = root;
	AVLNode<KeyType, DataType>* T2 = root->getLeft()->getRight();

	root = child;
	child->setRight(oldRoot);
	oldRoot->setLeft(T2);

	ForceBalanceFactorUpdate(root);
	ForceBalanceFactorUpdate(root->getRight());
	ForceHeightUpdate(root);
}

template <class KeyType, class DataType>
void AVLTree<KeyType, DataType>::RotateRL(AVLNode<KeyType, DataType> *& root)
{
	RotateL(root->getRight());
	RotateR(root);
}

template <class KeyType, class DataType>
void AVLTree<KeyType, DataType>::RotateLR(AVLNode<KeyType, DataType> *& root)
{
	RotateR(root->getLeft());
	RotateL(root);
}