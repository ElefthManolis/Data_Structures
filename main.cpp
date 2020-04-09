#include <fstream>
#include <chrono>
#include "MaxHeap.h"
#include "MinHeap.h"
#include "Hashtable.h"
#include "AvlTree.h"
#include "Graph.h"

bool IsCommand(std::string command, std::string line)
{
	return (line.find(command) != std::string::npos);
}

std::string ExtractFilename(std::string command, std::string line)
{
	size_t pos = line.find_last_of(command);
	std::string filename = line.substr(pos + 1);
	return filename;
}

int ExtractNumber(std::string line)
{
	std::string n = "";
	unsigned int i = 0;
	while (i <= line.length() - 1)
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			n += line[i];
		}
		i++;
	}
	int number = -1;
	if (n != "")
		number = stoi(n);
	return number;
}

int main()
{
	using std::chrono::steady_clock;

	std::ifstream commands("commands.txt");
	std::ofstream output("output.txt");
	if (!commands)
	{
		output << "ERROR:\tCOMMAND FILE NOT FOUND" << std::endl;
		output << "HINT:\tFILE SHOULD BE IN THE SAME FOLDER AS THE EXECUTABLE NAMED \"commands.txt\"" << std::endl;
		return 0;
	}

	MaxHeap maxHeap;
	MinHeap minHeap;
	Hashtable hashTable;
	AVLTree avlTree;
	Graph graph;

	float totalTimeElapsed = 0.0;
	output << "COMMAND                                           RESULT";
	std::string line = "";
	while (std::getline(commands, line))
	{
		// Just some formating for the output
		output << std::endl << line;
		std::string space = "";
		for (unsigned int i = 0; i < (50 - line.length()); i++)
			space += '.';
		output << space;

		auto startPoint = std::chrono::steady_clock::now();

		int number = ExtractNumber(line);

		//~~~~~~~~~~~~~~~ MAX HEAP ~~~~~~~~~~~~~~~
		if (IsCommand("BUILD MAXHEAP", line))
		{
			std::string filename = ExtractFilename("BUILD MAXHEAP ", line);
			if (maxHeap.Build(filename))
				output << "SUCCESS - ";
			else
			{
				output << "FILE NOT FOUND. MAKE SURE IT IS A .txt LOCATED IN THE FOLDER OF THE EXECUTABLE";
				continue;
			}
		}
		else if (IsCommand("INSERT MAXHEAP", line))
		{
			if (maxHeap.Insert(number))
				output << "SUCCESS - ";
			else
			{
				output << "HEAP IS FULL";
				continue;
			}
		}
		else if (IsCommand("FINDMAX MAXHEAP", line))
		{
			int max = maxHeap.GetMax();
			if (max != -1)
				output << max;
			else
				output << "HEAP IS EMPTY";
			continue;
		}
		else if (IsCommand("DELETEMAX MAXHEAP", line))
		{
			if (maxHeap.DeleteMax())
				output << "SUCCESS - ";
			else
			{
				output << "HEAP IS EMPTY";
				continue;
			}
		}
		else if (IsCommand("GETSIZE MAXHEAP", line))
		{
			int size = maxHeap.GetSize();
			output << size << " ELEMENTS";
			continue;
		}

		//~~~~~~~~~~~~~~~ MIN HEAP ~~~~~~~~~~~~~~~
		else if (IsCommand("BUILD MINHEAP", line))
		{
			std::string filename = ExtractFilename("BUILD MINHEAP ", line);
			if (minHeap.Build(filename))
				output << "SUCCESS - ";
			else
			{
				output << "FILE NOT FOUND. MAKE SURE IT IS A .txt LOCATED IN THE FOLDER OF THE EXECUTABLE";
				continue;
			}
		}
		else if (IsCommand("INSERT MINHEAP", line))
		{
			if (minHeap.Insert(number))
				output << "SUCCESS - ";
			else
			{
				output << "HEAP IS FULL";
				continue;
			}
		}
		else if (IsCommand("FINDMIN MINHEAP", line))
		{
			int min = minHeap.GetMin();
			if (min != -1)
				output << min;
			else
				output << "HEAP IS EMPTY";
			continue;
		}
		else if (IsCommand("DELETEMIN MINHEAP", line))
		{
			if (minHeap.DeleteMin())
				output << "SUCCESS - ";
			else
			{
				output << "HEAP IS EMPTY";
				continue;
			}
		}
		else if (IsCommand("GETSIZE MINHEAP", line))
		{
			int size = minHeap.GetSize();
			output << size << " ELEMENTS";
			continue;
		}

		//~~~~~~~~~~~~~~~ HASHTABLE ~~~~~~~~~~~~~~~
		else if (IsCommand("BUILD HASHTABLE", line))
		{
			std::string filename = ExtractFilename("BUILD HASHTABLE ", line);
			if (hashTable.Build(filename))
				output << "SUCCESS - ";
			else
			{
				output << "FILE NOT FOUND. MAKE SURE IT IS A .txt LOCATED IN THE FOLDER OF THE EXECUTABLE";
				continue;
			}
		}
		else if (IsCommand("INSERT HASHTABLE", line))
		{
			if (hashTable.Insert(number))
				output << "SUCCESS - ";
			else
				output << "NUMBER ALREADY EXISTS - ";
		}
		else if (IsCommand("DELETE HASHTABLE", line))
		{
			if (hashTable.Delete(number))
				output << "SUCCESS - ";
			else
				output << "NUMBER NOT FOUND - ";
		}
		else if (IsCommand("SEARCH HASHTABLE", line))
		{
			if (hashTable.Search(number))
				output << "SUCCESS - ";
			else
				output << "NUMBER NOT FOUND - ";
		}
		else if (IsCommand("GETSIZE HASHTABLE", line))
		{
			int size = hashTable.GetSize();
			output << size << " ELEMENTS";
			continue;
		}

		//~~~~~~~~~~~~~~~ AVL TREE ~~~~~~~~~~~~~~~
		else if (IsCommand("BUILD AVLTREE", line))
		{
			std::string filename = ExtractFilename("BUILD AVLTREE ", line);
			if (avlTree.Build(filename))
				output << "SUCCESS - ";
			else
			{
				output << "FILE NOT FOUND. MAKE SURE IT IS A .txt LOCATED IN THE FOLDER OF THE EXECUTABLE";
				continue;
			}
		}
		else if (IsCommand("FINDMIN AVLTREE", line))
		{
			int min = avlTree.GetMin();
			if (min != -1)
				output << min << " - ";
			else
			{
				output << "AVL TREE IS EMPTY";
				continue;
			}
		}
		else if (IsCommand("INSERT AVLTREE", line))
		{
			avlTree.Insert(number);
		}
		else if (IsCommand("DELETE AVLTREE", line))
		{
			if (avlTree.Delete(number))
				output << "SUCCESS - ";
			else
				output << "NUMBER NOT FOUND - ";
		}
		else if (IsCommand("SEARCH AVLTREE", line))
		{
			if (avlTree.Search(number))
				output << "SUCCESS - ";
			else
				output << "NUMBER NOT FOUND - ";
		}
		else if (IsCommand("GETSIZE AVLTREE", line))
		{
			int size = avlTree.GetSize();
			output << size << " ELEMENTS";
			continue;
		}

		//~~~~~~~~~~~~~~~ GRAPH ~~~~~~~~~~~~~~~
		else if (IsCommand("BUILD GRAPH", line))
		{
			std::string filename = ExtractFilename("BUILD GRAPH ", line);
			if (graph.Build(filename))
				output << "SUCCESS - ";
			else
			{
				output << "FILE NOT FOUND. MAKE SURE IT IS A .txt LOCATED IN THE FOLDER OF THE EXECUTABLE";
				continue;
			}
		}
		else if (IsCommand("GETSIZE GRAPH", line))
		{
			int nodes, links;
			graph.GetSize(nodes, links);
			output << nodes << " NODE, " << links << " LINKS";
			continue;
		}
		else if (IsCommand("INSERT GRAPH", line))
		{
			if (graph.Insert(line))
				output << "SUCCESS - ";
			else
				output << "COULD NOT INSERT NEW NODE";
		}
		else if (IsCommand("DELETE GRAPH", line))
		{
			if (graph.Delete(line))
				output << "SUCCESS - ";
			else
				output << "NUMBERS OR LINK NOT FOUND - ";
		}
		else if (IsCommand("FINDCONNECTEDCOMPONENTS GRAPH", line))
		{
			int components = graph.ConnectedComponents();
			output << components << " - ";
		}
		else if (IsCommand("COMPUTESPANNINGTREE GRAPH", line))
		{
			output << graph.ComputeSpanningTree();
		}
		else if (IsCommand("COMPUTESHORTESTPATH GRAPH", line))
		{
			output << "NOT SUPPORTED";
			continue;
		}

		auto endPoint = std::chrono::steady_clock::now();
		auto commandRuntime = std::chrono::duration_cast<std::chrono::duration<float>>(endPoint - startPoint);
		float durationMs = commandRuntime.count() * 1000.0f;
		totalTimeElapsed += durationMs;
		output << durationMs << " ms";
	}
	output << "\n\nTOTAL TIME ELAPSED                                " << totalTimeElapsed << " ms" << std::endl;

	return 0;
}
