#include "MinHeap.h"

MinHeap::~MinHeap()
{
	delete[] heap;
}

bool MinHeap::Build(std::string filename)
{
	std::ifstream data(filename);
	if (!data)
		return false;

	//count the elements
	std::string number = "";
	while (std::getline(data, number))
		currentSize++;

	maxSize = currentSize + 100;
	delete[] heap; // delete for safety
	heap = new int[maxSize];

	//Go to start of file
	data.clear();
	data.seekg(0, std::ios_base::beg);

	// Fill the heap
	heap[0] = -1;
	int i = 1;
	while (std::getline(data, number))
	{
		int element = std::stoi(number);
		heap[i] = element;
		i++;
	}
	for (int i = currentSize / 2; i >= 1; i--)
		Heapify(i);
	return true;
}

bool MinHeap::Insert(int number)
{
	if (currentSize < maxSize)
	{
		int pos = ++currentSize;
		heap[pos] = number;
		while (pos > 1 && heap[parent(pos)] > heap[pos])
		{
			Swap(pos, parent(pos));
			pos = parent(pos);
		}
		return true;
	}
	return false;
}

bool MinHeap::DeleteMin()
{
	if (currentSize > 0)
	{
		int temp = heap[currentSize--];
		int tempPos = 1;
		int newPos = 1;
		heap[1] = temp;

		while (tempPos < currentSize)
		{
			int leftC = leftChild(tempPos);
			int rightC = rightChild(tempPos);
			if (leftC <= currentSize)
			{
				if (temp > heap[leftC])
					newPos = leftC;
				if (rightC <= currentSize)
					if (heap[leftC] > heap[rightC])
						newPos = rightC;
			}

			if (newPos != tempPos)
			{
				Swap(tempPos, newPos);
				tempPos = newPos;
			}
			else
				break;
		}
		return true;
	}
	return false;
}

int MinHeap::GetSize() const
{
	return currentSize;
}

int MinHeap::GetMin() const
{
	if (currentSize > 0)
		return heap[1];
	else
		return -1;
}

void MinHeap::Heapify(int level)
{
	int parent = heap[level];
	int leftPos = leftChild(level);
	int rightPos = rightChild(level);
	int minPos = level;

	if (leftPos <= currentSize)
	{
		if (parent > heap[leftPos])
			minPos = leftPos;
		if (rightPos <= currentSize)
			if (heap[minPos] > heap[rightPos])
				minPos = rightPos;
	}
	if (minPos != level)
	{
		Swap(minPos, level);
		Heapify(minPos);
	}
}

void MinHeap::Swap(int i, int j)
{
	int temp = heap[i];
	heap[i] = heap[j];
	heap[j] = temp;
}

int MinHeap::parent(int i) const
{
	return i / 2;
}

int MinHeap::leftChild(int parentPos) const
{
	return 2 * parentPos;
}

int MinHeap::rightChild(int parentPos) const
{
	return (2 * parentPos) + 1;
}
