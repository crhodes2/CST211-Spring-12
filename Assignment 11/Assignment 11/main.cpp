/***********************************************************
* Author:		Andrew Sparkes
* Title:		CST 211 Assignment 11
* Filename:		main.cpp
* Date Created:	5-24-12
* Modified:		5-26-12 : documentation, small tweaks
*
* Overview:
*	This program is a driver demonstrating the basic 
*	capabilities of a undirected graph class
*
* Input:
*	None.
*
* Output:
*	Will output a basic test of the class to console.
************************************************************/
#include <iostream>
using std::cout;
using std::endl;

#include "UndirectedGraph.h"

#include <string>
using std::string;

#include <crtdbg.h> 
#define _CRTDBG_MAP_ALLOC

template <class T>
void Print(T& data);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	cout << "Making a graph with string type data and double type weights..." << endl;
	UndirectedGraph<string, string, double> myGraph;

	/*
	myGraph.InsertEdge("Klamath Falls, OR", "Medford, OR", "Edge Description Here", 76.8);
	myGraph.InsertEdge("Klamath Falls, OR", "Eugene, OR", "Edge Description Here", 173.0);
	myGraph.InsertEdge("Klamath Falls, OR", "Bend, OR", "Edge Description Here", 137.0);
	myGraph.InsertEdge("Medford, OR", "Eugene, OR", "Edge Description Here", 167.0);
	myGraph.InsertEdge("Eugene, OR", "Salem, OR", "Edge Description Here", 66.3);
	myGraph.InsertEdge("Salem, OR", "Portland, OR", "Edge Description Here", 47.1);
	myGraph.InsertEdge("Bend, OR", "Salem, OR", "Edge Description Here", 132.0);
	myGraph.InsertEdge("Eugene, OR", "Bend, OR", "Edge Description Here", 128.0);
	myGraph.InsertEdge("Bend, OR", "Portland, OR", "Edge Description Here", 162.0);
	*/
	
	myGraph.ForceInsertEdge("A", "B", "A<->B", 1);
	myGraph.ForceInsertEdge("B", "C", "B<->C", 1);
	myGraph.ForceInsertEdge("C", "A", "C<->A", 1);
	myGraph.ForceInsertEdge("D", "A", "D<->A", 1);
	myGraph.ForceInsertEdge("D", "E", "D<->E", 1);
	myGraph.ForceInsertEdge("A", "E", "A<->E", 1);

	
	
	cout << endl << "Outputting graph:" << endl;
	cout << "BreadthFirstTraversal:" << endl;
	myGraph.BreadthFirstTraversal(&Print<string>);
	cout << "DepthFirstTraversal:" << endl;
	myGraph.DepthFirstTraversal(&Print<string>);

	UndirectedGraph<string, string, double> test;
	test = myGraph;
	
	cout << endl << "Outputting assigned graph:" << endl;
	cout << "BreadthFirstTraversal:" << endl;
	test.BreadthFirstTraversal(&Print<string>);
	cout << "DepthFirstTraversal:" << endl;
	test.DepthFirstTraversal(&Print<string>);

	UndirectedGraph<string, string, double> copy(test);
	
	cout << endl << "Outputting copy constructed graph:" << endl;
	cout << "BreadthFirstTraversal:" << endl;
	copy.BreadthFirstTraversal(&Print<string>);
	cout << "DepthFirstTraversal:" << endl;
	copy.DepthFirstTraversal(&Print<string>);

	cout << "Removing B Node" << endl;
	myGraph.DeleteNode(string("B"));
	myGraph.BreadthFirstTraversal(&Print<string>);

	cout << "Removing Edge from A to E" << endl;
	myGraph.DeleteEdge(string("A"), string("E"));
	myGraph.BreadthFirstTraversal(&Print<string>);

	system("pause");
	return 0;
}

template <class T>
void Print(T& data)
{
	cout << data << endl;
}