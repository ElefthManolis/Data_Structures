#include "MaxHeap.h"

MaxHeap::~MaxHeap()
{
	delete[] heap;
}

bool MaxHeap::Build(std::string filename)
{
	std::fstream data(filename, std::ios::in);
	if (!data)
		return false;

	// count the elements
	std::string number = "";
	while (std::getline(data, number))
		currentSize++;

	maxSize = currentSize + 100;
	delete[] heap; // delete for safety
	heap = new int[maxSize];

	// Go to the start of the file
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

bool MaxHeap::Insert(int number)
{
	if (currentSize < maxSize)
	{
		int pos = ++currentSize;
		heap[pos] = number;
		while (pos > 1 && heap[parent(pos)] < heap[pos])
		{
			Swap(pos, parent(pos));
			pos = parent(pos);
		}
		return true;
	}
	return false;
}

bool MaxHeap::DeleteMax()
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
				if (temp < heap[leftC])
					newPos = leftC;
				if (rightC <= currentSize)
					if (heap[leftC] < heap[rightC])
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

int MaxHeap::GetSize() const
{
	return currentSize;
}

int MaxHeap::GetMax() const
{
	if (currentSize > 0)
		return heap[1];
	else
		return -1;
}

void MaxHeap::Heapify(int level)
{
	int parent = heap[level];
	int leftPos = leftChild(level);
	int rightPos = rightChild(level);
	int maxPos = level;

	if (leftPos <= currentSize)
	{
		if (parent < heap[leftPos])
			maxPos = leftPos;
		if (rightPos <= currentSize)
			if (heap[maxPos] < heap[rightPos])
				maxPos = rightPos;
	}
	if (maxPos != level)
	{
		Swap(maxPos, level);
		Heapify(maxPos);
	}
}

void MaxHeap::Swap(int i, int j)
{
	int temp = heap[i];
	heap[i] = heap[j];
	heap[j] = temp;
}

int MaxHeap::parent(int i)
{
	return i / 2;
}

int MaxHeap::leftChild(int parentPos)
{
	return 2 * parentPos;
}

int MaxHeap::rightChild(int parentPos)
{
	return (2 * parentPos) + 1;
}
