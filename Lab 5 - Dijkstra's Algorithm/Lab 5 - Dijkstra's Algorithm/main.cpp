/***********************************************************
* Author:		Andrew Sparkes
* Title:		CST 211 Lab 5 - Dijkstra's Algorithm
* Filename:		main.cpp
* Date Created:	6-1-12
* Modified:		6-5-12 : Documentation, tweaks
*
* Overview:
*	This program demonstrates Dijkstra's Algorithm.
*
* Input:
*	Will take input from console.
*
* Output:
*	Will output demo to console.
************************************************************/
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <crtdbg.h> 
#define _CRTDBG_MAP_ALLOC

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <string>
using std::string;

#include <stack>
using std::stack;

#include <vector>
using std::vector;

#include <algorithm>
using std::sort;

#include <exception>
using std::exception;

#include <unordered_map>
using std::unordered_map;

using std::getline;

#include "UndirectedGraph.h"
#include "GraphPath.h"

void split(const string& str, const string& delim, vector<string>& parts);

template <class DataType, class DescType, class WeightType>
GraphPath<DataType, DescType, WeightType> Dijkstras(Graph<DataType, DescType, WeightType> const& graph, DataType source, DataType destination);

void EstimateTravelTime(const GraphPath<string, string, unsigned> &roadPath);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	const char* inputFilePath = "lab05.txt";

	UndirectedGraph<string, string, unsigned> graph;
	
	// first, we deal with the file input, and toss all the data into the graph
	ifstream input(inputFilePath);

	if(!input.is_open())
	{
		// file isn't open, throw stl exception
		throw exception("File failed to open.");
	}

	unsigned lineCount = 0;

	string buffer;
	vector<string> parts;
	while(!input.eof())
	{
		// read the whole line into the buffer
		getline(input, buffer);
		
		if(buffer != "") // make sure the line isn't blank...
		{
			++lineCount;
			
			// deal with the contents of the buffer, by splitting it, and then inputting it into the graph
			split(buffer, ",", parts);

			// now, parts has elements in this order: source, destination, description, weight
			// so force insert each of those edges into the graph
			cout << "Inserting Edge from " << parts[0] << " to " << parts[1] << " called '" << parts[2] << "' (length: " << atoi(parts[3].c_str()) << "mi)" << endl;
			graph.ForceInsertEdge(parts[0], parts[1], parts[2], atoi(parts[3].c_str()));
			
			parts.clear(); // remove contents of parts
		}
	}
	cout << "Read in " << lineCount << " records." << endl;

	string source;
	string destination;

	system("pause"); 
	system("cls");
	cout << "List of currently available nodes:" << endl;
	vector< string > listOfNodes = graph.GetListOfNodes();
	sort(listOfNodes.begin(), listOfNodes.end()); // sort them so it's easier for user to read through them

	for(vector<string>::iterator i = listOfNodes.begin(); i != listOfNodes.end(); ++i)
	{
		cout << "'" << *i << "', ";
	}
	cout << endl << endl;
	
	cout << "Please input desired source: " << endl;
	getline(cin, source);

	cout << "Please input desired destination: " << endl;
	getline(cin, destination);

	cout << "Calculating path with least weight from " << source << " to " << destination << "..." << endl;
	
	try
	{
		GraphPath<string, string, unsigned> path = Dijkstras(graph, source, destination);

		// output the path, and then calculate expected travel time, considering I5 is 65, all other roads are 55 mph limit.
		path.Display();

		// now calculate the travel time with the above stipulations
		EstimateTravelTime(path);
	}
	catch(exception e)
	{
		cout << "Error: " << e.what() << endl; // STL FTW
	}

	system("pause");
	return 0;
}

/**********************************************************************	
* Purpose: Splits a string into a vector of strings, based on a delimiter
*
* Entry: str can be any string
*		 delim can be any string
*		 parts is a vector of strings (assumed to be empty when func called)
*
* Exit: parts now contains str broken up into substrings, based on delim
*
************************************************************************/
// used from SO user tgamblin from: http://stackoverflow.com/questions/289347/using-strtok-with-a-string-argument-instead-of-char
// NOTE: Not my code, copied from StackOverflow, licensed under CC http://creativecommons.org/licenses/by-sa/3.0/
// with attribution required, I felt it simpler to use pre-existing code than to reinvent the wheel, even though this is a simple func
// Also, why is this not part of the STL?
void split(const string& str, const string& delim, vector<string>& parts) {
	size_t start, end = 0;
	while (end < str.size()) {
		start = end;
		while (start < str.size() && (delim.find(str[start]) != string::npos)) {
			start++;  // skip initial whitespace
		}
		end = start;
		while (end < str.size() && (delim.find(str[end]) == string::npos)) {
			end++; // skip to end of word
		}
		if (end-start != 0) {  // just ignore zero-length strings.
			parts.push_back(string(str, start, end-start));
		}
	}
}

