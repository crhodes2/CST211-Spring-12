/***********************************************************
* Author:		Andrew Sparkes
* Lab Number:	CST 211 Assignment 10
* Filename:		main.cpp
* Date Created:	5-13-12
* Modifications:	5-18-12 Adjustments
*
* Overview:
*	This program demos a binary search tree data struct.
*
* Input:
*	Nothing. Just a console demo of a binary search tree.
*
* Output:
*	Output is written to console.
************************************************************/
#include <iostream>
using std::cout;
using std::endl;

#include "BinarySearchTree.h"

#include <crtdbg.h> 
#define _CRTDBG_MAP_ALLOC

template <class T>
void Print(T& data);

template <class T>
void Double(T& data);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int numbers[] = {4, 5, 16, 35, 63, 77, 15, 65, 78, 10};

	// make a binary search tree and dump the above numbers in it
	cout << "Creating a binary search tree of ints" << endl;
	BinarySearchTree<int> tree;

	for(unsigned i = 0; i < sizeof(numbers)/sizeof(int); ++i)
	{
		cout << "Adding " << numbers[i] << " to the tree. ";
		tree.Insert(numbers[i]);
		cout << "Height is now " << tree.Height() << endl;
	}
	
	cout << "Now, traversing over the tree in order to show the inserted values: " << endl;
	tree.InOrderTraversal(&Print<int>);
	cout << endl;

	cout << "Making a copy via copy constructor so we can demo delete on the first tree..." << endl;
	BinarySearchTree<int> copy(tree);

	cout << "The duplicated tree (with same structure as original): " << endl;
	copy.InOrderTraversal(&Print<int>);
	cout << endl;

	cout << "Now, removing any numbers that are odd from the tree to demo delete()..." << endl;
	for(unsigned i = 0; i < 10; ++i)
	{
		if(numbers[i] % 2 == 1)
		{
			tree.Delete(numbers[i]);
			cout << "After deleting " << numbers[i] << endl;
			tree.InOrderTraversal(&Print<int>);
			cout << endl;
		}
	}
	cout << "Trying to delete 1... (does nothing, as 1 is not in the tree)" << endl;
	tree.Delete(1);

	cout << "Now, traversing over the tree in order to show the deleted values: " << endl;
	tree.InOrderTraversal(&Print<int>);
	cout << endl;

	cout << "Now, purging the whole tree..." << endl;
	tree.Purge();

	cout << "Now, traversing over the tree to show that it is purged: " << endl;
	tree.InOrderTraversal(&Print<int>);
	cout << endl;

	cout << "Now, demoing op= to set the tree to the copy we made a minute ago..." << endl;
	tree = copy;

	cout << "Now, traversing over the tree to show that it assigned properly: " << endl;
	tree.InOrderTraversal(&Print<int>);
	cout << endl;

	cout << "Now, testing if any of the numbers 1-10 are in the tree using IsInTree()..." << endl;
	for(unsigned i = 1; i <= 10; ++i)
	{
		cout << "Does the tree contain " << i << "? " << ((tree.isInTree(i))? "yes":"no") << endl;
	}

	cout << "Displaying each type of traversal:" << endl;
	cout << "InOrder Traversal:" << endl;
	tree.InOrderTraversal(&Print<int>);
	cout << endl;

	cout << "PreOrder Traversal:" << endl;
	tree.PreOrderTraversal(&Print<int>);
	cout << endl;

	cout << "PostOrder Traversal:" << endl;
	tree.PostOrderTraversal(&Print<int>);
	cout << endl;

	cout << "BreadthFirst Traversal:" << endl;
	tree.BreadthFirstTraversal(&Print<int>);
	cout << endl;
	
	cout << "Now, testing InOrder Traversal with a function that simple doubles each value to show traversal can take any (proper) function argument..." << endl;
	tree.InOrderTraversal(&Double<int>);
	tree.InOrderTraversal(&Print<int>);
	cout << endl;

	system("pause");
	return 0;
}

template <class T>
void Double(T& data)
{
	data *= 2;
}

template <class T>
void Print(T& data)
{
	cout << data << " ";
}