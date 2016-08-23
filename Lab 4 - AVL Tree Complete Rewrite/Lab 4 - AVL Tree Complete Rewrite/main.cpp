/***********************************************************
* Author:		Andrew Sparkes
* Lab Number:	CST 211 Lab 4 Complete Rewrite
* Filename:		main.cpp
* Date Created:	5-20-12
* Modifications:	5-25-12 Pain, anguish, suffering
*
* Overview:
*	This program demos a basic avl tree data struct.
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

	int numbers[] = {2, 3, 4, 5, 16, 35, 63, 77, 15, 66, 78, 10, 71, 999, 35, 125, 6};


	// make a avl tree and dump the above numbers in it
	cout << "Creating a avl tree of ints" << endl;
	AVLTree<int,int> tree;

	for(unsigned i = 0; i < sizeof(numbers)/sizeof(int); ++i)
	{
		cout << "Adding " << numbers[i] << " to the tree. " << endl;
		tree.Insert(numbers[i],numbers[i]);
		cout << "Height is now " << tree.Height() << endl;
		cout << "Still an AVL Tree? " << ((tree.VerifyAVLTree())? "Yes" : "No" ) << endl;
	}

	cout << "Now, traversing over the tree to show the inserted values: " << endl;
	tree.BreadthFirstTraversal(&Print<int>);
	cout << endl;

	cout << "Making a copy via copy constructor so we can demo delete on the first tree..." << endl;
	AVLTree<int,int> copy(tree);

	cout << "The duplicated tree (with same structure as original): " << endl;
	copy.BreadthFirstTraversal(&Print<int>);
	cout << endl;

	cout << "Now, removing any numbers that are odd from the tree to demo delete()..." << endl;
	for(unsigned i = 0; i < sizeof(numbers)/sizeof(int); ++i)
	{
		if(numbers[i] % 2 == 1)
		{
			cout << "Deleting " << numbers[i] << "..." << endl;
			tree.Delete(numbers[i]);
			cout << "Tree after deleting " << numbers[i] << endl;
			cout << "Still an AVL Tree? " << ((tree.VerifyAVLTree())? "Yes" : "No" ) << endl;

			tree.BreadthFirstTraversal(&Print<int>);
			cout << endl;
		}
	}
	
	cout << "Trying to delete 1... (does nothing, as 1 is not in the tree)" << endl;
	tree.Delete(1);

	cout << "Now, traversing over the tree to show the deleted values: " << endl;
	tree.BreadthFirstTraversal(&Print<int>);
	cout << endl;

	cout << "Now, purging the whole tree..." << endl;
	tree.Purge();

	cout << "Now, traversing over the tree to show that it is purged: " << endl;
	tree.BreadthFirstTraversal(&Print<int>);
	cout << endl;

	cout << "Now, demoing op= to set the tree to the copy we made a minute ago..." << endl;
	tree = copy;

	cout << "Now, traversing over the tree to show that it assigned properly: " << endl;
	tree.BreadthFirstTraversal(&Print<int>);
	cout << endl;
	
	cout << "Now, testing Traversal with a function that simple doubles each value to show traversal can take any (proper) function argument..." << endl;
	tree.BreadthFirstTraversal(&Double<int>);
	tree.BreadthFirstTraversal(&Print<int>);
	cout << endl;

	cout << "Note: Used breadth first traversal for all traversals as inorder was not helping me to visualize the tree at all, breadth first was a bit more helpful." << endl;

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