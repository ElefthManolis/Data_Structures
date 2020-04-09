#pragma once
#include <fstream>
#include <string>

class MinHeap
{
public:
	~MinHeap();
	bool Build(std::string filename);
	int GetSize() const;
	int GetMin() const;
	bool Insert(int number);
	bool DeleteMin();

private:
	void Heapify(int size);
	void Swap(int i, int j);
	int parent(int i) const;
	int leftChild(int parentPos) const;
	int rightChild(int parentPos) const;

private:
	int currentSize = 0;
	int maxSize = 0;
	int *heap = nullptr;
};