/**********************************************************************	
* Purpose: Used to find a Dijkstra's least distance from two nodes on a graph
*
* Entry: graph can be any graph, including empty
*		 source and destination can be any datatype, but will be used as key, 
*			so simple comparable data types are suggested
*		 parameters for graph: WeightType should be some numeric type, 
*
* Exit: A path object representing the shortest path is returned.
*
************************************************************************/
template <class DataType, class DescType, class WeightType>
GraphPath<DataType, DescType, WeightType> Dijkstras(Graph<DataType, DescType, WeightType> const& graph, DataType source, DataType destination)
{
	// right off the bat, let's do a sanity check and make sure that both the source and destination are in the graph
	GraphNode<DataType, DescType, WeightType>* source_node = graph.FindNode(source);
	GraphNode<DataType, DescType, WeightType>* dest_node = graph.FindNode(destination);

	if(!source_node)
	{
		throw exception("Source node not found in graph!");
	}
	if(!dest_node)
	{
		throw exception("Destination node not found in graph!");
	}

	// now, get a list of the nodes in the graph, to be used later
	vector< DataType > listOfNodes = graph.GetListOfNodes();

	// create predecessor and distance maps
	// note that I do not initialize the pred/dist maps here, because I use the fact that the key isn't present in the map to indicate that they have a "-1" value. It worked out simpler this way.
	unordered_map< DataType, DataType > predecessor;
	unordered_map< DataType, WeightType > distance;

	// set distance from source to source = 0
	distance[source] = 0;

	// set up a variable to count the number of nodes we've processed
	unsigned processedCount = 0;
	

	// loop until we have processed all nodes
	while(listOfNodes.size())
	{
		//find the lowest dist, nonprocessed, initialized node, this is the current node
		vector< DataType >::iterator current = listOfNodes.begin();
		unsigned minimumDist = INT_MAX; // set to a large number, max integer should suffice

		for(vector< DataType >::iterator i = listOfNodes.begin(); i != listOfNodes.end(); ++i)
		{
			// if this node has a nonnull distance (aka has a defined key in the map) and is less than the current distance
			if(distance.find(*i) != distance.end() && distance[*i] < minimumDist)
			{
				current = i;
				minimumDist = distance[*i];
			}
		}
		
		// loop over each edge in the current node
		GraphNode< DataType, DescType, WeightType >* current_node = graph.FindNode(*current);

		for(list< GraphEdge< DataType, DescType, WeightType > >::iterator i = current_node->m_edges.begin();
			i != current_node->m_edges.end();
			++i)
		{
			// if the distance to edge destination in dist array is greater than that of distance[current]+edge's weight
			DataType edgeDest = (*i).m_destination->m_data;
			if(distance.find(edgeDest) == distance.end() || distance[edgeDest] > distance[*current] + graph.GetWeight(*current, edgeDest))
			{
				// set distance = that sum above
				distance[edgeDest] = distance[*current] + graph.GetWeight(*current, edgeDest);

				// set predecessor[dest] = current
				predecessor[edgeDest] = *current;
			}
		}

		// now we have processed the current node, so remove it from the list of nodes to process
		listOfNodes.erase(current);
	}

	// that's it for the Dijkstra algorithm itself, now to populate a path object, as the arrays are less than useful to an enduser
	
	// now, populate the GraphPath with the proper path, likely by referencing dist[dest] first, then using a stack and pushing predecessor[dest] (and backtracking) and then pop them off into the path
	stack<DataType> stk;
	stk.push(destination);

	// infinite loop here if you throw in Medford to Klamath Falls
	while(predecessor[destination] != source)
	{
		stk.push(predecessor[destination]);
		destination = predecessor[destination];
	}
	GraphPath<DataType, DescType, WeightType> path(source);

	
	// pointer and traveling pointer, so we can call graph.FindEdge(prev, curr) to get edge information
	GraphNode<DataType, DescType, WeightType>* prev = nullptr;
	GraphNode<DataType, DescType, WeightType>* curr = source_node;

	GraphEdge<DataType, DescType, WeightType>* edge = nullptr; // just a temp pointer to hold address of the current edge, so we don't have to look it up twice

	while(stk.size())
	{
		// shift the pointers
		prev = curr;
		curr = graph.FindNode(stk.top());

		// look up the edge that connects them
		edge = graph.FindEdge(prev->m_data, curr->m_data);

		// add that edge to the path
		path.AddEdge(curr->m_data, edge->m_description, edge->m_weight); 

		stk.pop();
	}
	


	return path;
}

/**********************************************************************	
* Purpose: This function takes a path, assumed to be a path over highways 
*		and roads through cities, and calculates estimated travel time 
*		assuming 55mph highway and 65mph on I-5 only.
*
* Entry: roadPath is a GraphPath with associated edge descriptions and weights
*
* Exit: Outputs a brief explanation of its accumulation logic and displays a total in hours.
*
************************************************************************/
void EstimateTravelTime(const GraphPath<string, string, unsigned> &roadPath)
{
	size_t numEdges = roadPath.m_edgePath.size();

	double travelTime = 0;
	double coefficient;

	for(size_t i = 0; i < numEdges; ++i)
	{
		if(roadPath.m_edgePath[i] == "I-5")
		{
			coefficient = 1.0/65.0;
		}
		else
		{
			coefficient = 1.0/55.0;
		}
		cout << "Traveling along " << roadPath.m_edgePath[i] << " for " << roadPath.m_weightPath[i] << " miles at " << pow(coefficient, -1.0) << " mph." << endl;
		travelTime += coefficient * roadPath.m_weightPath[i];
	}
	cout << "Total estimated travel time is " << travelTime << " hrs." << endl;
}