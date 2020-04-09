#pragma once
#include <fstream>
#include <string>

class MaxHeap
{
public:
	~MaxHeap();
	bool Build(std::string filename);
	bool Insert(int number);
	bool DeleteMax();
	int GetSize() const;
	int GetMax() const;

private:
	void Heapify(int size);
	void Swap(int i, int j);
	int parent(int i);
	int leftChild(int parentPos);
	int rightChild(int parentPos);

private:
	int currentSize = 0;
	int maxSize = 0;
	int *heap = nullptr;
};