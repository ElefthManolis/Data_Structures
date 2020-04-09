#pragma once
#include <string>
#include <fstream>

struct Cell
{
	Cell()
	{
		value = -1;
		next = nullptr;
	}
	Cell(int v)
	{
		value = v;
		next = nullptr;
	}
	int value;
	Cell* next;
};

class Graph
{
public:
	bool Build(std::string filename);
	bool Insert(std::string line);
	bool Delete(std::string line);
	void GetSize(int& n, int& l) const;
	int ConnectedComponents();
	int ComputeSpanningTree();

	int FindShortestPath(int start, int end); // NOT COMPLETED
	
private:
	int AddNode(int n);
	int FindIndex(int n);
	bool Insert(int a, int b);
	Cell* AddLink(Cell* cell, int value);
	bool RemoveLink(Cell& cell, int value);
	void DepthFirstSearch(int index, bool* visited);
	int BreadthFirstSearch(int start, int end, int currentDist);

private:
	Cell* Elements = nullptr;
	int nodes = 0;
	int links = 0;
	int maxSize = 0;

	void ExtractNumbers(std::string line, int& a, int& b);
};