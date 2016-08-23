/***********************************************************
* Author:		Andrew Sparkes
* Lab Number:	CST 211 Lab 4
* Filename:		main.cpp
* Date Created:	5-20-12
* Modifications:	5-21-12 Adjustments
*
* Overview:
*	This program demos a avl tree data struct.
*
* Input:
*	Nothing. Just a console demo of a avl tree.
*
* Output:
*	Output is written to console.
************************************************************/
#include <iostream>
using std::cout;
using std::endl;

#include "AVLTree.h"

#include <crtdbg.h> 
#define _CRTDBG_MAP_ALLOC

template <class T>
void Print(T& data);

template <class T>
void Double(T& data);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int numbers[] = {2, 3, 4, 5, 16, 35, 63, 77, 15, 66, 78, 10};
	//int numbers[] = {8,3,9,2,5,10,1,4,6,7};
	//int numbers[] = {7,5,9,3};
	//int numbers[] = {16, 10, 66, 4, 78, 2};

	// make a avl tree and dump the above numbers in it
	cout << "Creating a avl tree of ints" << endl;
	AVLTree<int> tree;

	for(unsigned i = 0; i < sizeof(numbers)/sizeof(int); ++i)
	{
		cout << "Adding " << numbers[i] << " to the tree. " << endl;
		tree.Insert(numbers[i]);
		cout << "Height is now " << tree.Height() << endl;
	}
	
	// REMOVE ME
	//tree.Insert(7);


	cout << "Now, traversing over the tree in order to show the inserted values: " << endl;
	tree.InOrderTraversal(&Print<int>);
	cout << endl;

	cout << "Making a copy via copy constructor so we can demo delete on the first tree..." << endl;
	AVLTree<int> copy(tree);

	cout << "The duplicated tree (with same structure as original): " << endl;
	copy.InOrderTraversal(&Print<int>);
	cout << endl;

	cout << "Now, removing any numbers that are odd from the tree to demo delete()..." << endl;
	for(unsigned i = 0; i < sizeof(numbers)/sizeof(int); ++i)
	{
		if(numbers[i] % 2 == 1)
		{
			cout << "Deleting " << numbers[i] << "..." << endl;
			tree.Delete(numbers[i]);
			cout << "Tree after deleting " << numbers[i] << endl;
			//tree.InOrderTraversal(&Print<int>);
			tree.BreadthFirstTraversal(&Print<int>);
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